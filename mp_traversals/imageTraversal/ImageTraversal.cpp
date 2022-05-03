#include <cmath>
#include <iostream>
#include <iterator>

#include "../Point.h"
#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel& p1, const HSLAPixel& p2) {
	double h = fabs(p1.h - p2.h);
	double s = p1.s - p2.s;
	double l = p1.l - p2.l;

	// Handle the case where we found the bigger angle between two hues:
	if (h > 180) {
		h = 360 - h;
	}
	h /= 360;

	return sqrt((h * h) + (s * s) + (l * l));
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() : start_(), curr_(), imt_(NULL), png_(NULL), visited_(NULL) {
	/** @todo [Part 1] */
	//nothing
}

ImageTraversal::Iterator::Iterator(Point start, Point p, ImageTraversal* imt, PNG* png) : start_(start), curr_(p), imt_(imt), png_(png) {
	visited_ = new bool*[png_->height()];
	for (unsigned i = 0; i < png_->height(); ++i) {
		visited_[i] = new bool[png_->width()];
		for (unsigned j = 0; j < png_->width(); ++j) {
			visited_[i][j] = false;
		}
	}
}

ImageTraversal::~ImageTraversal() {
	return;
}

ImageTraversal::Iterator::~Iterator() {
	for (unsigned i = 0; i < png_->height(); ++i) {
		delete visited_[i];
	}
	delete visited_;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator& ImageTraversal::Iterator::operator++() {
	curr_ = imt_->pop();
	visited(curr_);
	addNeighbors(curr_);
	Point top = imt_->peek();
	//HSLAPixel& topPixel = png_->getPixel(top.x, top.y);
	HSLAPixel& startPixel = png_->getPixel(start_.x, start_.y);

	while (visited(top) || calculateDelta(png_->getPixel(top.x, top.y), startPixel) >= imt_->getTolerance()) {
		imt_->pop();
		if (imt_->empty()) {
			curr_.x = png_->width();
			curr_.y = png_->height();
			return *this;
		}
		top = imt_->peek();
	}
	curr_.x = top.x;
	curr_.y = top.y;
	return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
	/** @todo [Part 1] */
	return curr_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator& other) {
	/** @todo [Part 1] */
	return !(curr_ == other.curr_);
}

bool ImageTraversal::Iterator::inBounds(unsigned x, unsigned y) {
	return (x >= 0 && x < png_->width() && y >= 0 && y < png_->height());
}

void ImageTraversal::Iterator::addNeighbors(Point p) {
	imt_->add(Point(p.x + 1, p.y));
	imt_->add(Point(p.x, p.y + 1));
	imt_->add(Point(p.x - 1, p.y));
	imt_->add(Point(p.x, p.y - 1));
}

bool ImageTraversal::Iterator::visited(const Point p) {
	if (p.y >= png_->height() || p.x >= png_->width()) return false;
	bool ans = visited_[p.y][p.x];
	if (ans == false) visited_[p.y][p.x] = true;

	return ans;
}