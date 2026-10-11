#pragma once

#include "ICanvas.h"

#include <vector>
#include <string>
#include <cstdint>
#include <fstream>

/// <summary>
/// platno pro vykresleni ve formatu pgm
/// </summary>
class PgmCanvas : public ICanvas {
	int width, height;
	std::vector<uint8_t> pixels;
	std::ofstream file; // vystupni soubor

	/// <summary>
	/// nastavi pixel na danych souradnicich v obrazku na danou barvu, provadi orez na velikost platna - vse mimo platno ignoruje
	/// </summary>
	/// <param name="x">x-ova souradnice pixelu</param>
	/// <param name="y">y-ova souradnice pixelu</param>
	/// <param name="color">barva</param>
	void setPixel(int x, int y, uint8_t color);

public:
	/// <summary>
	/// otevre soubor pro zapis, vytvori pole pixelu o velikosti obrazku nastavenych na bilou barvu, vytvori hlavicku pro pgm format
	/// </summary>
	/// <param name="filename">nazev ciloveho souboru</param>
	/// <param name="w">sirka obrazku</param>
	/// <param name="h">vyska obrazku</param>
	PgmCanvas(const std::string filename, int w, int h);

	/// <summary>
	/// vypise vektor pixelu do ciloveho souboru a zavre soubor
	/// </summary>
	~PgmCanvas() override;

	/// <summary>
	/// rasterizuje usecku a obarvi prislusne pixely ve vektoru pixelu
	/// </summary>
	/// <param name="x1">x-ova souradnice pocatecniho bodu</param>
	/// <param name="y1">y-ova souradnice pocatecniho bodu</param>
	/// <param name="x2">x-ova souradnice koncoveho bodu</param>
	/// <param name="y2">y-ova souradnice koncoveho bodu</param>
	void drawLine(double x1, double y1, double x2, double y2) override;

	/// <summary>
	/// rasterizuje kruznici danych parametru a obarvi prislusne pixely ve vektoru pixelu
	/// </summary>
	/// <param name="cx">x-ova souradnice stredu</param>
	/// <param name="cy">y-ova souradnice stredu</param>
	/// <param name="r">polomer</param>
	void drawCircle(double cx, double cy, double r) override;
};