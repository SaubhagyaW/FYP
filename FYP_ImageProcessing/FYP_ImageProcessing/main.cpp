#include "opencv2/highgui/highgui.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <list>
#include <fstream>

using namespace std;
using namespace cv;

//======camera calibration parameters============
const double ku = 1.4 * 1000000;
const double f = 3.6 / 1000;
const double v0_h0 = (f * ku) / 2;
// const float v0 = screenHeight / 2;
// const float h0 = screenWidth / 2;
const double h = 1;
// const float fku = 1000;
// const float v0 = 100;
// const float h = 1;
const int MAX_CORNERS = 100;
const int THRESHOLD = MAX_CORNERS * 0.1;
const string videoPath = "G:/Final Year Project/Prototype/dataset/test_video_1.mp4";

CvPoint2D32f* featuresArray;
int* heightFromFloor;
int numOfFeatures;

void validateFrame(Mat frame)
{
	if (!frame.data)
	{
		cout << "Frame not captured" << endl;
		exit(0);
	}
}

void findFeatures(Mat currentFrame, Rect rect)
{
	list<CvPoint2D32f> features;
	list<int> dist2B;

	Mat croppedRect;
	// Crop rect to cropped_rect
	currentFrame(rect).copyTo(croppedRect);

	// Extracting good features
	// Convert matrix croppedRect to IplImage
	IplImage* imgA = new IplImage(croppedRect);
	CvSize imgSize = cvGetSize(imgA);
	// Scratch image
	IplImage* eigImage = cvCreateImage(imgSize, IPL_DEPTH_32F, 1);
	IplImage* tmpImage = cvCreateImage(imgSize, IPL_DEPTH_32F, 1);

	// The cornerCount indicates the maximum number of points for which there is space to return. After the routine exits, 
	// corner_count is overwritten by the number of points that were actually found
	CvPoint2D32f* cornersA = new CvPoint2D32f[MAX_CORNERS];

	// Good feature points
	int cornerCount = MAX_CORNERS;
	cvGoodFeaturesToTrack(imgA, eigImage, tmpImage, cornersA, &cornerCount, 0.01, 5.0, 0, 3, 0, 0.04);

	// Mapping good features to the original picture and add them to the list of features and 
	// set their set(the rectangle they are belonging)
	for (int k = 0; k < MAX_CORNERS; k++)
	{
		int distance = rect.height - cornersA[k].y;
		dist2B.push_back(distance);

		// Mapping
		cornersA[k].x = rect.x + cornersA[k].x;
		cornersA[k].y = rect.y + cornersA[k].y;
		// Adding
		features.push_back(cornersA[k]);
	}


	int iter = 0;

	// Copy the features list to the final features array
	while (features.size() > 0)
	{
		CvPoint2D32f F_point = features.front();
		featuresArray[iter].x = F_point.x;
		featuresArray[iter].y = F_point.y;
		features.pop_front();

		int d = dist2B.front();
		heightFromFloor[iter] = d;
		dist2B.pop_front();
		iter++;
	}
}

int personFloor(bool & status)
{
	int sum = 0;
	int m = 0;

	for (int i = 0; i < numOfFeatures; i++)
	{
		sum += ((featuresArray[i].y + heightFromFloor[i]));
		m++;
	}

	if (m == 0)
	{
		status = false;
		return 0;
	}

	status = true;
	return(sum / m);
}

int scaledPersonFloor(bool &status)
{
	int y = personFloor(status);

	if (!status)
		return -1;

	float sum = 0;
	float m = 0;

	for (int i = 0; i < numOfFeatures; i++)
	{
		for (int j = i + 1; j < numOfFeatures; j++)
		{

			if (heightFromFloor[i] - heightFromFloor[j] < 2)
				continue;

			float t = (featuresArray[i].y - featuresArray[j].y) / (heightFromFloor[i] - heightFromFloor[j]);

			if (t < 0)
				t = -t;

			sum += t;
			m++;
		}
	}

	if (m == 0)
	{
		return(y);
	}

	float alpha = sum / m;
	return(alpha * y);
}

