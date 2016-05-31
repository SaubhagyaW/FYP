#include "Position.h"

Position::Position(double velocityMagnitude, double velocityDeirection)
{
	Position::velocityMagnitude = velocityMagnitude;
	Position::velocityDirection = velocityDeirection;
}

Position::Position(double x, double y, double velocityMagnitude)
{
	Position::x = x;
	Position::y = y;
	Position::velocityMagnitude = velocityMagnitude;
}

double Position::getX()
{
	return x;
}

void Position::setX(double x)
{
	Position::x = x;
}

double Position::getY()
{
	return y;
}

void Position::setY(double y)
{
	Position::y = y;
}

double Position::getVelocityMagnitude()
{
	return velocityMagnitude;
}

void Position::setVelocityMagnitude(double velocityMagnitude)
{
	Position::velocityMagnitude = velocityMagnitude;
}

double Position::getVelocityDirection()
{
	return velocityDirection;
}

void Position::setVelocityDirection(double velocityDirection)
{
	Position::velocityDirection = velocityDirection;
}