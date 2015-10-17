#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

/*
 * A circular linked list of Nodes.
*/
class Tour {
public:

    /*
     * Constructor: initializes the first node.
     */
    Tour();
    /*
     * Destructor: deletes every node in the linked list.
     */
    ~Tour();
    /*
     * Prints each node to standard output.
     */
    void show() const;
    /*
     * Draws each node as a line from the previous node to the next node.
     */
    void draw(QGraphicsScene* scene) const;
    /*
     * Returns how many nodes there are in the linked list at the moment.
     */
    int size() const;
    /*
     * Returns the total distance around the nodes from the startnode to the endnode.
     */
    double distance() const;
    /*
     * Inserts the Point p after the node which the distance is the closest/lowest.
     */
    void insertNearest(const Point p);
    /*
     * Inserts the Point p after the node that is the most optimal. Iterates the linked list to find the total length of it and where to put the Point p.
     */
    void insertSmallest(const Point p);

private:
    /*
     * Our initial node
    */
    Node* firstNode;
};

#endif // TOUR_H
