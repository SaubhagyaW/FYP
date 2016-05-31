#pragma once

#include "PersonFollowing.h"

class BackPersonFollowing : public PersonFollowing
{
private:
	double x, y, x_robot, y_robot;

	void adjustVelocityMagnitude(double);
	void adjustVelocityDirection(double);
	void draw(System::Windows::Forms::PictureBox^, cv::Mat);

public:
	const double maxOffsetDistance = 5; //metres
	const double minOffsetDistance = 2;

	void follow(double, double, int, cv::Mat, System::Windows::Forms::PictureBox^);
};