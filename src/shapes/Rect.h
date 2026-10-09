#pragma once
#include "IShape.h"

/// <summary>
/// trida pro reprezentaci obdelniku ve 2D pomoci jeho ctyr vrcholu
/// </summary>
class Rect : public IShape {
	Point p1;
	Point p2;
	Point p3;
	Point p4;

public:
	/// <summary>
	/// vytvori novy obdelnik
	/// </summary>
	/// <param name="x">x-ova souradnice leveho horniho vrcholu</param>
	/// <param name="y">y-ova souradnice leveho horniho vrcholu</param>
	/// <param name="w">sirka obdelniku</param>
	/// <param name="h">vyska obdelnihu</param>
	Rect(double x, double y, double w, double h);

	void transform(const Matrix3x3& m) override;

	void draw(Canvas& canvas) const override;
};