#pragma once

class Camera
{
private:
	float cx, cy;
	float cMinX, cMinY, cMaxX, cMaxY;
public:
	Camera();
	void move(float x, float y);
	void setPosition(float x, float y);
	float getX() { return cx; }
	float getY() { return cy; }
	void setBounds(float minX, float minY, float maxX, float maxY);
	float getMinX() { return cMinX; }
	float getMinY() { return cMinY; }
	float getMaxX() { return cMaxX; }
	float getMaxY() { return cMaxY; }
};

