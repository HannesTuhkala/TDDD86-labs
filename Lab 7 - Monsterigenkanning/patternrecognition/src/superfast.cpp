#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"

using namespace std;
// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

/*
 * A data structure that helps us to compare a point to a starting point.
 */
struct PointComparison {
	/*
	 * The point which all other points compare to.
	 */
	Point* comparePoint;
	/*
	 * The point to compare with.
	 */
	Point* thisPoint;
	/*
	 * The slope between the points.
	 */
	double slope;
	/*
	 * Constructs a PointComparison and calculates the slope between the two points.
	 */
	PointComparison(Point* comparePoint, Point* thisPoint) {
		this->comparePoint = comparePoint;
		this->thisPoint = thisPoint;
		this->slope = comparePoint->slopeTo(*thisPoint);
	}

	bool operator <(const PointComparison &other) const {
		if (this->slope != other.slope) {
			return this->slope < other.slope;
		} else {
			return *this->thisPoint < *other.thisPoint;
		}
	}
	
	bool operator >(const PointComparison &other) const {
		return other < *this;
	}
};

void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    
	// open file
    string filename = "input6400.txt";
    ifstream input;
    input.open(filename);


    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    // the vector of points
    vector<Point> points;
	// a vector of pointers to the points in points
	vector<Point*> pointPointers;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
		Point* p = new Point(x, y);
        points.push_back(*p);
		pointPointers.push_back(p);
    }
    input.close();
	
    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Extra Fast Pattern Recognition");
    view->show();
    auto begin = chrono::high_resolution_clock::now();
	//do all of this using each point as starting point
	for (int startingPoint = 0; startingPoint < N; ++startingPoint) {
		vector<PointComparison> comparisons;
		//iterate over all except the starting point. Instead of
		//checking each point if it is a starting point, iterate first
		//over all points until the starting point, and then after.
		for (int i = 0; i < startingPoint; ++i) {
			//for every point that isn't the starting point, create a PointComparison of 
			//the starting point pointer and the point pointer at index i.
			comparisons.push_back(PointComparison(pointPointers[startingPoint], pointPointers[i]));
		}
		for (int i = startingPoint + 1; i < N; ++i) {
			//do the same here.
			comparisons.push_back(PointComparison(pointPointers[startingPoint], pointPointers[i]));
		}
		//sort the comparisons by slope
		sort(comparisons.begin(), comparisons.end());

		//start finding collinear lines. Create an index variable.
		int i = 0;
		//since we are checking two points ahead, and checking every point except the starting point,
		//we check from i = 0 to N-1-2 = N-3.
		while (i < N - 3) {
			//get the slopes of this index and the one two indexes away
			double slope1 = comparisons[i].slope;
			double slope2 = comparisons[i + 2].slope;
			//if they are equal, that means we have found four aligned points (including the startingPoint)!
			//Lets see if we can find more...
			//EXTRATASK E8: Because of how the list is sorted, several equal slopes in a row will be sorted
			//lexicographically, which means that the last of these points will be the upmost right point.
			//This also means that the starting point is the downmost left point if and only if it follows
			//the order of the comparison list. That is, only if it is "less" than the first point with equal
			//slope. Since we only want to draw one single line segment between these lines, we include this
			//as a condition to draw the line.
			if (slope1 == slope2 && *comparisons[0].comparePoint < *comparisons[i].thisPoint) {
				int j = i + 3;
				while (slope1 == comparisons[j].slope && j < N - 1) {
					//we found another aligned point!
					j++;
				}
				//okay, so the compared point at comparisons[j] was not aligned, so we will
				//just draw a line from the starting point to the one at j-1 (since that was the 
				//last aligned point). We use comparisons[0] to get the starting point but
				//we could just use any element in comparisons since they all have the same
				//pointer to the starting point.
                render_line(scene, *comparisons[0].comparePoint, *comparisons[j-1].thisPoint);
                a.processEvents(); // show rendered line
				//continue searching from where the last aligned point was found.
				i = j - 1;
			} else {
				//okay, we didn't find aligned points here, increment and continue.
				i++;
			}
		}
	}
	//And we're done! Pause the timer.
    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;
	return a.exec();
}
