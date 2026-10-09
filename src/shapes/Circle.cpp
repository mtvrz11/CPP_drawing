#include "Circle.h"
#include <cmath>

Circle::Circle(double cx, double cy, double r)
	: center{ cx, cy }, radius(r)
{
}

void Circle::transform(const Matrix3x3& m) {

	// pomocny bod pro spravne chovani vsech transformaci vcetne scale - obecne reseni
	// (pri scale je potreba menit i polomer, pri ostatnich transformacich jen stred)
	Point tmp{ center.x + radius, center.y };
	tmp = m * tmp;
	center = m * center;

	// vypocet vzdalenosti pomocneho bodu na obvodu od stredu kruznice
	radius = std::sqrt((tmp.x - center.x) * (tmp.x - center.x) + (tmp.y - center.y) * (tmp.y - center.y));
}

void Circle::draw(Canvas& canvas) const {

}