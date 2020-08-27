#include "Camera.h"

Camera::Camera()
{
	cx = 0;
	cy = 0;
	cMinX = 0;
	cMinY = 0;
	cMaxX = 0;
	cMaxY = 0;
}

void Camera::move(float x, float y)
{
	cx += x;
	cy += y;
}

void Camera::setPosition(float x, float y)
{
	if (x < cMinX)
		cx = cMinX;
	else if (x > cMaxX)
		cx = cMaxX;
	else
		cx = x;
	if (y < cMinY)
		cy = cMinY;
	else if (y > cMaxY)
		cy = cMaxY;
	else
		cy = y;
}

void Camera::setBounds(float minX, float minY, float maxX, float maxY)
{
	cMinX = minX;
	cMinY = minY;
	cMaxX = maxX;
	cMaxY = maxY;
}