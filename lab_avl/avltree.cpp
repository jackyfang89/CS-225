/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const {
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const {
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else {
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t) {
	functionCalls.push_back("rotateLeft");   // Stores the rotation name (don't remove this)
											 // your code
	Node* right = t->right;
	if (right == NULL) return;

	Node* newRight = right->left;
	t->right = newRight;
	right->left = t;
    //update t and right's heights
	t->height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    right->height = 1 + std::max(heightOrNeg1(right->right), heightOrNeg1(right->left));
    t = right;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t) {
	functionCalls.push_back("rotateLeftRight");   // Stores the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t) {
	functionCalls.push_back("rotateRight");   // Stores the rotation name (don't remove this)
											  // your code here
	Node* left = t->left;
	if (left == NULL) return;

	Node* newleft = left->right;
	t->left = newleft;
	left->right = t;

    t->height = 1 + std::max(heightOrNeg1(t->right), heightOrNeg1(t->left));
    left->height = 1 + std::max(heightOrNeg1(left->right), heightOrNeg1(left->left));
	t = left;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t) {
	functionCalls.push_back("rotateRightLeft");   // Stores the rotation name (don't remove this)
												  // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree) {
    //todo
	int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    int leftBalance = 0, rightBalance = 0;
    if (subtree->left != NULL)
        leftBalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
    if (subtree->right != NULL)
        rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
    
    if (balance >= 2) {
        if (rightBalance >= 1) {
            rotateLeft(subtree);
        }
        else if (rightBalance <= -1){
            rotateRightLeft(subtree);
        }
    }
    else if (balance <= -2) {
        if (leftBalance >= 1) {
            rotateLeftRight(subtree);
        }
        else if (leftBalance <= -1) {
            rotateRight(subtree);
        }
    }

    // subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V>
void AVLTree<K, V>::insert(const K& key, const V& value) {
	insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value) {
	if (subtree == NULL) {
		subtree = new Node(key, value);
	}
	else {
		if (key < subtree->key) 
			insert(subtree->left, key, value);
		else 
			insert(subtree->right, key, value);
        int origHeight = subtree->height;
        subtree->height = 1 + std::max(heightOrNeg1(subtree->right), heightOrNeg1(subtree->left));

		if (origHeight != subtree->height)
            rebalance(subtree); 
	}
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key) {
	remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key) {
	if (subtree == NULL)
		return;

	if (key < subtree->key) {
		remove(subtree->left, key);
        if (subtree->left == NULL) {
            if (subtree->right == NULL) subtree->height = 0;
            else subtree->height = 1 + subtree->right->height; 
        }
		rebalance(subtree);
	}
	else if (key > subtree->key) {
		// your code here
		remove(subtree->right, key);
        if (subtree->right == NULL) {
            if (subtree->left == NULL) subtree->height = 0;
            else subtree->height = 1 + subtree->left->height; 
        }
		rebalance(subtree);
	}
	else {
		if (subtree->left == NULL && subtree->right == NULL) {
			/* no-child remove */
            delete subtree;
			subtree = NULL;
		}
		else if (subtree->left != NULL && subtree->right != NULL) {
			/* two-child remove */
			// your code here
			Node* curr = subtree->left;
			Node* parent = subtree;
			while (curr->right != NULL) {
				parent = curr;
				curr = curr->right;
			}
			swap(subtree, curr);
            subtree->height = 1 + std::max(subtree->left->height, subtree->right->height);

			if (parent == subtree) 
				parent->left = NULL;
			else 
				parent->right = NULL;
            
            delete curr;
		}
		else {
			/* one-child remove */
			// your code here
			Node* temp = NULL;
			if (subtree->left != NULL)
				temp = subtree->left;

			else
				temp = subtree->right;

			delete subtree;
			subtree = temp;
		}
	}
}


