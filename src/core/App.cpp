#include "App.h"
#include "../shapes/Line.h"
#include "../shapes/Circle.h"
#include "../shapes/Rect.h"

#include <fstream>
#include <sstream>

int App::processFile(const std::string& filename) {

	std::ifstream file(filename);
	if (!file.is_open()) {
		// chyba
		return -1;
	}

	std::string line;
	int cmd_count = 0;

	// prochazim po radcich
	while (std::getline(file, line)) {
		auto pl = processLine(line);

		if (pl == -1) {
			// chyba
			return -1;
		}

		if (pl == 1) {
			cmd_count++;
		}

		// pri prazdnem radku (pl == 0) nevyhazuji chybu, ale ani nepricitam dalsi prikaz 
	}

	return cmd_count;
}

int App::processLine(std::string line) {
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
		return 0; // prazdny radek
	}

	if (command == "line") {
		int x1, y1, x2, y2;

		if (!(ss >> x1 >> y1 >> x2 >> y2)) return -1; // zoskani ciselnych hodnot
		if (x1 == x2 && y1 == y2) return -1; // overeni, zda pocatecni a koncovy bod nesplyvaji
		if (!isEnd()) return -1;

		addShape(std::make_unique<Line>(x1, y1, x2, y2));
		return 1;
	}

	if (command == "circle") {
		int cx, cy;
		double r;

		if (!(ss >> cx >> cy >> r)) return -1; // ziskani ciselnych hodnot
		if (r <= 0) return -1; // overeni, zda je polomer kladny nenulovy
		if (!isEnd()) return -1;

		addShape(std::make_unique<Circle>(cx, cy, r));
		return 1;
	}

	if (command == "rect") {
		int x, y, w, h;

		if (!(ss >> x >> y >> w >> h)) return -1; // ziskani ciselnych hodnot
		if (w <= 0 || h <= 0) return -1; // overeni, zda neni zadana nulova sirka nebo vyska
		if (!isEnd()) return -1;

		addShape(std::make_unique<Rect>(x, y, w, h));
		return 1;
	}

	if (command == "translate") {
		int x, y;

		if (!(ss >> x >> y)) return -1; // ziskani ciselnych hodnot
		if (!isEnd()) return -1;

		applyTransformation(Matrix3x3::createTranslation(x, y));
		return 1;
	}

	if (command == "rotate") {
		int x, y;
		double a;

		if (!(ss >> x >> y >> a)) return -1; // ziskani ciselnych hodnot
		if (!isEnd()) return -1;

		applyTransformation(Matrix3x3::createRotation(x, y, a));
		return 1;
	}

	if (command == "scale") {
		int x, y;
		double f;

		if (!(ss >> x >> y >> f)) return -1; // ziskani ciselnych hodnot
		if (f == 0) return -1; // overeni, zda faktor neni nulovy
		if (!isEnd()) return -1;

		applyTransformation(Matrix3x3::createScale(x, y, f));
		return 1;
	}

	// radek zacinal necim, co nebyl platny prikaz
	return -1;
}

void App::addShape(std::unique_ptr<IShape> shape) {
	shapes.push_back(std::move(shape));
}

void App::applyTransformation(const Matrix3x3& m) {
	for (auto& shape : shapes) {
		shape->transform(m);
	}
}