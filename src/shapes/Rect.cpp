#include "Rect.h"

Rect::Rect(double x, double y, double w, double h)
	: p1{ x, y }, p2{ x + w, y }, p3{ x + w, y + h }, p4{ x, y + h }
{
}

void Rect::transform(const Matrix3x3& m) {
	p1 = m * p1;
	p2 = m * p2;
	p3 = m * p3;
	p4 = m * p4;
}

void Rect::draw(Canvas& canvas) const {

}