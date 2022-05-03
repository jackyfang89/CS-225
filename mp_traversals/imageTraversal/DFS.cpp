#include <cmath>
#include <iterator>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../Point.h"
#include "../cs225/PNG.h"

#include "DFS.h"
#include "ImageTraversal.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG& png, const Point& start, double tolerance) {
	/** @todo [Part 1] */
	png_ = png;
	start_ = start;
	tolerance_ = tolerance;
	add(start_);
}

DFS::~DFS() {
	//do nothing
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
	/** @todo [Part 1] */
	return ImageTraversal::Iterator(start_, start_, this, &png_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
	/** @todo [Part 1] */
	Point otpe(png_.width(), png_.height());
	return ImageTraversal::Iterator(start_, otpe, this, &png_);
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point& point) {
	/** @todo [Part 1] */
	if (point.x < png_.width() && point.y < png_.height())
		stack_.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
	/** @todo [Part 1] */
	//if (stack_.size() == 0) return NULL;
	Point top = stack_.top();
	stack_.pop();
	//if (!visited(top)) visited_.push_back(top);
	return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
	/** @todo [Part 1] */
	return stack_.top();
	//if (stack_.size() == 0) return NULL;
	// if (!empty()) return stack_.top();
	// else return Point(png_.width(), png_.height());
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
	/** @todo [Part 1] */
	return stack_.size() == 0;
}

double DFS::getTolerance() const {
	return tolerance_;
}