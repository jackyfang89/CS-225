#include <cmath>
#include <iterator>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../Point.h"
#include "../cs225/PNG.h"

#include "BFS.h"
#include "ImageTraversal.h"

using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG& png, const Point& start, double tolerance) {
	/** @todo [Part 1] */
	png_ = png;
	start_ = start;
	tolerance_ = tolerance;
	add(start_);
}

BFS::~BFS() {
	//do nothing
}
/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
	/** @todo [Part 1] */
	return ImageTraversal::Iterator(start_, start_, this, &png_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
	/** @todo [Part 1] */
	Point otpe(png_.width(), png_.height());
	return ImageTraversal::Iterator(start_, otpe, this, &png_);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point& point) {
	/** @todo [Part 1] */
	if (point.x < png_.width() && point.y < png_.height())
		queue_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
	/** @todo [Part 1] */
	Point top = queue_.front();
	queue_.pop();
	//if (!visited(top)) visited_.push_back(top);
	return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
	/** @todo [Part 1] */
	return queue_.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
	/** @todo [Part 1] */
	return queue_.size() == 0;
}

double BFS::getTolerance() const {
	return tolerance_;
}