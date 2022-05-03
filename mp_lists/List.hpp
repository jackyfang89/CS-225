/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  if (head_ != NULL) return List<T>::ListIterator(head_);
  else return List<T>::ListIterator();
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  if (tail_ != NULL) {
      List<T>::ListIterator it(tail_);
      //++it;
      return ++it;
  }
  else return List<T>::ListIterator();
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* curr = head_;
  while(curr != NULL) {
      ListNode* next = curr->next;
      delete curr;
      curr = next;
  }
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  
  if (head_ != NULL) {
      newNode->next = head_;
      newNode->prev = NULL;
      head_->prev = newNode;
      head_ = newNode;
  }
  else {
      head_ = newNode;
      tail_ = newNode;
      newNode->next = NULL;
      newNode->prev = NULL;
  }

  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  // @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  
  if (tail_ != NULL) {
      newNode->prev = tail_;
      newNode->next = NULL;
      tail_->next = newNode;
      tail_ = newNode;
  }
  else {
      head_ = newNode;
      tail_ = newNode;
      newNode->prev = NULL;
      newNode->next = NULL;
  }

  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  ///@todo Graded in MP3.1
  if (start == NULL || splitPoint >= length_ || length_ < 2) return NULL; //can't split
  else if (splitPoint <= 0) return start;
  else {
      //length_ = splitPoint;
      while (splitPoint > 0) {
          if (start == NULL) return NULL; //can't split at splitPoint
          start = start->next;
          splitPoint--;
      }
      //start should now be at head of sublist.
      //handle previous point(new tail of orig list)
      tail_ = start->prev;
      start->prev->next = NULL; //set new tail of orig list
      start->prev = NULL; //set NULL to be next of new tail
      return start;
  }
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
    int i = 1;
    ListNode* C = head_;
    while (C != NULL) {
        if (i % 3 == 0) {
            ListNode* oldPrev = C->prev->prev->prev;
            ListNode* oldNext = C->next;

            ListNode* A = C->prev->prev;
            ListNode* B = C->prev;

            //need to turn A <-> B <-> C into B <-> C <-> A
            //set C <-> A; C is curr;
            
            C->next = A;
            A->prev = C;

            //remove A <-> B
            A->next = oldNext;
            B->prev = oldPrev;

            //update oldPrev and oldNext
            if (oldPrev != NULL) oldPrev->next = B;
            if (oldNext != NULL) oldNext->prev = A;
            //update head_ and tail_ if needed
            if (i == 3) head_ = B;
            if (i == length_) tail_ = A;
            C = A; //update curr to correct node after rotate
        }
        i++;
        C = C->next;
    }
}


/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
    if (startPoint == NULL || endPoint == NULL) return; //add this edge case later
    
    ListNode* startPrev = startPoint->prev;
    ListNode* endNext = endPoint->next;
    
    ListNode* curr = endPoint;

    //reverse partially, remove all prevs
    while (curr != startPrev) {
        ListNode* temp = curr->prev;
        curr->next = curr->prev;
        curr->prev = NULL;
        curr = temp;
    }

    //add back prevs
    curr = endPoint; //endPoint is new start, just not yet updated
    curr->prev = startPrev;
    if (startPrev != NULL) startPrev->next = curr;

    while (curr != startPoint) {
        ListNode* temp = curr->next;
        temp->prev = curr;
        curr = temp;
    }

    curr->next = endNext;
    if (endNext != NULL) endNext->prev = curr;

    //update startPoint and endPoint
    startPoint = endPoint;
    endPoint = curr;

    //update head_ and tail_
    if (startPrev == NULL) head_ = startPoint;
    if (endNext == NULL) tail_ = endPoint;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
    if (n > length_ || head_ == NULL) return;
    
    int l = length_;
    ListNode* curr = head_;
    while (l >= 0 && curr != NULL) {
        ListNode* end = curr;
        if (l >= n)
            for (int i = 0; i < n - 1; ++i) end = end->next;
        else 
            for (int i = 0; i < l - 1; ++i) end = end->next;
        reverse(curr, end);
        curr = end->next;
        l -= n;
    }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL; 
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
    if (first == NULL) return second;
    if (second == NULL) return first;

    ListNode* start = first;
    while (first != NULL && second != NULL) {
        ListNode* second_next = second->next;
        if (first->next != NULL) {
            if (first->data < second->data && second->data < first->next->data) {
                ListNode* temp = first->next;
                first->next = second;
                second->prev = first;
                second->next = temp;
                if (temp != NULL) temp->prev = second;
                second = second_next;
            }
            else if (second->data < first->data || second->data == first->data) {
                ListNode* temp = first->prev;
                second->next = first;
                first->prev = second;
                second->prev = temp;
                if (temp != NULL) temp->next = second;
                second = second_next;
            }
            else first = first->next;
        }
        else {
            if (first->data < second->data) {
                first->next = second;
                second->prev = first;
                second->next = NULL;
                second = second_next;
            }
            else {
                ListNode* temp = first->prev;
                second->next = first;
                first->prev = second;
                second->prev = temp;
                if (temp != NULL) temp->next = second;
                first = first->prev;
                second = second_next;
            }
        }
    }
    
    while(start->prev != NULL) start = start->prev;
    return start;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
    if (chainLength == 1 || start == NULL) return start;
    ListNode* start2 = start->next;
    int n = chainLength/2;
    
    for (int i = 0; i < n - 1; ++i)
        if (start2 != NULL) start2 = start2->next; else break;
    
    //break off chains
    start2->prev->next = NULL;
    start2->prev = NULL;
    
    ListNode* a = mergesort(start, n);
    ListNode* b = mergesort(start2, chainLength - n);

    return merge(a, b);
}
