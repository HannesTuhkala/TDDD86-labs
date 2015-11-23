/*
 * TDDD86 TSP
 * This client program uses your Tour class and contains the 'main'
 * function to open the input file and set up the program's primitive GUI.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chrono>
#include <thread>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Point.h"
#include "Tour.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
	Tour tour;
	bool shit = tour.intersects(new Node(Point(1, 1)), new Node(Point(2, 3)),
					new Node(Point(4, 4)), new Node(Point(10, 1)));
	cout << shit << endl;
    /*string filename = "/Users/Malcolm/Google Drive/C++/Labb3EGEN/labb3/tsp/res/tsp10.txt";
    ifstream input;
    input.open(filename);	

    // get dimensions
    int width;
    int height;
    input >> width;
    input >> height;
    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene();
    view->setScene(scene);
    view->scale(1, -1); //screen y-axis is inverted
    view->setSceneRect(0, 0, width, height);
    view->show();

    // run insertion heuristic
    Tour tour;
    double x;
    double y;
    while (input >> x >> y) {
        Point p(x, y);
        tour.insertNearest(p);*/
    /*    tour.draw(scene);
		std::chrono::milliseconds dura(50);
		std::this_thread::sleep_for(dura);
        a.processEvents();*/
    /*}
    input.close();
	tour.optimize();
    // print tour to standard output
    cout << "Tour distance: " << std::fixed << std::setprecision(4)
         << std::showpoint << tour.distance() << endl;
    cout << "Number of points: " << tour.size() << endl;
    tour.show();

    // draw tour
	tour.draw(scene);*/
    return a.exec(); // start Qt event loop
}
