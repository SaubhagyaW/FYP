#pragma once
#include "PersonFollowing.h"

class SideBySidePersonFollowing : public PersonFollowing
{
	Position* curr;

	double calculateX();
	double calculateY();
	void adjustVelocityMagnitude();
	double calculateVelocityDirection();
	void adjustVelocityDirection(double);

public:
	const double offsetAngle = M_PI / 6; // degrees

	void follow();
};