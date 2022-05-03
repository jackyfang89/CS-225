/* Your code here! */

#include "dsets.h"

//adds num amount of unconnected root nodes at the end of the vector
void DisjointSets::addelements(int num) {
	for (int i = 0; i < num; ++i) {
		_up.push_back(-1);
	}
}

//returns index of root of the up tree that elem resides in
//also compresses paths to elem
int DisjointSets::find(int elem) {
	//every node points to its parent
	//so traverse up tree until we hit a root

	//check elem to prevent out of bouds
	if (elem < 0 || (size_t)elem > _up.size() - 1)
		return -1;

	//find root and update path while traversing
	vector<int> path;
	path.push_back(elem);

	int parent = _up[elem];
	if (parent < 0)
		return elem;

	//while actual parent node isn't a root
	while (parent >= 0) {
		for (size_t i = 0; i < path.size(); ++i) {
			//set nodes in path to point to same node as parent
			_up[path[i]] = parent;
		}
		path.push_back(parent);
		elem = parent;
		parent = _up[parent];
	}

	return elem;
}

//sets union of two uptress with elems a and b
//implemented as union-by-size
void DisjointSets::setunion(int a, int b) {
	/* Procedure:
     * 1. find roots of trees that contain a and b
     * 2. check the sizes of the trees
     * 3. append root of smaller tree to root of big tree
     * 3.1 update roots to reflect change
     */
	int a_root = find(a);
	int b_root = find(b);

	//do nothing if in same set
	if (a_root == b_root) return;

	//if didn't find either root then no union do nothing
	if (a_root == -1 || b_root == -1)
		return;

	int size_a = size(a_root), size_b = size(b_root);

	if (size_a > size_b || size_a == size_b) {
		_up[b_root] = a_root;
		_up[a_root] -= size_b;
	}
	else {
		_up[a_root] = b_root;
		_up[b_root] -= size_a;
	}
}

//returns number of nodes in the uptree that contains elem
int DisjointSets::size(int elem) {
	int root = find(elem);
	return -_up[root];
}