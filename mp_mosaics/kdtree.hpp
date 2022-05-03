/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
								const Point<Dim>& second, int curDim) const {
	if (first[curDim] == second[curDim])
		return first < second;
	else
		return first[curDim] < second[curDim];
}

template <int Dim>
double KDTree<Dim>::distance(const Point<Dim> a, const Point<Dim> b) const {
	double d = 0;
	for (int i = 0; i < Dim; ++i) {
		d += pow((a[i] - b[i]), 2.0);
	}
	return sqrt(d);
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
								const Point<Dim>& currentBest,
								const Point<Dim>& potential) const {
	//current distance
	double d1 = distance(currentBest, target);
	//potential distance
	double d2 = distance(potential, target);

	if (d1 == d2) {
		return potential < currentBest;
	}
	return d2 < d1;
}

template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& vec, int l, int r, int d) const {
	//choose end as pivot
	Point<Dim> pivot = vec[r];
	int i = l;
	for (int j = l; j <= r - 1; ++j) {
		Point<Dim> a = vec[j];

		if (smallerDimVal(a, pivot, d)) {
			iter_swap(vec.begin() + i, vec.begin() + j);
			//swap(vec[i], vec[j]);
			i++;
		}
	}
	iter_swap(vec.begin() + i, vec.begin() + r);
	//swap(vec[i], vec[r]);
	return i;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(vector<Point<Dim>>& newPoints, int l, int r, int k, int d) const {
	if (l == r)
		return newPoints[l];

	int pivotIndex = partition(newPoints, l, r, d);

	if (k == pivotIndex)
		return newPoints[pivotIndex];
	else if (k < pivotIndex) {
		r = pivotIndex - 1;
	}
	else {
		l = pivotIndex + 1;
	}

	return quickSelect(newPoints, l, r, k, d);
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::helpConstruct(vector<Point<Dim>> newPoints, int l, int r, int d) {
	//base cases for if newPoints is empty or only 1 element
	if (newPoints.size() == 0)
		return NULL;
	if (newPoints.size() == 1)
		return new KDTreeNode(newPoints[0]);

	int m = floor((double)(newPoints.size() - 1) / 2.0);
	Point<Dim> median = quickSelect(newPoints, l, r, m, d);
	KDTreeNode* node = new KDTreeNode(median);

	vector<Point<Dim>> left(newPoints.begin(), newPoints.begin() + m);
	vector<Point<Dim>> right(newPoints.begin() + m + 1, newPoints.end());

	node->left = helpConstruct(left, 0, left.size() - 1, (d + 1) % Dim);
	node->right = helpConstruct(right, 0, right.size() - 1, (d + 1) % Dim);
	return node;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints) {
	root = KDTree<Dim>::helpConstruct(newPoints, 0, newPoints.size() - 1, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
	copy(other.root, root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
	if (this != &rhs) {
		root = NULL;
		destroy(root);
		copy(rhs.root, root);
	}
	return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
	destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const {
	Point<Dim> root_copy = root->point;
	return helpFind(query, root_copy, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::helpFind(const Point<Dim>& target, Point<Dim>& best, KDTreeNode* subroot, int d) const {
	/*
        procedure for findNearestNeighbor:
        1. go down the tree recursively to the smallest hyperrectangle that contains target
        2. leaf node eventually hit, and becomes our "current best"
        3. begin backtracking to check for other nodes that are closer
        4. return final current best as nearestNeigbor

        procedure for backtracking:
        3.1. If at leaf node, check to update current best return up subtree
        3.2. If not at leaf, check distance from target to current splitting plane*. 
             *. ex: if d = 0, then check abs(target[0] - current[0]).
        3.3. If within current radius, go down other subtree based on step 1.
        3.4. If not, return up subtree
        3.5. Repeat steps 3.1 - 3.4. 
    */

	if (subroot == NULL) {
		return Point<Dim>();
	}

	//if at leaf node
	Point<Dim>& curr = subroot->point;
	if (subroot->left == NULL && subroot->right == NULL) {
		//check if should replace current best
		if (shouldReplace(target, best, curr)) {
			best = curr;
		}
		return best;
	}
	else {
		//tells me if I went left or right subtree
		bool left = false;
		//check to go left if curr point smaller than target point
		if (smallerDimVal(target, curr, d)) {
			helpFind(target, best, subroot->left, (d + 1) % Dim);
			left = true;
		}
		else {
			helpFind(target, best, subroot->right, (d + 1) % Dim);
		}

		//check if current node closer to target than best
		if (shouldReplace(target, best, curr)) {
			best = curr;
		}
		//distance from target point to splitting plane for curr node
		double dist = abs(target[d] - curr[d]);
		double rad = distance(target, best);
		if (dist <= rad) {
			//check which subtree we just went
			//and go down the other one
			if (left) {
				helpFind(target, best, subroot->right, (d + 1) % Dim);
			}
			else {
				helpFind(target, best, subroot->left, (d + 1) % Dim);
			}
		}
		return best;
	}
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* subroot) {
	if (subroot != NULL) {
		destroy(subroot->left);
		destroy(subroot->right);
		delete subroot;
	}
}

template <int Dim>
void KDTree<Dim>::copy(const KDTreeNode* other, KDTreeNode*& subroot) {
	if (other == NULL) {
		subroot = NULL;
	}
	else {
		subroot = new KDTreeNode(other->point);
		copy(other->left, subroot->left);
		copy(other->right, subroot->right);
	}
}
