#include "curves.h"

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <future>
#include <numeric>

using namespace std;

inline int COUNT_CURVES = 50;
inline int SEQ_SIZE = 1000;

enum CurveType {
	CIRCLE,
	ELLIPSE,
	HELIX
};

ostream& operator<<(ostream& os, const Point& point) {
	return os << "{ " << point.x << " " << point.y << " " << point.z << " }";
}

struct Sum
{
	void operator()(shared_ptr<Circle>& circle) { sum += circle->GetRadius(); }
	double sum = 0.;
};

template <typename RandomIt>
double parallel_sum(RandomIt beg, RandomIt end)
{
	auto len = end - beg;
	if (len < SEQ_SIZE) {
		Sum s = for_each(beg, end, Sum());
		return s.sum;
	}

	RandomIt mid = beg + len / 2;
	auto handle = async(launch::async, parallel_sum<RandomIt>, mid, end);
	double sum = parallel_sum(beg, mid);
	return sum + handle.get();
}

int main() {
	random_device rd;
	mt19937 mt(rd());	
	vector<shared_ptr<Shape>> shapes;			
	vector<shared_ptr<Circle>> circles;		

	for (int i = 0; i < COUNT_CURVES; ++i) {
		uniform_int_distribution<> dist_int(0, 2);
		uniform_real_distribution<> dist_real(-50., 50.);	
		switch (dist_int(mt)) {
			case CIRCLE:
			{
				auto ptr = make_shared<Circle>(abs(dist_real(mt)), Point{ dist_real(mt), dist_real(mt) });
				shapes.emplace_back(ptr);
				circles.emplace_back(ptr);
				break;
			}
			case ELLIPSE:
			{
				auto ptr = make_shared<Ellipse>(abs(dist_real(mt)), Point{ dist_real(mt), dist_real(mt) }, abs(dist_real(mt)));
				shapes.emplace_back(ptr);
				break;
			}
			case HELIX:
			{
				auto ptr = make_shared <Helix>(abs(dist_real(mt)), Point{ dist_real(mt), dist_real(mt) }, abs(dist_real(mt)));
				shapes.emplace_back(ptr);
				break;
			}
		}
	}
	// Print coordinates of points and derivatives of all curves in the container at t=PI/4
	double t =  M_PI / 4;
	for (const auto& shape : shapes) {
		std::cout << "Point: " << shape->GetPoint(t) << " Derivative: " << shape->GetDerivative(t) << endl;

	}
	// Sort the Circles container in the ascending order of circles’ radii
	sort(circles.begin(), circles.end());
	
	// Compute the total sum of radii of all curves in the Circles container
	double circlesRadiusSum = parallel_sum(circles.begin(), circles.end());
	
	return 0;
}