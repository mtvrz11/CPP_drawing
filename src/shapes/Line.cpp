#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2)
	: p1{ x1, y1 }, p2{ x2, y2 }
{
}

void Line::transform(const Matrix3x3& m) {
	p1 = m * p1;
	p2 = m * p2;
}

void Line::draw(Canvas& canvas) const {

}