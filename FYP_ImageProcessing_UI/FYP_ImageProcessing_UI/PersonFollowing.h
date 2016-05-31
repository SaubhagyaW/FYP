#pragma once

#define _USE_MATH_DEFINES

#include "Position.h"
#include <math.h>
#include "opencv/cv.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

class PersonFollowing
{
protected:
	double prevDistance;

	Position* prev;

public:
	const int fps = 10;
	const double startVelocity = 5;
	const double offsetVelocityMagnitude = 5; // metres per second
	const double offsetVelocityDirection = M_PI / 3; // radians
};