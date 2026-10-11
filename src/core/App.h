#pragma once

#include <vector>
#include <memory>
#include <string>

#include "../shapes/IShape.h"
#include "../math/Math.h"

/// <summary>
/// trida pro zpracovani vstupnich dat a drzeni vnitrniho stavu aplikace
/// </summary>
class App {
	/// <summary>
	/// vektor obsahujici vsechny tvary nakresu
	/// </summary>
	std::vector<std::unique_ptr<IShape>> shapes;

	/// <summary>
	/// zpracuje jednu radku - rozpozna prikaz a jeho parametry, vytvori instanci tvaru a prida jej do vektoru shapes
	/// </summary>
	/// <param name="line">radek ke zpracovani</param>
	/// <returns>1 pri zpracovani validniho prikazu, 0 pri zpracovani prazdneho radku, -1 pri chybnem vstupu</returns>
	int processLine(std::string line);

	/// <summary>
	/// prida jednu instanci tvaru do vektoru shapes
	/// </summary>
	/// <param name="shape">tvar k pridani</param>
	void addShape(std::unique_ptr<IShape> shape);

	/// <summary>
	/// aplikuje transformaci danou matici na vsechny tvary, ktere jsou aktualne ve vektoru shapes
	/// </summary>
	/// <param name="m">transformacni matice</param>
	void applyTransformation(const Matrix3x3& m);

public:
	/// <summary>
	/// nacte zdrojovy soubor radek po radku, naplni vektor shapes a provede vsechny transformace
	/// </summary>
	/// <param name="filename">nazev zdrojoveho souboru</param>
	/// <returns>pocet nactenych prikazu nebo -1 pri chybe</returns>
	int processFile(const std::string& filename);
};