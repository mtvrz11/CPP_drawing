/**
 * @file    SvgCanvas.h
 * @author  Matìj Tvrz
 * @date    10/2026
 * @brief   Deklarace tøídy SvgCanvas, která pøevádí interní reprezentací primitiv na formát svg.
 */

#pragma once
#include "ICanvas.h"
#include <fstream>

/// <summary>
/// platno pro vykreslovani ve formatu svg
/// </summary>
class SvgCanvas final : public ICanvas {
	std::ofstream file;

public:
	/// <summary>
	/// otevre cilovy soubor a vytvori svr platno o zadane velikosti
	/// </summary>
	/// <param name="filename">do jakeho souboru se ma ulozit textovy popis</param>
	/// <param name="w">sirka platna (v px)</param>
	/// <param name="h">vyska platna (v px)</param>
	/// <exception cref="std::runtime_exception">Vyhozena v pripade, ze se nepodari najit soubor</exception>
	SvgCanvas(const std::string& filename, int w, int h);

	/// <summary>
	/// ukonci svg kod a zavre cilovy soubor
	/// </summary>
	~SvgCanvas() override;

	void drawLine(double x1, double y1, double x2, double y2) override;

	void drawCircle(double cx, double cy, double r) override;
};