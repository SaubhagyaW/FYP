#include "SideBySidePersonFollowing.h"

using namespace cv;
using namespace std;

double SideBySidePersonFollowing::calculateX(double distance, double angle)
{
	double displacement = prev->getVelocityMagnitude() * 1 / fps;
	double x = displacement * sin(prev->getVelocityDirection()) + distance * cos(angle);

	return x;
}

double SideBySidePersonFollowing::calculateY(double distance, double angle)
{
	double displacement = prev->getVelocityMagnitude() * 1 / fps;
	double y = displacement * cos(prev->getVelocityDirection()) + distance + sin(angle);

	return y;
}

void SideBySidePersonFollowing::adjustVelocityMagnitude(double angle)
{
	if (angle > 0 && angle > offsetAngle)
	{
		curr->setVelocityMagnitude(curr->getVelocityMagnitude() - offsetVelocityMagnitude);
	}
	else if (angle < 0 && angle < offsetAngle)
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

void SideBySidePersonFollowing::draw(System::Windows::Forms::PictureBox^ img, Mat canvas) {
	System::Drawing::Graphics^ graphics2 = img->CreateGraphics();
	System::IntPtr ptr2(canvas.ptr());
	System::Drawing::Bitmap^ b2 = gcnew System::Drawing::Bitmap(canvas.cols,
		canvas.rows, canvas.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr2);
	System::Drawing::RectangleF rect2(0, 0, img->Width, img->Height);
	graphics2->DrawImage(b2, rect2);
	System::Threading::Thread::Sleep(System::TimeSpan::FromMilliseconds(100));
}

void SideBySidePersonFollowing::follow(double distance, double angle, int counter, Mat canvas, System::Windows::Forms::PictureBox^ paths)
{
	// x, y coordinates are relative to (0, 0) point which is the starting point of the robot
	// Scale: 1m is represented by 1 units
	double x, y, x_robot, y_robot;

	if (counter == 0)
	{
		x = distance * cos(angle);
		y = distance * sin(angle);
		prev = new Position(x, y, startVelocity);

		prevDistance = distance;

		circle(canvas, Point(x * 10, y * 10), 2, CV_RGB(0, 0, 255), 2);
		draw(paths, canvas);
	}
	else if (counter == 1)
	{
		if (distance < (prevDistance + 5) && distance > (prevDistance - 5))
		{
			x = distance * cos(angle);
			y = distance * sin(angle);
			curr = new Position(x, y, startVelocity);
			curr->setVelocityDirection(calculateVelocityDirection());

			prevDistance = distance;

			circle(canvas, Point(x * 10, y * 10), 2, CV_RGB(0, 0, 255), 2);
			draw(paths, canvas);
		}
		else {
			counter--;
		}
	}
	else
	{
		prev->setX(curr->getX());
		prev->setY(curr->getY());
		prev->setVelocityMagnitude(curr->getVelocityMagnitude());
		prev->setVelocityDirection(curr->getVelocityDirection());

		if (distance < (prevDistance + 5) && distance > (prevDistance - 5))
		{
			x = calculateX(distance, angle);
			curr->setX(x);
			y = calculateY(distance, angle);
			curr->setY(y);
			adjustVelocityMagnitude(angle);
			adjustVelocityDirection(calculateVelocityDirection());

			prevDistance = distance;
		}

		circle(canvas, Point(x * 10, y * 10), 2, CV_RGB(0, 0, 255), 2);
		draw(paths, canvas);

		x_robot = (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
		y_robot = (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());
		circle(canvas, Point(x_robot * 10, y_robot * 10), 2, CV_RGB(0, 255, 0), 2);
		draw(paths, canvas);
	}
}