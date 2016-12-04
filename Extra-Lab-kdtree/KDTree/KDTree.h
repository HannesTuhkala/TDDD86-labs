/**
 * File: KDTree.h
 * Author: (your name here)
 * ------------------------
 * An interface representing a kd-tree in some number of dimensions. The tree
 * can be constructed from a set of data and then queried for membership and
 * nearest neighbors.
 */

#ifndef KDTREE_INCLUDED
#define KDTREE_INCLUDED

#include "Point.h"
#include "BoundedPQueue.h"
#include <stdexcept>
#include <cmath>

// "using namespace" in a header file is conventionally frowned upon, but I'm
// including it here so that you may use things like size_t without having to
// type std::size_t every time.
using namespace std;

template <size_t N, typename ElemType>
struct KDNode {

    KDNode(Point<N> point, ElemType value) : point(point), value(value){}

    KDNode<N, ElemType>* left_child;
    KDNode<N, ElemType>* right_child;

    ElemType value;
    Point<N> point;

};

template <size_t N, typename ElemType>
class KDTree {
public:
    // Constructor: KDTree();
    // Usage: KDTree<3, int> myTree;
    // ----------------------------------------------------
    // Constructs an empty KDTree.
    KDTree();
    
    // Destructor: ~KDTree()
    // Usage: (implicit)
    // ----------------------------------------------------
    // Cleans up all resources used by the KDTree.
    ~KDTree();
    
    // KDTree(const KDTree& rhs);
    // KDTree& operator=(const KDTree& rhs);
    // Usage: KDTree<3, int> one = two;
    // Usage: one = two;
    // -----------------------------------------------------
    // Deep-copies the contents of another KDTree into this one.
    KDTree(const KDTree& rhs);
    KDTree& operator=(const KDTree& rhs);
    
    // size_t dimension() const;
    // Usage: size_t dim = kd.dimension();
    // ----------------------------------------------------
    // Returns the dimension of the points stored in this KDTree.
    size_t dimension() const;
    
    // size_t size() const;
    // bool empty() const;
    // Usage: if (kd.empty())
    // ----------------------------------------------------
    // Returns the number of elements in the kd-tree and whether the tree is
    // empty.
    size_t size() const;
    bool empty() const;
    
    // bool contains(const Point<N>& pt) const;
    // Usage: if (kd.contains(pt))
    // ----------------------------------------------------
    // Returns whether the specified point is contained in the KDTree.
    bool contains(const Point<N>& pt) const;
    
    // void insert(const Point<N>& pt, const ElemType& value);
    // Usage: kd.insert(v, "This value is associated with v.");
    // ----------------------------------------------------
    // Inserts the point pt into the KDTree, associating it with the specified
    // value. If the element already existed in the tree, the new value will
    // overwrite the existing one.
    void insert(const Point<N>& pt, const ElemType& value);
    
    // ElemType& operator[](const Point<N>& pt);
    // Usage: kd[v] = "Some Value";
    // ----------------------------------------------------
    // Returns a reference to the value associated with point pt in the KDTree.
    // If the point does not exist, then it is added to the KDTree using the
    // default value of ElemType as its key.
    ElemType& operator[](const Point<N>& pt);
    
    // ElemType& at(const Point<N>& pt);
    // const ElemType& at(const Point<N>& pt) const;
    // Usage: cout << kd.at(v) << endl;
    // ----------------------------------------------------
    // Returns a reference to the key associated with the point pt. If the point
    // is not in the tree, this function throws an out_of_range exception.
    ElemType& at(const Point<N>& pt);
    const ElemType& at(const Point<N>& pt) const;
    
    // ElemType kNNValue(const Point<N>& key, size_t k) const
    // Usage: cout << kd.kNNValue(v, 3) << endl;
    // ----------------------------------------------------
    // Given a point v and an integer k, finds the k points in the KDTree
    // nearest to v and returns the most common value associated with those
    // points. In the event of a tie, one of the most frequent value will be
    // chosen.
    ElemType kNNValue(const Point<N>& key, size_t k) const;

private:

    size_t length;

    KDNode<N, ElemType>* root_node;

    /* Helper function to find the node with Point pt as suggested in the lab */
    KDNode<N, ElemType>* find_node(const Point<N>& pt, KDNode<N, ElemType>* current_node, int level) const;

    /* Helper function to insert a new node into the KDTree */
    void insert_recursive(const Point <N>& pt, const ElemType value, KDNode<N, ElemType>* current_node, int level);

    /* Helper function to delete all nodes */
    void freeTree(KDNode<N, ElemType>* node);
};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDNode<N, ElemType>* find_node(const Point<N>& pt, KDNode<N, ElemType>* current_node, int level) {
    if ((current_node == nullptr) || (current_node == pt)) {
        return current_node;
    } else {
        if (pt[level] < current_node->point[level]) {
            level = (level + 1) % N;
            return find_node(pt, current_node->left_child, level);
        } else {
            level = (level + 1) % N;
            return find_node(pt, current_node->right_child, level);
        }
    }
}


template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree() {
    length = 0;
    root_node = nullptr;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::~KDTree() {
    freeTree(root_node);
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::freeTree(KDNode<N, ElemType>* node) {
    if (node == nullptr) {
        return;
    } else {
        freeTree(node->left_child);
        freeTree(node->right_child);
    }

    delete node;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::dimension() const {
    return N;
}

template <size_t N, typename ElemType>
size_t KDTree<N, ElemType>::size() const {
    return length;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::empty() const {
    return length == 0;
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::contains(const Point<N>& pt) const {
    return find_node(pt, root_node, 0) != nullptr;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert(const Point<N>& pt, const ElemType& value) {
    if (root_node = nullptr) {
        root_node = new KDNode<N, ElemType>(pt, value);
        length++;
    } else {
        insert_recursive(pt, value, root_node, 0);
    }
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert_recursive(const Point <N>& pt, const ElemType value, KDNode<N, ElemType>* current_node, int level) {
    // Incase the point already exists, update its value.
    if (current_node->point == pt) {
        current_node->value = value;
    } else {
        // traverse the KDTree..
    }
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt) {
    // TODO implement
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) {
    KDNode<N, ElemType>* node_found = find_node(pt, root_node, 0);

    if (node_found == nullptr) {
        throw out_of_range("Node was not found!");
    } else {
        return node_found->value;
    }
}


template <size_t N, typename ElemType>
const ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) const {
    KDNode<N, ElemType>* node_found = find_node(pt, root_node, 0);

    if (node_found == nullptr) {
        throw out_of_range("Node was not found!");
    } else {
        return node_found->value;
    }
}

template <size_t N, typename ElemType>
ElemType KDTree<N, ElemType>::kNNValue(const Point<N>& key, size_t k) const {
    // TODO implement
}

#endif // KDTREE_INCLUDED
