#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    firstNode = nullptr;
}

Tour::Tour(Point a, Point b, Point c, Point d) {
    // Om vi bara har en nod i programmet.. hur gör vi så den pekar på sig själv?
    firstNode = nullptr;
    Node* aNode = new Node(a, nullptr);
    firstNode = aNode;
    aNode->next = aNode;

    Node* bNode = new Node(b, firstNode);
    aNode->next = bNode;

    Node* cNode = new Node(c, firstNode);
    bNode->next = cNode;

    Node* dNode = new Node(d, firstNode);
    cNode->next = dNode;
}

Tour::~Tour()
{
    // TODO: write this member
}

void Tour::show()
{
    Node* currentNode = firstNode;
    if (currentNode == nullptr) {
        cout << endl;
    } else if (currentNode->next == firstNode) {
        cout << currentNode->toString() << endl;
    } else {
        do {
            cout << currentNode->toString() << endl;
            currentNode = currentNode->next;
        } while (currentNode != firstNode);
    }
}

void Tour::draw(QGraphicsScene *scene)
{
    Node* currentNode = firstNode;
    Node* nextNode = nullptr;

    if (currentNode == nullptr) {
        return;
    } else if (currentNode->next == firstNode) {
        currentNode->point.draw(scene);
    }

    do {
        nextNode = currentNode->next;
        // vet inte om den här behövs
        //currentNode->point.draw(scene);
        currentNode->point.drawTo(nextNode->point, scene);
        currentNode = nextNode;
    } while(currentNode != firstNode);
}

int Tour::size()
{
    int size = 0;
    Node* currentNode = firstNode;

    if (currentNode == nullptr) {
        return size;
    } else if (currentNode->next == firstNode) {
        return ++size;
    }

    do {
        ++size;
        currentNode = currentNode->next;
    } while (currentNode != firstNode);

    return size;
}

double Tour::distance()
{
    double distance = 0.0;
    Node* currentNode = firstNode;
    Node* nextNode = nullptr;

    if (currentNode == nullptr || currentNode->next == firstNode) {
        return distance;
    }

    do {
        nextNode = currentNode->next;
        distance += currentNode->point.distanceTo(nextNode->point);
        currentNode = nextNode;
    } while(currentNode != firstNode);

    return distance;
}

void Tour::insertNearest(Point p)
{
    Node* closestNode;
    Node* currentNode = firstNode;
    double lowestDistance, currentDistance;

    if (currentNode == nullptr) {
        Node* newNode = new Node(p, nullptr);
        newNode->next = newNode;
        firstNode = newNode;
    } else {

        // set initial distance and closestNode to the first node
        closestNode = currentNode;
        lowestDistance = currentNode->point.distanceTo(p);

        do {
            currentDistance = currentNode->point.distanceTo(p);
            if (currentDistance < lowestDistance) {
                closestNode = currentNode;
                lowestDistance = currentDistance;
            }

            currentNode = currentNode->next;
        } while(currentNode != firstNode);

        Node* newNode = new Node(p, closestNode->next);
        closestNode->next = newNode;
    }
}

void Tour::insertSmallest(Point p)
{
    // TODO: write this member
}
