#pragma once
#include <cmath>
class Vector
{
public:
	Vector();
	Vector(float x1, float y1, float z1);
	~Vector();
	void setX(float newX);
	void setY(float newY);
	void setZ(float newZ);
	float getX();
	float getY();
	float getZ();
	float getLength();
	float getLengthSquared();
	void normalise();
	Vector operator +(Vector v2) const;
	Vector operator -(Vector v2) const;
	Vector operator -() const;
	double operator *(Vector v2) const;
	Vector operator *(double k) const;
	Vector operator *(float k) const;
	Vector operator *(int k) const;
	Vector operator ^(Vector v2) const;
protected:
	float x;
	float y;
	float z;
};

