
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
	// @TODO Update to return the index you are choosing to be your root.
	return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const {
	// @TODO Update to return the index of the left child.
	return 2 * currentIdx;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const {
	// @TODO Update to return the index of the right child.
	return 2 * currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const {
	// @TODO Update to return the index of the parent.
	return floor(currentIdx / 2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const {
	// @TODO Update to return whether the given node has a child

	return currentIdx * 2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const {
	// @TODO Update to return the index of the child with highest priority
	///   as defined by higherPriority()

	//check if right child exists
	size_t left = leftChild(currentIdx);
	if (currentIdx * 2 + 1 < _elems.size()) {
		size_t right = rightChild(currentIdx);
		if (higherPriority(_elems[left], _elems[right]))
			return left;
		else
			return right;
	}
	else {
		return left;
	}
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx) {
	// @TODO Implement the heapifyDown algorithm.
	if (!hasAChild(currentIdx))
		return;

	size_t curr = currentIdx;
	size_t left = leftChild(currentIdx);
	size_t right = 0;

	int n;
	//check if right child exists
	if (currentIdx * 2 + 1 < _elems.size()) {
		right = rightChild(currentIdx);
		//both left and right child exist
		//check if done
		if (higherPriority(_elems[curr], _elems[left]) && higherPriority(_elems[curr], _elems[right])) {
			return;
		}

		if (higherPriority(_elems[left], _elems[right])) {
			n = left;
		}
		else {
			n = right;
		}
	}
	else {
		//only left child exists, check if done
		if (higherPriority(_elems[curr], _elems[left])) {
			return;
		}
		else {
			n = left;
		}
	}

	std::swap(_elems[currentIdx], _elems[n]);
	heapifyDown(n);
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx) {
	if (currentIdx == root())
		return;
	size_t parentIdx = parent(currentIdx);
	if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
		std::swap(_elems[currentIdx], _elems[parentIdx]);
		heapifyUp(parentIdx);
	}
}

template <class T, class Compare>
heap<T, Compare>::heap() {
	// @TODO Depending on your implementation, this function may or may
	///   not need modifying

	//add -infinity to front as NULL
	_elems.push_back(std::numeric_limits<T>::min());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) {
	// @TODO Construct a heap using the buildHeap algorithm

	_elems = elems;
	_elems.insert(_elems.begin(), std::numeric_limits<T>::min());
	int level = log2(_elems.size() - 1);
	buildHeap(pow(2, level) - 1);
}

template <class T, class Compare>
void heap<T, Compare>::buildHeap(size_t currentIdx) {
	if (currentIdx == 0)
		return;

	heapifyDown(currentIdx);
	buildHeap(currentIdx - 1);
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
	// @TODO Remove, and return, the element with highest priority

	//replace highest prio with rightmost leaf and remove highest prio
	T ret = _elems[1];

	std::swap(_elems[1], _elems[_elems.size() - 1]);
	_elems.pop_back();

	heapifyDown(1);
	return ret;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
	// @TODO Return, but do not remove, the element with highest priority
	return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem) {
	// @TODO Add elem to the heap
	//push elem to back of elems and heapify up
	_elems.push_back(elem);
	heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t& idx, const T& elem) {
	// @TODO In-place updates the value stored in the heap array at idx
	// Corrects the heap to remain as a valid heap even after update
	if (idx == 0 || idx >= _elems.size())
		return;

	_elems[idx] = elem;

	size_t parentidx = parent(idx);
	if (parentidx != 0) {
		if (higherPriority(_elems[idx], _elems[parentidx]))
			heapifyUp(idx);
	}

	if (hasAChild(idx)) {
		size_t compare = leftChild(idx);
		//check has right child
		if (idx * 2 + 1 < _elems.size()) {
			compare = maxPriorityChild(idx);
		}

		if (higherPriority(_elems[compare], _elems[idx])) {
			heapifyDown(idx);
		}
	}
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
	// @TODO Determine if the heap is empty
	return _elems.size() == 1;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T>& heaped) const {
	for (size_t i = root(); i < _elems.size(); i++) {
		heaped.push_back(_elems[i]);
	}
}
