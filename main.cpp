#include <iostream>
#include <string>

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

	std::string props = argv[3];
	auto delimiter_idx = props.find('x');

	if (delimiter_idx == std::string::npos) {
		// chyba - x nenalezeno
		std::cout << "x nenalezeno" << std::endl;
		return 1;
	}

	auto width = props.substr(0, delimiter_idx);
	auto height = props.substr(delimiter_idx + 1, props.length());
	auto w_int = std::stoi(width);
	auto h_int = std::stoi(height);

	if (w_int <= 0 || h_int <= 0) {
		// chyba
		std::cout << "nulove rozmery" << std::endl;
		return 1;
	}

	AppConfig config;
	config.inputFile = argv[1];
	config.outputFile = argv[2];
	config.canvasWidth = w_int;
	config.canvasHeight = h_int;

	std::cout << "v poradku!" << std::endl;

	return 0;
}