#include "curves.h"

using namespace std;

Shape::Shape(double r, Point xy) : r_(r), xy_(xy) {}

Circle::Circle(double r, Point xy) : Shape(r, xy) {}

Point Circle::GetPoint(double t) const {					
	double x = r_ * cos(t) + xy_.x;
	double y = r_ * sin(t) + xy_.y;
	
	return { x, y };
}

Point Circle::GetDerivative(double t) const {				
	double x = r_ * sin(t);
	double y = r_ * cos(t);
	
	return { x, y };
}

bool Circle::operator<(const Circle& other) const {
	return r_ < other.r_;
}

double Circle::GetRadius() const {
	return r_;
}

Ellipse::Ellipse(double r, Point xy, double r2) : Shape(r, xy), r2_(r2) {}

Point Ellipse::GetPoint(double t) const {
	double x = r_ * cos(t) + xy_.x;
	double y = r2_ * sin(t) + xy_.y;

	return { x, y };
}
Point Ellipse::GetDerivative(double t) const {
	double x = r_ * sin(t);
	double y = r2_ * cos(t);

	return { x, y };
}

Helix::Helix(double r, Point xy, double step) : Shape(r, xy), step_(step) {}

Point Helix::GetPoint(double t) const {				
	double x = r_ * cos(t) + xy_.x;
	double y = r_ * sin(t) + xy_.y;
	double z = step_ * t / (2 * M_PI);
	
	return { x, y, z };
}

Point Helix::GetDerivative(double t) const {			
	double x = r_ * sin(t);
	double y = r_ * cos(t);
	double z = step_ / (2 * M_PI);
	
	return { x, y, z };
}
