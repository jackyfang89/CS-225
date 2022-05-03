/**
 * @file BFS.h
 */

#pragma once

#include <cmath>
#include <iterator>
#include <list>
#include <queue>
#include <vector>

#include "../Point.h"
#include "../cs225/PNG.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
	BFS(const PNG& png, const Point& start, double tolerance);
	~BFS();
	ImageTraversal::Iterator begin();
	ImageTraversal::Iterator end();

	void add(const Point& point);
	Point pop();
	Point peek() const;
	bool empty() const;
	double getTolerance() const;

private:
	/** @todo [Part 1] */
	/** add private members here*/
	PNG png_;
	Point start_;
	std::queue<Point> queue_;
	double tolerance_;
};
