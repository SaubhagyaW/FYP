#pragma once
#include "PersonFollowing.h"

class BackPersonFollowing : public PersonFollowing
{
	void adjustVelocityMagnitude();
	void adjustVelocityDirection();

public:
	const double maxOffsetDistance = 5; //metres
	const double minOffsetDistance = 2;

	void follow();
};