double computeDistance(double v)
{
	double distance = ((f * h * ku) / (v0_h0 - v));
	return distance;
}

double computeAngle()
{
	double sum = 0;

	for (int i = 0; i < numOfFeatures; i++)
	{
		sum += (featuresArray[i].x - v0_h0);
	}

	double avgX = sum / numOfFeatures;
	double val = avgX / (f * ku);
	double angle = atan2(avgX / ku, f);

	return angle;
}

void main() {
	//string ip;
	//int mode;
	//cout << "IP address: ";
	//cin >> ip;
	VideoCapture cap;
	int screenWidth, screenHeight;

	VideoCapture cap1(videoPath);
	cap = cap1;

	if (!cap.isOpened())
		exit(0);

	namedWindow("Video capture", CV_WINDOW_AUTOSIZE);

	screenWidth = cap1.get(CV_CAP_PROP_FRAME_WIDTH);
	screenHeight = cap1.get(CV_CAP_PROP_FRAME_HEIGHT);

	Mat currentFrame, currentFrameCopy, nextFrame;
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	double distance, angle;

	while (1)
	{
		vector<Rect> found, foundFiltered;
		CvPoint2D32f* trackedFeatures;

		// Detection loop
		while (1)
		{
			// Delete info of previous iteration
			foundFiltered.clear();
			// Get next frame
			cap >> currentFrame;
			validateFrame(currentFrame);
			currentFrame.copyTo(currentFrameCopy);

			// Convert it to the gray scale
			cvtColor(currentFrame, currentFrame, CV_BGR2GRAY);

			// Denoising
			//fastNlMeansDenoising(currentFrame, currentFrame, 10, 7, 21);
			//imshow("Video capture 2", currentFrame);
			//waitKey(100);

			// Detection with HOG algorithm
			hog.detectMultiScale(currentFrame, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);

			// Filter redundant rectangles
			for (int i = 0; i < found.size(); i++)
			{
				Rect r = found[i];
				int j;
				for (j = 0; j < found.size(); j++)
					if (j != i && (r & found[j]) == r)
						break;
				if (j == found.size())
					foundFiltered.push_back(r);
			}

			// Extracting good features for tracking
			// If at least one person found
			if (foundFiltered.size() > 0)
			{
				// Bound rectangles to the screen
				for (int i = 0; i < foundFiltered.size(); i++)
				{
					if (foundFiltered[i].x<0)
						foundFiltered[i].x = 0;

					if (foundFiltered[i].y<0)
						foundFiltered[i].y = 0;

					if (foundFiltered[i].x + foundFiltered[i].width > screenWidth)
						foundFiltered[i].width = screenWidth - foundFiltered[i].x;

					if (foundFiltered[i].y + foundFiltered[i].height > screenHeight)
						foundFiltered[i].height = screenHeight - foundFiltered[i].y;

					rectangle(currentFrameCopy, foundFiltered[i], CV_RGB(255, 0, 0), 2, 8, 0);

					string text = static_cast<ostringstream*>(&(ostringstream() << i + 1))->str();
					putText(currentFrameCopy, text,
						Point(foundFiltered[i].x + foundFiltered[i].width / 2, foundFiltered[i].y),
						CV_FONT_NORMAL, 1, CV_RGB(255, 0, 0), 1, 8);
				}

				// Showing detection
				imshow("Video capture", currentFrameCopy);
				waitKey(100);

				int personIndex;
				do {
					cout << "Target person: ";
					cin >> personIndex;
				} while ((personIndex < 0) || (personIndex > foundFiltered.size()));

				if (personIndex == 0) {
					continue;
				}

				Rect person = foundFiltered[personIndex - 1];

				// Find the list of features of the people
				try
				{
					featuresArray = new CvPoint2D32f[MAX_CORNERS];
					heightFromFloor = new int[MAX_CORNERS];

					findFeatures(currentFrame, person);
					numOfFeatures = MAX_CORNERS;
				}
				catch (Exception exp)
				{
					cout << "Exception: Find features error" << endl;
					continue;
				}

				break;
			}
		}

		while (1)
		{
			// Check for breaking condition
			// Check for enough number of features to track
			// Go to the detection loop when number of tracked features is less than an arbitrary threshold
			if (numOfFeatures < THRESHOLD)
			{
				cout << "Target lost" << endl;
				break;
			}

			// Reading the next frame
			currentFrameCopy.setTo(Scalar(0, 0, 0));
			cap >> nextFrame;
			validateFrame(nextFrame);
			nextFrame.copyTo(currentFrameCopy);

			// Convert it to gray scale
			cvtColor(nextFrame, nextFrame, CV_BGR2GRAY);

			// Tracking using Lucas-Kanade algorithm
			try
			{
				// LK parameters
				// Shows the status of points. 0 means feature lost. 1 means found
				//char status[numOfFeatures];
				char* status = (char *)malloc(sizeof(int)* numOfFeatures);
				// List of lost features
				//float featureErrors[numOfFeatures];
				float* featureErrors = (float *)malloc(sizeof(int)* numOfFeatures);
				trackedFeatures = new CvPoint2D32f[numOfFeatures];
				// Convert initial matrix image to IplImage
				IplImage* imgA = new IplImage(currentFrame);
				// Convert final matrix image to IplImage
				// Both should be single - channel, 8 - bit images.
				IplImage* imgB = new IplImage(nextFrame);
				CvSize pyrSize = cvSize(imgA->width + 8, imgB->height / 3);
				// Buffer allocated to store the pyramid images
				IplImage* pyrA = cvCreateImage(pyrSize, IPL_DEPTH_32F, 1);
				IplImage* pyrB = cvCreateImage(pyrSize, IPL_DEPTH_32F, 1);
				int win_size = 10;

				cvCalcOpticalFlowPyrLK(
					imgA, imgB, pyrA, pyrB,
					featuresArray, // Array containing the points for which the motion is to be found
					trackedFeatures, // Array containing the computed new locations of the points from features
					numOfFeatures, // Number of points in the features list
					cvSize(win_size, win_size), 5, status, featureErrors, cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, .3),
					0);

				free(featureErrors);

				// Updating the info after tracking
				// Updating feature points    
				// Removing info (set_number/distance to bottom) of lost features 
				int newNumOfFeatures = 0;
				int *tempDistance = new int[numOfFeatures];
				int j = 0;

				for (int i = 0; i < numOfFeatures; i++)
				{
					if (status[i] == 1)
					{
						// Counting number of features tracked successfully
						newNumOfFeatures++;

						tempDistance[j] = heightFromFloor[i];
						j++;
					}
				}

				free(status);

				heightFromFloor = tempDistance;
				numOfFeatures = newNumOfFeatures;
				delete[] featuresArray;
				featuresArray = new CvPoint2D32f[numOfFeatures];

				// Update features
				for (int i = 0; i < numOfFeatures; i++)
				{
					featuresArray[i] = trackedFeatures[i];
				}

				delete[] trackedFeatures;
				nextFrame.copyTo(currentFrame);
			}
			catch (Exception exp)
			{
				cout << "LK Exception" << endl;
				break;
			}

			// Computing distance
			bool status;
			int v = scaledPersonFloor(status);

			if (status)
			{
				distance = computeDistance(v);
				angle = computeAngle();

				string distTxt = static_cast<ostringstream*>(&(ostringstream() << distance))->str();
				distTxt = distTxt.substr(0, 5);
				string angleTxt = static_cast<ostringstream*>(&(ostringstream() << angle))->str();
				angleTxt = angleTxt.substr(0, 5);
				cout << distTxt << "\t" << angleTxt << endl;

				ofstream myfile;
				myfile.open("output2.txt", ios::app);
				myfile << distTxt << "\t" << angleTxt << endl;
				myfile.close();
			}

			imshow("Video capture", currentFrameCopy);
			waitKey(100);
		}
	}
}