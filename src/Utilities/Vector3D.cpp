// This file contains the definition of the class Vector3D

#include <math.h>

#include "Vector3D.h"
#include "Normal.h"
#include "Point3D.h"
#include <iostream> //Added by Joel for overloading << for cout

using namespace std;  //Added by Joel for overloading << for cout

// ---------------------------------------------------------- default constructor

Vector3D::Vector3D(void)
	 : x(0.0), y(0.0), z(0.0)							
{}

// ---------------------------------------------------------- constructor

Vector3D::Vector3D(double a)
	 : x(a), y(a), z(a)							
{}

// ---------------------------------------------------------- constructor

Vector3D::Vector3D(double _x, double _y, double _z)	 
	: x(_x), y(_y), z(_z)
{}

// ---------------------------------------------------------- copy constructor

Vector3D::Vector3D(const Vector3D& vector)
	: x(vector.x), y(vector.y), z(vector.z)
{}


// ---------------------------------------------------------- constructor
// constructs a vector from a normal

Vector3D::Vector3D(const Normal& n)	 
	: x(n.x), y(n.y), z(n.z)
{}

// ---------------------------------------------------------- constructor
// constructs a vector from a point
// this is used in the ConcaveHemisphere hit functions

Vector3D::Vector3D(const Point3D& p)	 
	: x(p.x), y(p.y), z(p.z)
{}


// ---------------------------------------------------------- destructor

Vector3D::~Vector3D (void) 							
{}



// ---------------------------------------------------------- assignment operator

Vector3D& 
Vector3D::operator= (const Vector3D& rhs) {
	if (this == &rhs)
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;

	return (*this);
}


// ----------------------------------------------------------- assignment operator
// assign a Normal to a vector

Vector3D& 
Vector3D::operator= (const Normal& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


// ---------------------------------------------------------- assignment operator 
// assign a point to a vector

Vector3D& 												
Vector3D::operator= (const Point3D& rhs) {
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


// ----------------------------------------------------------  length
// length of the vector

double													
Vector3D::length(void) {
	return (sqrt(x * x + y * y + z * z));
}


// ----------------------------------------------------------  normalize
// converts the vector to a unit vector

void 													
Vector3D::normalize(void) {	
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
}


// ----------------------------------------------------------  hat
// converts the vector to a unit vector and returns the vector

Vector3D& 													
Vector3D::hat(void) {	
	double length = sqrt(x * x + y * y + z * z);
	x /= length; y /= length; z /= length;
	return (*this);
} 


// non-member function

// ----------------------------------------------------------  operator* 
// multiplication by a matrix on the left

Vector3D 
operator* (const Matrix& mat, const Vector3D& v) {
	return (Point3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
					mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
					mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}


//Here, the << operation in the ostream class is being overloaded to also accept a Vector3D.
//Notice that this method is NOT Vector3D::. This is because this method is NOT part of the Vector3D class, it is
// being added to the ostream class.
// To tell the compiler to add this to the ostream class, 'friend' is used in Vector3D.h
//ostream& 
//operator<< (ostream &os, const Vector3D &v) {
//  os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
//  return os;
//}

//template <class T>
//auto operator<<(std::ostream &os, const T &t) -> decltype(t.print(os), os) {
//  t.print(os);
//return os;
//}
