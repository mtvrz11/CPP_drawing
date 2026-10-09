#pragma once

/// <summary>
/// struktura reprezentujici bod ve 2D v homogennich souradnicich (jako sloupcovy vektor)
/// </summary>
struct Point {
	double x, y, w = 1.0;
};

/// <summary>
/// trida reprezentujici matici o rozmerech 3x3
/// </summary>
class Matrix3x3 {

	/// <summary>
	/// data matice M - M(i, j) = data[i][j]
	/// </summary>
	double data[3][3];

public:
	/// <summary>
	/// konstruktor vytvori novou JEDNOTKOVOU matici 3x3
	/// </summary>
	Matrix3x3();

	/// <summary>
	/// pretizeni operatoru funkcniho volani pro zapis
	/// </summary>
	/// <param name="row">index radku matice</param>
	/// <param name="col">index sloupce matice</param>
	/// <returns>reference na cislo na dane pozici</returns>
	double& operator()(int row, int col);

	/// <summary>
	/// pretizeni operatoru funkcniho volani pro cteni
	/// </summary>
	/// <param name="row">index radku matice</param>
	/// <param name="col">index sloupce matice</param>
	/// <returns>reference na cislo na dane pozici</returns>
	const double& operator()(int row, int col) const;

	/// <summary>
	/// vytvori a vrati matici translace o zadany vektor
	/// </summary>
	/// <param name="tx">posun v ose x</param>
	/// <param name="ty">posun v ose y</param>
	/// <returns>nova matice translace</returns>
	static Matrix3x3 createTranslation(double tx, double ty);

	/// <summary>
	/// vytvori a vrati matici rotace zadany uhel podle zadaneho stredu
	/// </summary>
	/// <param name="cx">x-ova souradnice stredu</param>
	/// <param name="cy">y-ova souradnice stredu</param>
	/// <param name="a">uhel VE STUPNICH - kladny smer otaceni proti smeru hodinovych rucicek</param>
	/// <returns>nova matice rotace</returns>
	static Matrix3x3 createRotation(double cx, double cy, double a);

	/// <summary>
	/// vytvori a vrati matici scale zadanym faktorem podle zadaneho stredu
	/// </summary>
	/// <param name="cx">x-ova souradnice stredu</param>
	/// <param name="cy">y-ova souradnice stredu</param>
	/// <param name="f">faktor</param>
	/// <returns>nova matice scale</returns>
	static Matrix3x3 createScale(double cx, double cy, double f);

};

/// <summary>
/// pretizeni operatoru * pro nasobeni bodu matici zleva
/// </summary>
/// <param name="matrix">matice, kterou se ma nasobit</param>
/// <param name="point">bod (vektor), ktery ma byt vynasoben</param>
/// <returns>novy bod vznikly soucinem</returns>
Point operator*(const Matrix3x3& matrix, const Point& point);

/// <summary>
/// pretizeni operatoru * pron asobeni dvou matic v danem poradi
/// </summary>
/// <param name="m1">matice vlevo</param>
/// <param name="m2">matice vpravo</param> 
/// <returns>nova matice vznikla jako soucin dvou zadanych</returns>
Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2);