#include "Math.h"
#include <cmath>

Matrix3x3::Matrix3x3() {
	// vytvoreni jednotkove matice
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				data[i][j] = 1;
			}
			else {
				data[i][j] = 0;
			}
		}
	}
}

double& Matrix3x3::operator()(int row, int col) {
	return data[row][col];
}

const double& Matrix3x3::operator()(int row, int col) const {
	return data[row][col];
}

Matrix3x3 Matrix3x3::createTranslation(double tx, double ty) {
	Matrix3x3 translation;
	translation(0, 2) = tx;
	translation(1, 2) = ty;
	return translation;
}

Matrix3x3 Matrix3x3::createRotation(double cx, double cy, double a) {
	// posun pocatku souradneho systemu do zadaneho stredu
	Matrix3x3 to_origin = createTranslation(-cx, -cy);

	// prevod stupnu na radiany
	double pi = 2 * asin(1.0);
	double a_rad = (a / 180.0) * pi;

	// vytvoreni matice rotace
	Matrix3x3 rot;
	rot(0, 0) = cos(a_rad);
	rot(0, 1) = -sin(a_rad);
	rot(1, 0) = sin(a_rad);
	rot(1, 1) = cos(a_rad);

	// posun souradneho systemu zpet do puvodni pozice
	Matrix3x3 back = createTranslation(cx, cy);

	// slozeni matic
	return back * rot * to_origin;

}

Matrix3x3 Matrix3x3::createScale(double cx, double cy, double f) {
	// posun pocatku souradneho systemu do zadaneho stredu
	Matrix3x3 to_origin = createTranslation(-cx, -cy);

	// vytvoreni matice scale
	Matrix3x3 scale;
	scale(0, 0) = f;
	scale(1, 1) = f;

	// posun souradneho systemu zpet na puvodni pozici
	Matrix3x3 back = createTranslation(cx, cy);

	// slozeni matic
	return back * scale * to_origin;
}

Point operator*(const Matrix3x3& matrix, const Point& point) {
	Point result;
	result.x = point.x * matrix(0, 0) + point.y * matrix(0, 1) + point.w * matrix(0, 2);
	result.y = point.x * matrix(1, 0) + point.y * matrix(1, 1) + point.w * matrix(1, 2);
	result.w = point.x * matrix(2, 0) + point.y * matrix(2, 1) + point.w * matrix(2, 2);
	return result;
}

Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2) {
	Matrix3x3 result;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; i < 3; i++) {
			result(i, j) = m1(i, 0) * m2(0, j) + m1(i, 1) * m2(1, j) + m1(i, 2) * m2(2, j);
		}
	}

	return result;
}