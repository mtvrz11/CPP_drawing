#include "PgmCanvas.h"
#include <cmath>

PgmCanvas::PgmCanvas(const std::string filename, int w, int h)
	: width(w), height(h)
{
    file.open(filename);
    if (!file.is_open()) {
        // chyba
        return;
    }

    // hlavicka pro pgm
    file << "P2\n"
        << width << " " << height << "\n"
        << "255\n";

	pixels.assign(width * height, 255); // zvetseni vektoru na pozadovanou velikost a naplneni bilou barvou
}

PgmCanvas::~PgmCanvas() {
    if (!file.is_open()) {
        // chyba
        return;
    }

    // vypsani vektoru pixels do souboru (formatovane pro vizualni kontrolu)
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            file << pixels[y * width + x] << " ";
        }
        file << "\n";
    }

    file.close();
}

void PgmCanvas::drawLine(double x1, double y1, double x2, double y2) {
    // prevedeni realnych hodnot na zaukrouhlene celociselne indexy pixelu
    int x = static_cast<int>(std::round(x1));
    int y = static_cast<int>(std::round(y1));
    int end_x = static_cast<int>(std::round(x2));
    int end_y = static_cast<int>(std::round(y2));

    // obecny Bressenhamuv algoritmus
    int dx = std::abs(end_x - x);
    int dy = -std::abs(end_y - y);
    int sx = x < end_x ? 1 : -1;
    int sy = y < end_y ? 1 : -1;
    int err = dx + dy;
    //bool is_horizontal = (dx > -dy);

    while (true) {
        brush2Px(x, y, 0);

        /*if (is_horizontal) {
            setPixel(x, y + 1, 0);
        }
        else {
            setPixel(x + 1, y, 0);
        }*/

        // cil
        if (x == end_x && y == end_y) break;

        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x += sx; }
        if (e2 <= dx) { err += dx; y += sy; }
    }
}

void PgmCanvas::drawCircle(double cx, double cy, double r) {
    // prevedeni realnych hodnot na zaokrouhlene celociselne indexy pixelu
    int x0 = static_cast<int>(std::round(cx));
    int y0 = static_cast<int>(std::round(cy));
    int radius = static_cast<int>(std::round(r));

    // midpoint algoritmus
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        // vykresleni 8 bodu po celem obvodu naraz
        brush2Px(x0 + x, y0 + y, 0);
        brush2Px(x0 + y, y0 + x, 0);
        brush2Px(x0 - y, y0 + x, 0);
        brush2Px(x0 - x, y0 + y, 0);
        brush2Px(x0 - x, y0 - y, 0);
        brush2Px(x0 - y, y0 - x, 0);
        brush2Px(x0 + y, y0 - x, 0);
        brush2Px(x0 + x, y0 - y, 0);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void PgmCanvas::brush2Px(int x, int y, int color) {
    setPixel(x, y, color);
    setPixel(x + 1, y, color);
    setPixel(x + 1, y + 1, color);
    setPixel(x, y + 1, color);
}

void PgmCanvas::setPixel(int x, int y, int color) {
    // clipping - vse mimo platno ignoruji
    if (x >= 0 && x < width && y >= 0 && y < height) {
        pixels[y * width + x] = color;
    }
}