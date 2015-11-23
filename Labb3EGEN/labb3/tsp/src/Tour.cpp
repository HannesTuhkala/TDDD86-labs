// This is the .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include <limits>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
	firstNode = nullptr;
}

Tour::Tour(Point a, Point b, Point c, Point d) {
	firstNode = new Node(a);
	firstNode->next = new Node(b);
	firstNode->next->next = new Node(c);
	//firstNode->next->next->next = new Node(d);
	firstNode->next->next->next = firstNode;
}

Tour::~Tour()
{
	Node* curr = firstNode->next;
	Node* temp;

	while (curr != firstNode) {
		temp = curr;
		curr = curr->next;
		delete temp;
	}
}

void Tour::show() const
{
	if (firstNode == nullptr) {
		std::cout << endl;
	} else {
		Node* curr = firstNode;
		do {
			std::cout << curr->point.toString() << endl;
			curr = curr->next;
		} while (curr != firstNode);
	}
}

void Tour::draw(QGraphicsScene *scene) const
{
	//if there are no points, there is nothing to draw.
	if (firstNode == nullptr) return;
	//if there only is one point, draw that point and you're done.
	else if (firstNode->next == firstNode) {
		firstNode->point.draw(scene);
		return;
	}
	Node* curr = firstNode;
	do {
		curr->point.drawTo(curr->next->point, scene);
		curr = curr->next;
	} while (curr != firstNode);
}

int Tour::size() const
{
	if (firstNode == nullptr) {
		return 0;
	}
	Node* curr = firstNode;
	int size = 0;
	do {
		size++;
		curr = curr->next;
	} while (curr != firstNode);
	return size;
}

double Tour::distance() const
{
	if (firstNode == nullptr || firstNode->next == firstNode) return 0;
	double distance = 0;
	Node* curr = firstNode;
	do {
		distance += curr->point.distanceTo(curr->next->point);
		curr = curr->next;
	} while (curr != firstNode);
	return distance;
}

void Tour::insertNearest(const Point& p)
{
	if (firstNode == nullptr) {
		firstNode = new Node(p);
		firstNode->next = firstNode;
		return;
	}
	Node* nearest = firstNode;
	double nearestDist = p.distanceTo(firstNode->point);
	Node* curr = firstNode->next;
	while (curr != firstNode) {
		double distance = p.distanceTo(curr->point);
		if (distance < nearestDist) {
			nearestDist = distance;
			nearest = curr;
		}
		curr = curr->next;
	}
	curr = nearest;
	Node* node = new Node(p);
	node->next = curr->next;
	curr->next = node;
}

void Tour::insertSmallest(const Point& p)
{
	if (firstNode == nullptr) {
		firstNode = new Node(p);
		firstNode->next = firstNode;
		return;
	}

	Node* curr = firstNode->next;
	Node* temp = new Node(p);
	Node* best = firstNode;
	double shortest = numeric_limits<double>::max();
	while (curr != firstNode) {
		Node* nextBackup = curr->next;
		temp->next = curr->next;
		curr->next = temp;
		double dist = distance();
		if (dist < shortest) {
			shortest = dist;
			best = curr;
		}
		curr->next = nextBackup;
		// se till att lägga in den bästa noden sen
		curr = curr->next;
	}
	temp->next = best->next;
	best->next = temp;
}

void Tour::optimize() {
	// no links can cross if there are only 3 or less points
	if (size() <= 3) return;
	//create a link (n1,n2) to be the first link.
	Node* n1 = firstNode;
	Node* n2 = firstNode->next;
	std::cout << "Starting optimization." << endl;
	int intersections;
	bool done;
	do {	//repeat everything until there are no more intersections
		done = true;
		intersections = 0;
		do { //compare every link with every other link
			//create a second link (n3,n4) to be the link after (n1,n2)
			Node* n3 = n2->next;
			Node* n4 = n3->next;
			cout << "Intersections: " << intersections << endl;
			while (n4 != n1) { //repeat until (n3,n4) has gone one lap around the list
				if (intersects(n1, n2, n3, n4)) {
					done = false;
					intersections++;
					cout << "found intersection, no " << intersections << endl;
					if (intersections == 1000) return; //TODO remove this
					if (n2->next = n3) {
						n1->next = n3;
						n2->next = n4;
						n3->next = n2;
						Node* temp = n2;
						n2 = n3;
						n3 = temp;
						cout << "Continuing..." << endl;
						continue;
					}
					//make backup of n2 and the next node
					Node* n2Backup = n2;
					Node* n2NextBackup = n2->next;
					//make n2 point to n4 to untangle part of the cross
					n2->next = n4;
					//create a current-pointer and make it point to the previous next
					//node to n2
					Node* curr = n2NextBackup;
					//reverse the links between n2 and n3 by moving (n2,curr) and 
					//redirecting the links
					int steps = 0;
					while (curr != n3) {
						steps++;
						cout << "steps: " << steps << endl;
						if (steps == 101) return;
						//make curr point to n2
						//increment n2 and curr "backwards"
						Node* currNextBackup = curr->next;
						curr->next = n2;
						n2 = curr;
						curr = currNextBackup;
					}
					cout << "Done reversing." << endl;
					//now curr is n3, make, n3 point to n2, n1 point to n3 and restore n2
					n3->next = n2;
					n1->next = n3;
					n2 = n2Backup;
				}
				//här är felet, den kommer bara loopa runt här
				n3 = n3->next;
				n4 = n4->next;
			}
			//increment (n1,n2)
			n1 = n1->next;
			n2 = n2->next;
		} while (n1 != firstNode); //stop when n1 returns to it's original position
		std::cout << intersections << " intersections found." << endl;
	} while (!done);
	std::cout << "Done optimizing" << endl;
}

//funkar inte som det ska
bool Tour::intersects(Node* n1, Node* n2, Node* n3, Node* n4) const {
	int x1 = n1->point.x;
	int y1 = n1->point.y;
	int x2 = n2->point.x;
	int y2 = n2->point.y;
	int x3 = n3->point.x;
	int y3 = n3->point.y;
	int x4 = n4->point.x;
	int y4 = n4->point.y;
/*
		Construct matrix equation: |a  b||s|  |e|
								   |c  d||t| =|f|
		The lines cross only if there is a single solution
		where t,s is in [0, 1]. 
	int a = x4 - x3;
	int b = x1 - x2;
	int c = y4 - y3;
	int d = y1 - y2;
	int e = x1 - x3;
	int f = y1 - y3;

	int det = determinant(a, b, c, d);

	if (det == 0) return false; //lines are parallel
	
	//invert the matrix : |s|		 |d -b||e|
	//					  |t| = 1/det|-c a||f|
	// compute matrix multiplication

	double s = (1/det) * (d * e - b*f);
	double t = (1/det) * (-c * e + a * f);
	return s <= 1 && s >= 0 && t <= 1 && t >= 0;*/

	return ((x3-x1)*(y2-y1) - (y3-y1)*(x2-x1)) * ((x4-x1)*(y2-y1) - (y4-y1)*(x2-x1)) < 0
	&&
	((x1-x3)*(y4-y3) - (y1-y3)*(x4-x3)) * ((x2-x3)*(y4-y3) - (y2-y3)*(x4-x3)) < 0;
}

int Tour::determinant(int a, int b, int c, int d) const {
	return a*c - b*d;
}
