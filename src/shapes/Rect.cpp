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

void Rect::draw(ICanvas& canvas) const {
	// obdelnik kreslim jako ctyri cary, aby se dal v svg vykreslovat i obdelnik, ktery neni zarovnany s osami
	canvas.drawLine(p1.x, p1.y, p2.x, p2.y);
	canvas.drawLine(p2.x, p2.y, p3.x, p3.y);
	canvas.drawLine(p3.x, p3.y, p4.x, p4.y);
	canvas.drawLine(p4.x, p4.y, p1.x, p1.y);
}