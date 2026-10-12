/**
 * @file    Line.cpp
 * @author  Matìj Tvrz
 * @date    10/2026
 * @brief   Implementace metod tøídy Line.
 */

#include "Line.h"

Line::Line(double x1, double y1, double x2, double y2)
	: p1{ x1, y1 }, p2{ x2, y2 }
{
}

void Line::transform(const Matrix3x3& m) {
	p1 = m * p1;
	p2 = m * p2;
}

void Line::draw(ICanvas& canvas) const {
	canvas.drawLine(p1.x, p1.y, p2.x, p2.y);
}