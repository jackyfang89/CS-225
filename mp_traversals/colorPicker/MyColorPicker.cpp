#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

#include <cmath>

using namespace cs225;

MyColorPicker::MyColorPicker() {
	//do nothing
}

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
	/* @todo [Part 3] */
	double a = fmod(x, 360);
	double b = fmod(y, 360);

	double hue = fmod((a + b), 360);

	return HSLAPixel(hue, 1, 0.5);
}
