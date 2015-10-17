#include <iostream>
#include <limits>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    firstNode = nullptr;
}

// fungerar inte som det ska. Programmet körs fortfarande.
Tour::~Tour()
{
    Node* currentNode = firstNode;
    Node* tempNode;

    while (currentNode != nullptr) {
        tempNode = currentNode;
        currentNode = currentNode->next;
        delete tempNode;
    }
}

void Tour::show() const
{
    Node* currentNode = firstNode;

    // if linked list is empty print newline
    if (currentNode == nullptr) {
        cout << endl;
    } else if (currentNode->next == firstNode) { // if list only has one node, print it
        cout << currentNode->point.toString() << endl;
    } else {
        // print each node until the currentnode is equal to the firstnode
        do {
            cout << currentNode->point.toString() << endl;
            currentNode = currentNode->next;
        } while (currentNode != firstNode);
    }
}

void Tour::draw(QGraphicsScene *scene) const
{
    Node* currentNode = firstNode;
    Node* nextNode = nullptr;

    // if linked list is empty do nothing.
    if (currentNode == nullptr) {
        return;
    } else if (currentNode->next == firstNode) { // if only one node just draw it
        currentNode->point.draw(scene);
    } else { // draw all nodes until we get to the start
        do {
            nextNode = currentNode->next;
            currentNode->point.drawTo(nextNode->point, scene);
            currentNode = nextNode;
        } while(currentNode != firstNode);
    }
}

int Tour::size() const
{
    int size = 0;
    Node* currentNode = firstNode;

    // if linked list is empty it obviously has 0 nodes => size = 0
    if (currentNode == nullptr) {
        return size;
    } else if (currentNode->next == firstNode) { // if node points to itself => size = 1
        return ++size;
    }

    // go through every node in the linked list and increment size
    do {
        ++size;
        currentNode = currentNode->next;
    } while (currentNode != firstNode);

    return size;
}

double Tour::distance() const
{
    double distance = 0.0;
    Node* currentNode = firstNode;
    Node* nextNode = nullptr;

    // if linked list has 0 or 1 node it obviously doesn't have any distance so return 0.
    if (currentNode == nullptr || currentNode->next == firstNode) {
        return distance;
    }

    // go through node for node and add the distance from the previous node to the next node until we get back to the start.
    do {
        nextNode = currentNode->next;
        distance += currentNode->point.distanceTo(nextNode->point);
        currentNode = nextNode;
    } while(currentNode != firstNode);

    return distance;
}

void Tour::insertNearest(const Point p)
{
    Node* closestNode;
    Node* currentNode = firstNode;
    double lowestDistance, currentDistance;

    // if list is empty then just add it..
    if (currentNode == nullptr) {
        Node* newNode = new Node(p, nullptr);
        newNode->next = newNode;
        firstNode = newNode;
    } else {

        // set initial distance and closestNode to the first node
        closestNode = currentNode;
        lowestDistance = currentNode->point.distanceTo(p);

        // for every node in the linked list check the distance between it and the new point.
        do {
            currentDistance = currentNode->point.distanceTo(p);

            // if current distance is less than the current lowest distance we got us a winner
            if (currentDistance < lowestDistance) {
                closestNode = currentNode;
                lowestDistance = currentDistance;
            }

            currentNode = currentNode->next;
        } while(currentNode != firstNode);

        // insert the new point as a node after the closest node.
        Node* newNode = new Node(p, closestNode->next);
        closestNode->next = newNode;
    }
}

void Tour::insertSmallest(const Point p)
{
    Node* currentNode = firstNode;
    Node* bestNode = nullptr;
    double lowestDistance = std::numeric_limits<double>::max(), currentDistance = 0.0;

    // if list is empty then just add it..
    if (currentNode == nullptr) {
        Node* newNode = new Node(p, nullptr);
        newNode->next = newNode;
        firstNode = newNode;
    } else {
        // does the length change if we put the point in the first position?
        // TODO: look this up!!

        // iterate every node in the linked list and put in the new node and see distance for each one
        do {
            // add the node to the current position
            Node* newNode = new Node(p, currentNode->next);
            currentNode->next = newNode;

            // get distance
            currentDistance = distance();

            // take away the node
            currentNode->next = newNode->next;
            newNode->next = nullptr;

            // if we got a better distance overall then this is our best node.
            if (currentDistance < lowestDistance) {
                bestNode = currentNode;
                lowestDistance = currentDistance;
            }

            currentNode = currentNode->next;
        } while (currentNode != firstNode);

        // insert the node after the best node.
        Node* newNode = new Node(p, bestNode->next);
        bestNode->next = newNode;
    }
}
