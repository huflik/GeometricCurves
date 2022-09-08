#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

struct Point {
	double x;
	double y;
	double z = 0.;
};

class Shape {
public:
	explicit Shape(double r, Point xy);
	virtual Point GetPoint(double t) const = 0;
	virtual Point GetDerivative(double t) const = 0;
	virtual ~Shape() = default;

protected:
	double r_;
	Point xy_;
};

class Circle : public Shape {
public:
	explicit Circle(double r, Point xy);
	Point GetPoint(double t) const override;					
	Point GetDerivative(double t) const override;					
	bool operator<(const Circle& other) const;
	double GetRadius() const;
};

class Ellipse : public Shape {
public:
	explicit Ellipse(double r, Point xy, double r2);
	Point GetPoint(double t) const override;
	Point GetDerivative(double t) const override;

private:
	double r2_;
};

class Helix : public Shape {
public:
	explicit Helix(double r, Point xy, double step);
	Point GetPoint(double t) const override;
	Point GetDerivative(double t) const override;

private:
	double step_;
};



