#include "BackPersonFollowing.h"
#include <iostream>
#include <fstream>
#include "opencv/cv.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void BackPersonFollowing::adjustVelocityMagnitude()
{
	if (distance > maxOffsetDistance)
	{
		prev->setVelocityMagnitude(prev->getVelocityMagnitude() + offsetVelocityMagnitude);
	}
	else if (distance < minOffsetDistance)
	{
		prev->setVelocityMagnitude(prev->getVelocityMagnitude() - offsetVelocityMagnitude);
	}
}

void BackPersonFollowing::adjustVelocityDirection()
{
	if (angle > 0) {
		if (angle > (prev->getVelocityDirection() + offsetVelocityDirection)) {
			prev->setVelocityDirection(angle);
		}
	}
	else if (angle < 0) {
		if (angle >(prev->getVelocityDirection() - offsetVelocityDirection)) {
			prev->setVelocityDirection(angle);
		}
	}
}

void BackPersonFollowing::follow()
{
	int counter = 0;

	Mat canvas = Mat::zeros(800, 800, CV_8UC3);
	canvas = cv::Scalar(255, 255, 255);

	ifstream dataFile("input2.txt");
	double x, y, x_robot, y_robot;

	// Back person-following loop
	while (dataFile >> distance >> angle)
	{
		if (counter == 0)
		{
			prev = new Position(startVelocity, angle);
			prevDistance = distance;

			x = 500 + distance * sin(angle);
			y = distance * cos(angle);
			x_robot = 500;
			y_robot = 0;
			circle(canvas, Point(x + 50, y + 50), 2, CV_RGB(0, 0, 255), 2);
			imshow("canvas", canvas);
			waitKey(100);
			circle(canvas, Point(x_robot + 50, y_robot + 50), 2, CV_RGB(0, 255, 0), 2);
			imshow("canvas", canvas);
			waitKey(100);
		}
		else 
		{
			if (distance > (prevDistance + 5) || distance < (prevDistance - 5))
			{
				x += prevDistance * sin(angle);
				y += prevDistance * cos(angle);

				x_robot += (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
				y_robot += (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());
			} 
			else
			{
				x += distance * sin(angle);
				y += distance * cos(angle);

				x_robot += (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
				y_robot += (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());

				adjustVelocityMagnitude();
				adjustVelocityDirection();

				prevDistance = distance;
			}
			
			circle(canvas, Point(x + 50, y + 50), 2, CV_RGB(0, 0, 255), 2);
			imshow("canvas", canvas);
			waitKey(100);
			circle(canvas, Point(x_robot + 50, y_robot + 50), 2, CV_RGB(0, 255, 0), 2);
			imshow("canvas", canvas);
			waitKey(100);
		}
		//else
		//{
		//	x += (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
		//	y += (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());

		//	x_robot += (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
		//	y_robot += (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());

		//	//circle(canvas, Point(x_robot, y_robot), 2, CV_RGB(0, 255, 0), 2);
		//	//imshow("canvas", canvas);
		//	//waitKey(100);
		//	//circle(canvas, Point(x * 10 + 50, y * 10 + 50), 2, CV_RGB(0, 0, 255), 2);
		//	//imshow("canvas", canvas);
		//	//waitKey(100);

		//	adjustVelocityMagnitude();
		//	adjustVelocityDirection();

		//	//prev->setX(x_robot);
		//	//prev->setY(y_robot);
		//}

		counter++;
	}
}