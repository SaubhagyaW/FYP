#pragma once

#include "opencv/cv.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <list>
#include <msclr\marshal_cppstd.h>

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
const std::string videoPath = "G:/Final Year Project/Prototype/dataset/dataset3.avi";

CvPoint2D32f* featuresArray;
int* heightFromFloor;
int numOfFeatures;

cv::VideoCapture cap;
int screenWidth, screenHeight;
cv::Mat currentFrame, currentFrameCopy, nextFrame;
std::vector<cv::Rect> found, foundFiltered;
CvPoint2D32f* trackedFeatures;

void validateFrame(cv::Mat frame);
void findFeatures(cv::Mat currentFrame, cv::Rect rect);
int personFloor(bool & status);
int scaledPersonFloor(bool &status);
double computeDistance(double v);
double computeAngle();
void configure();
void draw(System::Windows::Forms::PictureBox^ video);
void detectPeople(System::Windows::Forms::PictureBox^ video);
void validate(int personIndex, System::Windows::Forms::PictureBox^ video);
int trackPerson(double distance, double angle, System::Windows::Forms::PictureBox^ video);