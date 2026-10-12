/**
 * @file    ICanvas.h
 * @author  Matìj Tvrz
 * @date    10/2026
 * @brief   Deklarace rozhraní ICanvas, které deklaruje požadované funkce pro obecné plátno.
 */

#pragma once

/// <summary>
/// reprezentuje platno na ktere lze vykreslovat cary a kruznice
/// </summary>
class ICanvas {
public:
	/// <summary>
	/// virtualni destruktor
	/// </summary>
	virtual ~ICanvas() = default;

	/// <summary>
	/// vykresli na platno caru podle zadanych parametru
	/// </summary>
	/// <param name="x1">x-ova souradnice pocatecniho bodu</param>
	/// <param name="y1">y-ova souradnice pocatecniho bodu</param>
	/// <param name="x2">x-ova souradnice koncoveho bodu</param>
	/// <param name="y2">y-ova souradnice koncoveho bodu</param>
	virtual void drawLine(double x1, double y1, double x2, double y2) = 0;

	/// <summary>
	/// vykresli na platno kruh podle zadanych parametru
	/// </summary>
	/// <param name="cx">x-ova souradnice stredu</param>
	/// <param name="cy">y-ova souradnice stredu</param>
	/// <param name="r">polomer</param>
	virtual void drawCircle(double cx, double cy, double r) = 0;
};