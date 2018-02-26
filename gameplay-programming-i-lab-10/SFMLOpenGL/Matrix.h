#pragma once
#include "Vector.h"
#include <cmath>
class Matrix
{
public:
	const double PI = acos(-1);
	Matrix();
	Matrix(Vector Row1, Vector Row2, Vector Row3);
	Matrix(double newA11, double newA12, double newA13,
		double newA21, double newA22, double newA23,
		double newA31, double newA32, double newA33);
	~Matrix();
	void setA11(double newA11);
	void setA12(double newA12);
	void setA13(double newA13);
	void setA21(double newA21);
	void setA22(double newA22);
	void setA23(double newA23);
	void setA31(double newA31);
	void setA32(double newA32);
	void setA33(double newA33);

	double getA11();
	double getA12();
	double getA13();
	double getA21();
	double getA22();
	double getA23();
	double getA31();
	double getA32();
	double getA33();

	Vector operator *(Vector V1) const;
	Matrix Transpose(Matrix M1);
	Matrix operator +(Matrix M2) const;
	Matrix operator -(Matrix M2) const;
	Matrix operator *(double x) const;
	Matrix operator *(Matrix M2);
	double Determinant(Matrix M1);
	Vector Row(int i);
	Vector Column(int i);
	Matrix Inverse(Matrix M1);
	Matrix Rotation(int _angle);
	Matrix Translate(int dx, int dy);
	Matrix Scale(int dx, int dy);
	Matrix operator -(Matrix M1);
	Matrix RotationX(int _angle);
	Matrix RotationY(int _angle);
	Matrix RotationZ(int _angle);
	Matrix Scale3D(int dx);
	
protected:
	double A11;
	double A12;
	double A13;
	double A21;
	double A22;
	double A23;
	double A31;
	double A32;
	double A33;
};

