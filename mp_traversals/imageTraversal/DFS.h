/**
 * @file DFS.h
 */

#pragma once

#include <cmath>
#include <iterator>
#include <list>
#include <stack>
#include <vector>

#include "../Point.h"
#include "../cs225/PNG.h"

#include "ImageTraversal.h"

using namespace cs225;

/**
 * A depth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class DFS : public ImageTraversal {
public:
	DFS(const PNG& png, const Point& start, double tolerance);
	~DFS();

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
	std::stack<Point> stack_;
	double tolerance_;
};
