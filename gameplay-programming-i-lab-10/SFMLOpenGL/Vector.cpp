#include "Vector.h"



Vector::Vector()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector::Vector(float x1, float y1, float z1)
{
	x = x1;
	y = y1;
	z = z1;
}


Vector::~Vector()
{
}

void Vector::setX(float newX)
{
	x = newX;
}

void Vector::setY(float newY)
{
	y = newY;
}

void Vector::setZ(float newZ)
{
	z = newZ;
}

float Vector::getX()
{
	return x;
}

float Vector::getY()
{
	return y;
}

float Vector::getZ()
{
	return z;
}

float Vector::getLength()
{
	float length =(float)sqrt((x * x) + (y * y) + (z * z));
	return length;
}

float Vector::getLengthSquared()
{
	float length = (float)((x * x) + (y * y) + (z * z));
	return length;
}

void Vector::normalise()
{
	if (getLength() > 0.0)
	{  // Check for divide by zero
		float magnit = getLength();
		x = x / magnit;
		y = y / magnit;
		z = z / magnit;
	}
}

Vector Vector::operator +(Vector v2) const
{
	return Vector(x + v2.getX(), y + v2.getY(), z + v2.getZ());
}

Vector Vector::operator -(Vector v2) const
{
	return Vector(x - v2.getX(), y - v2.getY(), z - v2.getZ());
}

Vector Vector::operator -() const
{
	Vector v1 = Vector();
	v1.setX(-x);
	v1.setY(-y);
	v1.setZ(-z);
	return v1;
}

double Vector::operator *(Vector v2) const
{
	return (x * v2.getX() + y * v2.getY() + z * v2.getZ());
}

Vector Vector::operator *(double k) const
{
	return Vector(x * (float)k, y * (float)k, z * (float)k);
}

Vector Vector::operator *(float k) const
{
	return Vector(x * k, y * k, z * k);
}

Vector Vector::operator *(int k) const
{
	return Vector(x * k, y * k, z * k);
}

Vector Vector::operator ^(Vector v2) const
{
	return Vector(y * v2.getZ() - z * v2.getY(), z * v2.getX() - x * v2.getZ(), x * v2.getY() - y * v2.getX());
}