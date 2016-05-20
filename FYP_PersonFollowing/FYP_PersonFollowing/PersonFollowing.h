#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Position.h"

class PersonFollowing
{
protected:
	double distance; // metres
	double angle; // radians
	double prevDistance;

	Position* prev;

public:
	const int fps = 10;
	const double startVelocity = 5;
	const double offsetVelocityMagnitude = 5; // metres per second
	const double offsetVelocityDirection = M_PI / 3; // radians
};