#include "SideBySidePersonFollowing.h"
#include <iostream>
#include <fstream>
#include "opencv/cv.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

double SideBySidePersonFollowing::calculateX()
{
	double displacement = prev->getVelocityMagnitude() * 1 / fps;
	double x = displacement * sin(prev->getVelocityDirection()) + distance * cos(angle);

	return x;
}

double SideBySidePersonFollowing::calculateY()
{
	double displacement = prev->getVelocityMagnitude() * 1 / fps;
	double y = displacement * cos(prev->getVelocityDirection()) + distance + sin(angle);

	return y;
}

void SideBySidePersonFollowing::adjustVelocityMagnitude()
{
	if (angle > 0  && angle > offsetAngle)
	{
		curr->setVelocityMagnitude(curr->getVelocityMagnitude() - offsetVelocityMagnitude);
	}
	else if (angle < 0  && angle < offsetAngle)
	{
		curr->setVelocityMagnitude(curr->getVelocityMagnitude() + offsetVelocityMagnitude);
	}
}

double SideBySidePersonFollowing::calculateVelocityDirection()
{
	double velocityDirection = atan((curr->getX() - prev->getX()) / (curr->getY() - prev->getY())); // radians
	return velocityDirection;
}

void SideBySidePersonFollowing::adjustVelocityDirection(double velocityDirection)
{
	if (curr->getVelocityDirection() > 0) {
		if (curr->getVelocityDirection() > (prev->getVelocityDirection() + offsetVelocityDirection)) {
			curr->setVelocityDirection(velocityDirection);
		}
	}
	else if (curr->getVelocityDirection() < 0) {
		if (curr->getVelocityDirection() > (prev->getVelocityDirection() - offsetVelocityDirection)) {
			curr->setVelocityDirection(velocityDirection);
		}
	}
}

void SideBySidePersonFollowing::follow()
{
	int counter = 0;

	// x, y coordinates are relative to (0, 0) point which is the starting point of the robot
	// Scale: 1m is represented by 1 unit
	double x, y, x_robot, y_robot;

	Mat canvas = Mat::zeros(800, 800, CV_8UC3);
	canvas = cv::Scalar(255, 255, 255);

	ifstream dataFile("input.txt");

	// Side-by-side person-following loop
	while (dataFile >> distance >> angle)
	{
		if (counter == 0)
		{
			x = distance * cos(angle);
			y = distance * sin(angle);
			prev = new Position(x, y, startVelocity);

			prevDistance = distance;

			circle(canvas, Point(x * 10, y * 10), 2, CV_RGB(0, 0, 255), 2);
			imshow("canvas", canvas);
			waitKey(100);
		}
		else if (counter == 1)
		{
			x = distance * cos(angle);
			y = distance * sin(angle);
			curr = new Position(x, y, startVelocity);
			curr->setVelocityDirection(calculateVelocityDirection());

			circle(canvas, Point(x * 10, y * 10), 2, CV_RGB(0, 0, 255), 2);
			imshow("canvas", canvas);
			waitKey(100);
		}
		else
		{
			prev->setX(curr->getX());
			prev->setY(curr->getY());
			prev->setVelocityMagnitude(curr->getVelocityMagnitude());
			prev->setVelocityDirection(curr->getVelocityDirection());

			//if (distance > (prevDistance + 5) || distance < (prevDistance - 5))
			//{
			//	x += prevDistance * sin(angle);
			//	y += prevDistance * cos(angle);
			//}
			//else
			//{
				x = calculateX();
				curr->setX(x);
				y = calculateY();
				curr->setY(y);
				adjustVelocityMagnitude();
				adjustVelocityDirection(calculateVelocityDirection());

				prevDistance = distance;
			//}

			circle(canvas, Point(x * 10, y * 10), 2, CV_RGB(0, 0, 255), 2);
			imshow("canvas", canvas);
			waitKey(100);

			x_robot = (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
			y_robot = (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());
			circle(canvas, Point(x_robot * 10, y_robot * 10), 2, CV_RGB(0, 255, 0), 2);
			imshow("canvas", canvas);
			waitKey(100);
		}

		counter++;
	}
}