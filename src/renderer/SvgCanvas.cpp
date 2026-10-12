#include "SvgCanvas.h"

SvgCanvas::SvgCanvas(const std::string& filename, int w, int h) {
	file.open(filename);
	if (!file.is_open()) {
		throw std::runtime_error{ "Nepodarilo se otevrit vstupni soubor: " + filename };
	}

	file << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"" << w << "\" height=\"" << h << "\">\n"; // zalozeni platna dane velikosti
	file << "<rect width = \"100%\" height=\"100%\" fill=\"white\" />\n"; // vykresleni bileho obdelniku jako pozadi
}

SvgCanvas::~SvgCanvas() {
	if (file.is_open()) {
		file << "</svg>"; // ukonceni svg bloku
		file.close();
	}
}

void SvgCanvas::drawLine(double x1, double y1, double x2, double y2) {
	if (file.is_open()) { // kontrola otevreni souboru mozna zbytecna ???
		file << "<line x1=\"" << x1 << "\" y1=\"" << y1 << "\" x2=\"" << x2 << "\" y2=\"" << y2
			<< "\" stroke=\"black\" stroke-width=\"2\" />\n";
	}
}

void SvgCanvas::drawCircle(double cx, double cy, double r) {
	if (file.is_open()) {
		file << "<circle cx=\"" << cx << "\" cy=\"" << cy << "\" r=\"" << r
			<< "\" stroke=\"black\" stroke-width=\"2\" fill=\"white\" />\n";
	}
}