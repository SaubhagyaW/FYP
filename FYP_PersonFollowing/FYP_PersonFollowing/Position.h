#pragma once

class Position
{
	double x;
	double y;
	double velocityMagnitude;
	double velocityDirection;

public:
	Position(double, double);
	Position(double, double, double);

	double getX();
	void setX(double);
	double getY();
	void setY(double);
	double getVelocityMagnitude();
	void setVelocityMagnitude(double);
	double getVelocityDirection();
	void setVelocityDirection(double);
};