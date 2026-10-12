/**
 * @file    App.cpp
 * @author  Matìj Tvrz
 * @date    10/2026
 * @brief   Implementace metod tøídy App.
 */

#include "App.h"
#include "../shapes/Line.h"
#include "../shapes/Circle.h"
#include "../shapes/Rect.h"

#include <fstream>
#include <sstream>

int App::processFile(const std::string& filename) {

	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error{ "Nepodarilo se otevrit vstupni soubor." };
	}

	std::string line;
	int cmd_count = 0;
	int line_number = 0;
	bool pl = false;

	// prochazim po radcich
	while (std::getline(file, line)) {
		line_number++;
		try {
			pl = processLine(line);
		}
		catch (const std::exception& e) {
			throw std::runtime_error{ "Chyba na radku " + std::to_string(line_number) + ": " + e.what() };
		}

		if (pl) {
			cmd_count++;
		}
	}

	return cmd_count;
}

bool App::processLine(std::string line) {
	// oriznuti komentare
	size_t pos = line.find('#');
	if (pos != std::string::npos) {
		line = line.substr(0, pos);
	}

	std::stringstream ss(line);
	std::string command;

	// lambda funkce pro overeni, ze za pozadovanymi parametry nenasleduji dalsi
	auto isEnd = [&ss]() -> bool {
		std::string dummy;
		return !(ss >> dummy);
	};


	if (!(ss >> command)) {
		return false; // prazdny radek
	}

	if (command == "line") {
		int x1, y1, x2, y2;

		if (!(ss >> x1 >> y1 >> x2 >> y2) || !isEnd()) // zoskani ciselnych hodnot
			throw std::invalid_argument{ "Spatny format v parametrech prikazu line. Spravny format: line <x1:int> <y1:int> <x2:int> <y2:int>." };
		if (x1 == x2 && y1 == y2) // overeni, zda pocatecni a koncovy bod nesplyvaji
			throw std::invalid_argument{ "Pocatecni a koncovy bod usecky splyvaji. Musi byt ruzne." };

		addShape(std::make_unique<Line>(x1, y1, x2, y2));
		return 1;
	}

	if (command == "circle") {
		int cx, cy;
		double r;

		if (!(ss >> cx >> cy >> r) || !isEnd()) // ziskani ciselnych hodnot
			throw std::invalid_argument{ "Spatny format v parametrech prikazu circle. Spravny format: circle <cx:int> <cy:int> <r:double>." };
		if (r <= 0) // overeni, zda je polomer kladny nenulovy
			throw std::invalid_argument{ "Polomer musi byt realne cislo vetsi nez 0." };

		addShape(std::make_unique<Circle>(cx, cy, r));
		return 1;
	}

	if (command == "rect") {
		int x, y, w, h;

		if (!(ss >> x >> y >> w >> h) || !isEnd()) // ziskani ciselnych hodnot
			throw std::invalid_argument{ "Spatny format v parametrech prikazu rect. Spravny format: rect <x:int> <y:int> <w:int> <h:int>." };
		if (w <= 0 || h <= 0) // overeni, zda neni zadana nulova sirka nebo vyska
			throw std::invalid_argument{ "Sirka i vyska musi byt kladne nenulove cislo." };

		addShape(std::make_unique<Rect>(x, y, w, h));
		return 1;
	}

	if (command == "translate") {
		int x, y;

		if (!(ss >> x >> y) || !isEnd()) // ziskani ciselnych hodnot
			throw std::invalid_argument{ "Spatny format v parametrech prikazu translate. Spravny format: translate <x:int> <y:int>." };

		applyTransformation(Matrix3x3::createTranslation(x, y));
		return 1;
	}

	if (command == "rotate") {
		int x, y;
		double a;

		if (!(ss >> x >> y >> a) || !isEnd()) // ziskani ciselnych hodnot
			throw std::invalid_argument{ "Spatny format v parametrech prikazu rotate. Spravny format: rotate <x:int> <y:int> <a:double>." };

		applyTransformation(Matrix3x3::createRotation(x, y, a));
		return 1;
	}

	if (command == "scale") {
		int x, y;
		double f;

		if (!(ss >> x >> y >> f) || !isEnd()) // ziskani ciselnych hodnot
			throw std::invalid_argument{ "Spatny format v parametrech prikazu scale. Spravny format: scale <x:int> <y:int> <f:double>." };
		if (f == 0) // overeni, zda faktor neni nulovy
			throw std::invalid_argument{ "Faktor musi byt realne nenulove cislo." };

		applyTransformation(Matrix3x3::createScale(x, y, f));
		return 1;
	}

	throw std::invalid_argument{ "Neplatny prikaz: " + command + "."};
}

void App::addShape(std::unique_ptr<IShape> shape) {
	shapes.push_back(std::move(shape));
}

void App::applyTransformation(const Matrix3x3& m) {
	for (auto& shape : shapes) {
		shape->transform(m);
	}
}

void App::drawAllShapes(ICanvas& canvas) const {
	for (const auto& shape : shapes) {
		shape->draw(canvas);
	}
}