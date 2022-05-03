/* Your code here! */

// Implementation of Disjoint sets using a vector

#pragma once

#include <vector>

using std::vector;

class DisjointSets {
public:
	//adds num amount of unconnected root nodes at the end of the vector
	//param: num is the num of nodes to make
	void addelements(int num);

	//returns index of root of the up tree that elem resides in
	//also compresses paths to elem
	//param: elem is the elemnt to find
	//note: not const because find uses path compression
	int find(int elem);

	//sets union of two uptress with elems a and b
	//implemented as union-by-size
	//param: a and b are elems in tress to union
	void setunion(int a, int b);

	//returns number of nodes in the uptree that contains elem
	//param: elem is the element to get size of tree of
	//note: not const because size must call find, which uses path compression
	int size(int elem);

	//vector that stores uptrees that respresent our disjoint sets
	vector<int> _up;
};
