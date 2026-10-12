/**
 * @file    main.cpp
 * @author  Matìj Tvrz
 * @date    10/2026
 * @brief   Vstupni bod aplikace pro kresleni ve 2D.
 */

#include <iostream>
#include <string>

#include "./core/App.h"
#include "./renderer/ICanvas.h"
#include "./renderer/SvgCanvas.h"
#include "./renderer/PgmCanvas.h"

int main(int argc, char* argv[]) {
	try {
		if (argc != 4) {
			throw std::invalid_argument{ "Spatny pocet argumentu. Pouziti: drawing.exe <vstup> <vystup> <velikost>." };
		}

		auto findDelimiterIdx = [](const std::string s, const char delimiter) -> int {
			size_t idx = s.find(delimiter);
			if (idx == std::string::npos) {
				return -1;
			}
			return idx;
			};

		std::string size = argv[3];
		int x_idx = findDelimiterIdx(size, 'x');
		if (x_idx == -1) {
			throw std::invalid_argument{ "Spatny format argumentu <velikost>. Spravny format: <sirka:int>x<vyska:int>." };
		}
		auto width = size.substr(0, x_idx);
		auto height = size.substr(x_idx + 1);
		auto w_int = std::stoi(width);
		auto h_int = std::stoi(height);

		if (w_int <= 0 || h_int <= 0) {
			throw std::invalid_argument{ "Vyska a sirka platna musi byt prirozena nenulova cisla." };
		}

		std::string ifile = argv[1];
		std::string ofile = argv[2];

		std::unique_ptr<ICanvas> canvas = nullptr;

		int dot_idx = findDelimiterIdx(ofile, '.');
		if (x_idx == -1) {
			throw std::invalid_argument{ "Spatny format vystupniho souboru. Pozadovany format: <soubor>.<pripona>" };
		}
		auto format = ofile.substr(dot_idx + 1);
		if (format == "svg") {
			canvas = std::make_unique<SvgCanvas>(ofile, w_int, h_int);
		}
		else if (format == "pgm") {
			canvas = std::make_unique<PgmCanvas>(ofile, w_int, h_int);
		}
		else {
			throw std::invalid_argument{ "Spatna pripona vystupniho souboru. Povolene pripony: \"pgm\", nebo \"svg\"." };
		}

		App app;
		int cmd_count = app.processFile(ifile);
		app.drawAllShapes(*canvas);

		std::cout << cmd_count << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "CHYBA: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}