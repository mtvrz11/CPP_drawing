#pragma once
#include "IShape.h"

/// <summary>
/// trida pro reprezentaci usecky ve 2D - dedi od rozhrani IShape
/// </summary>
class Line : public IShape {
	Point p1;
	Point p2;

public:
	/// <summary>
	/// vytvori usecku naplnenim jejich dvou bodu
	/// </summary>
	/// <param name="x1">x-ova souradnice pocatecniho bodu</param>
	/// <param name="y1">y-ova souradnice pocatecniho bodu</param>
	/// <param name="x2">x-ova souradnice koncoveho bodu</param>
	/// <param name="y2">y-ova souradnice koncoveho bodu</param>
	Line(double x1, double y1, double x2, double y2);

	void transform(const Matrix3x3& m) override;
	
	void draw(Canvas& canvas) const override;
};