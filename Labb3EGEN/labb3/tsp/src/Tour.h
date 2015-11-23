// This is the .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:
	/*
	*	Contructor: initializes first node
	*/
    Tour();
	Tour(Point a, Point b, Point c, Point d);
	/*
	*	Destructor
	*/	
    ~Tour();
	/*
	*	
	*/
    void show() const;
    void draw(QGraphicsScene* scene) const;
    int size() const;
    double distance() const;
    void insertNearest(const Point& p);
    void insertSmallest(const Point& p);
	void optimize();
	bool intersects(Node* n1, Node* n2, Node* n3, Node* n4) const;

private:
	// The first node
	Node* firstNode;
	int determinant(int a, int b, int c, int d) const;
};

#endif // TOUR_H
