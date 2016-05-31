#include "BackPersonFollowing.h"

using namespace cv;
using namespace std;

void BackPersonFollowing::adjustVelocityMagnitude(double distance)
{
	if (distance > maxOffsetDistance)
	{
		prev->setVelocityMagnitude(prev->getVelocityMagnitude() + offsetVelocityMagnitude);
	}
	else if (distance < minOffsetDistance)
	{
		prev->setVelocityMagnitude(prev->getVelocityMagnitude() - offsetVelocityMagnitude);
	}
}

void BackPersonFollowing::adjustVelocityDirection(double angle)
{
	if (angle > 0) {
		if (angle > (prev->getVelocityDirection() + offsetVelocityDirection)) {
			prev->setVelocityDirection(angle);
		}
	}
	else if (angle < 0) {
		if (angle > (prev->getVelocityDirection() - offsetVelocityDirection)) {
			prev->setVelocityDirection(angle);
		}
	}
}

void BackPersonFollowing::draw(System::Windows::Forms::PictureBox^ img, Mat canvas) {
	System::Drawing::Graphics^ graphics2 = img->CreateGraphics();
	System::IntPtr ptr2(canvas.ptr());
	System::Drawing::Bitmap^ b2 = gcnew System::Drawing::Bitmap(canvas.cols,
		canvas.rows, canvas.step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr2);
	System::Drawing::RectangleF rect2(0, 0, img->Width, img->Height);
	graphics2->DrawImage(b2, rect2);
	System::Threading::Thread::Sleep(System::TimeSpan::FromMilliseconds(100));
}

void BackPersonFollowing::follow(double distance, double angle, int counter, Mat canvas, System::Windows::Forms::PictureBox^ paths)
{
	if (counter == 0)
	{
		prev = new Position(startVelocity, angle);
		prevDistance = distance;

		x = 500 + distance * sin(angle);
		y = distance * cos(angle);
		x_robot = 500;
		y_robot = 0;
		circle(canvas, Point(x + 50, y + 50), 2, CV_RGB(0, 0, 255), 2);
		draw(paths, canvas);
		circle(canvas, Point(x_robot + 50, y_robot + 50), 2, CV_RGB(0, 255, 0), 2);
		draw(paths, canvas);
	}
	else
	{
		if (distance > (prevDistance + 5) || distance < (prevDistance - 5))
		{
			x += prevDistance * sin(angle);
			y += prevDistance * cos(angle);

			x_robot += (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
			y_robot += (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());
		}
		else
		{
			x += distance * sin(angle);
			y += distance * cos(angle);

			x_robot += (prev->getVelocityMagnitude() * 1 / fps) * sin(prev->getVelocityDirection());
			y_robot += (prev->getVelocityMagnitude() * 1 / fps) * cos(prev->getVelocityDirection());

			adjustVelocityMagnitude(distance);
			adjustVelocityDirection(angle);

			prevDistance = distance;
		}

		circle(canvas, Point(x + 50, y + 50), 2, CV_RGB(0, 0, 255), 2);
		draw(paths, canvas);
		circle(canvas, Point(x_robot + 50, y_robot + 50), 2, CV_RGB(0, 255, 0), 2);
		draw(paths, canvas);
	}
}