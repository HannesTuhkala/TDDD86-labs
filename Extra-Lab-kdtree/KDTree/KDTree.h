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

    KDNode(Point<N> point, ElemType value) : point(point), value(value),left_child(nullptr), right_child(nullptr){}

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

    /* How many elements there are in the KDTree */
    size_t length;

    /* The root node of our KDTree */
    KDNode<N, ElemType>* root_node;

    /* Helper function to find the node with Point pt as suggested in the lab */
    KDNode<N, ElemType>* find_node(const Point<N>& pt, KDNode<N, ElemType>* current_node, int level) const;

    /* Helper function to insert a new node into the KDTree */
    void insert_node_recursive(const Point <N>& pt, const ElemType value, KDNode<N, ElemType>* current_node, int level);

    /* Creates a new KDNode and inserts it into the KDTree. The flag 'side' determines if to put it in as a left child
     * or as a right child of current_node. side = false => left side. side = true => right side. */
    void insert_node(KDNode<N, ElemType>* current_node, const Point <N>& pt, const ElemType value, bool side);

    /* Helper function to traverse the kdtree and add closest points to the bpq */
    void kNN_recursive(KDNode<N, ElemType>* current_node, const Point<N>& key,
                       BoundedPQueue<ElemType>& bpq, int level) const;

    /* Returns whether there could be closer nodes in the other side */
    bool isOtherPartPlane(KDNode<N, ElemType>* current_node, const Point<N>& key,
                                               BoundedPQueue<ElemType>& bpq, int level) const;

    /* Helper function to traverse the tree and copy it to a new one */
    KDNode<N, ElemType>* copy_recursive(KDNode<N, ElemType>* current_node);

        /* Helper function to delete all nodes */
    void freeTree(KDNode<N, ElemType>* node);
};

/** KDTree class implementation details */

template <size_t N, typename ElemType>
KDNode<N, ElemType>* KDTree<N, ElemType>::find_node(const Point<N>& pt, KDNode<N, ElemType>* current_node, int level) const {
    if ((current_node == nullptr) || (current_node->point == pt)) {
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
    if (root_node == nullptr) {
        root_node = new KDNode<N, ElemType>(pt, value);
        length++;
    } else {
        insert_node_recursive(pt, value, root_node, 0);
    }
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert_node_recursive(const Point <N>& pt, const ElemType value, KDNode<N, ElemType>* current_node, int level) {
    // Incase the point already exists, update its value.
    if (current_node->point == pt) {
        current_node->value = value;
    } else {
        if (pt[level] < current_node->point[level]) {
            /* if left child doesnt exist, insert the node here,
               otherwise continue down the tree from left_child. */
            if (current_node->left_child == nullptr) {
                insert_node(current_node, pt, value, false);
            } else {
                insert_node_recursive(pt, value, current_node->left_child, (level + 1) % N);
            }
        } else {
            /* if right child doesnt exist, insert the node here,
               otherwise continue down the tree from right_child. */
            if (current_node->right_child == nullptr) {
                insert_node(current_node, pt, value, true);
            } else {
                insert_node_recursive(pt, value, current_node->right_child, (level + 1) % N);
            }
        }
    }
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::insert_node(KDNode<N, ElemType>* current_node, const Point <N>& pt, const ElemType value, bool side) {
    (!side) ? current_node->left_child = new KDNode<N, ElemType>{pt, value} :
              current_node->right_child = new KDNode<N, ElemType>{pt, value};

    length++;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::operator[](const Point<N>& pt) {
    // if the point isnt in the kdtree, insert it and return the value
    KDNode<N, ElemType>* found_node = find_node(pt, root_node, 0);
    if (found_node == nullptr) {
        insert(pt, ElemType());
        return find_node(pt, root_node, 0)->value;
    }

    return found_node->value;
}

template <size_t N, typename ElemType>
ElemType& KDTree<N, ElemType>::at(const Point<N>& pt) {
    // if the point isnt in the kdtree, insert it and return the value
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
    BoundedPQueue<ElemType> bpq(k);
    kNN_recursive(root_node, key, bpq, 0);

    std::map<ElemType, size_t> priority_map;

    // traverse the bpq and add them into the priority map
    while (!bpq.empty()) {
        priority_map[bpq.dequeueMin()]++;
    }

    // set the current best element to the first element in the map
    ElemType best_element = priority_map.begin()->first;
    size_t best_priority = priority_map.begin()->second;

    /* traverse the whole map until we find better elements or until
       it has been fully traversed */
    for (auto it : priority_map) {
        if (it.second > best_priority) {
            best_element = it.first;
            best_priority = it.second;
        }
    }

    return best_element;
}

template <size_t N, typename ElemType>
void KDTree<N, ElemType>::kNN_recursive(KDNode<N, ElemType>* current_node, const Point<N>& key,
                                        BoundedPQueue<ElemType>& bpq, int level) const {
    if (current_node == nullptr) {
        return;
    }

    // put the current point into the bpq
    bpq.enqueue(current_node->value, Distance(current_node->point, key));

    // continue with the left & right child
    if (key[level] < current_node->point[level]) {
        kNN_recursive(current_node->left_child, key, bpq, (level + 1) % N);

        /* if there are less element in the bpq than the max size we allocated or
           there could be points closer on the other side of the plane (in this case) */
        if (bpq.size() < bpq.maxSize() || isOtherPartPlane(current_node, key, bpq, level)) {
            kNN_recursive(current_node->right_child, key, bpq, (level + 1) % N);
        }
    } else {
        kNN_recursive(current_node->right_child, key, bpq, (level + 1) % N);

        /* if there are less element in the bpq than the max size we allocated or
           there could be points closer on the other side of the plane (in this case) */
        if (bpq.size() < bpq.maxSize() || isOtherPartPlane(current_node, key, bpq, level)) {
            kNN_recursive(current_node->left_child, key, bpq, (level + 1) % N);
        }
    }
}

template <size_t N, typename ElemType>
bool KDTree<N, ElemType>::isOtherPartPlane(KDNode<N, ElemType>* current_node, const Point<N>& key,
                                           BoundedPQueue<ElemType>& bpq, int level) const {
    return (current_node->point[level] - key[level]) < bpq.worst();
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>::KDTree(const KDTree& rhs) {
    *this = rhs;
}

template <size_t N, typename ElemType>
KDTree<N, ElemType>& KDTree<N, ElemType>::operator=(const KDTree& rhs) {
    root_node = copy_recursive(rhs.root_node);
    length = rhs.length;

    return *this;
}

template <size_t N, typename ElemType>
KDNode<N, ElemType>* KDTree<N, ElemType>::copy_recursive(KDNode<N, ElemType>* current_node) {
    if (current_node == nullptr) {
        return current_node;
    } else {
        KDNode<N, ElemType>* new_node = new KDNode<N, ElemType>(current_node->point, current_node->value);

        new_node->left_child = copy_recursive(current_node->left_child);
        new_node->right_child = copy_recursive(current_node->right_child);

        return new_node;
    }
}

#endif // KDTREE_INCLUDED
