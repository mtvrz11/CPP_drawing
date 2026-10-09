#pragma once
#include "IShape.h"

/// <summary>
/// trida pro reprezentaci kruhu pomoci stredu a polomeru
/// </summary>
class Circle : public IShape {
	Point center;
	double radius;

public:
	/// <summary>
	/// vytvori novy kruh ve 2D
	/// </summary>
	/// <param name="cx">x-ova souradnice stredu</param>
	/// <param name="cy">y-ova souradnice stredu</param>
	/// <param name="r">polomer</param>
	Circle(double cx, double cy, double r);

	void transform(const Matrix3x3& m) override;

	void draw(Canvas& canvas) const override;
};