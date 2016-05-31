#pragma once

#include "PersonFollowing.h"

class SideBySidePersonFollowing : public PersonFollowing
{
	Position* curr;

	double calculateX(double, double);
	double calculateY(double, double);
	void adjustVelocityMagnitude(double);
	double calculateVelocityDirection();
	void adjustVelocityDirection(double);
	void draw(System::Windows::Forms::PictureBox^, cv::Mat);

public:
	const double offsetAngle = M_PI / 6; // degrees

	void follow(double, double, int, cv::Mat, System::Windows::Forms::PictureBox^);
};