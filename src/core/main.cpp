#include <iostream>
#include <string>
#include "App.h"
#include "../renderer/ICanvas.h"
#include "../renderer/SvgCanvas.h"
#include "../renderer/PgmCanvas.h"

struct AppConfig {
	std::string inputFile;
	std::string outputFile;
	int canvasWidth = 0;
	int canvasHeight = 0;
};

int main(int argc, char* argv[]) {

	if (argc != 4) {
		//chyba
		std::cout << "malo argumentu" << std::endl;
		return 1;
	}

	auto findDelimiterIdx = [](const std::string s, const char delimiter) -> size_t {
		size_t idx = s.find(delimiter);
		if (idx == std::string::npos) {
			std::cout << delimiter << " nenalezen" << std::endl;
		}
		return idx;
	};

	std::string size = argv[3];
	size_t x_idx = findDelimiterIdx(size, 'x');
	auto width = size.substr(0, x_idx);
	auto height = size.substr(x_idx + 1);
	auto w_int = std::stoi(width);
	auto h_int = std::stoi(height);

	if (w_int <= 0 || h_int <= 0) {
		// chyba
		std::cout << "nulove rozmery" << std::endl;
		return 1;
	}

	std::string ifile = argv[1];
	std::string ofile = argv[2];

	std::unique_ptr<ICanvas> canvas = nullptr;

	size_t dot_idx = findDelimiterIdx(ofile, '.');
	auto format = ofile.substr(dot_idx + 1);
	if (format == "svg") {
		canvas = std::make_unique<SvgCanvas>(ofile, w_int, h_int);
	}
	else if (format == "pgm") {
		canvas = std::make_unique<PgmCanvas>(ofile, w_int, h_int);
	}
	else {
		//chyba
		std::cout << "nepodporovany format" << std::endl;
		return 1;
	}

	App app;
	int cmd_count = app.processFile(ifile);
	if (cmd_count < 0) {
		// chyba
		std::cout << "chyba parseru" << std::endl;
		return 1;
	}

	app.drawAllShapes(*canvas);

	std::cout << "v poradku! nacteno radku: " << cmd_count << std::endl;

	return 0;
}