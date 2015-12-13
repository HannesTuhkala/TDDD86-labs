#include "costs.h"
#include "trailblazer.h"
#include <queue>
#include <stack>
using namespace std;

vector<Node*> DFSHelp(BasicGraph& graph, Vertex* start, Vertex* end) {
	//mark the start node as visited and green.
	start->visited = true;
	start->setColor(GREEN);
	//if the start equals the end, we have reached the end. Return a 
	//vector with those two pointers.
	if (start == end) {
		vector<Vertex*> path;
		path.push_back(start);
		path.push_back(end);
		return path;
	} 
	//if we haven't reached the end, start looking for ways to branch.
	//Gather all neighbors to the start node.
	for (Arc* arc : start->arcs) {
		Vertex* neighbor = arc->finish;
		//if it hasn't been visited already...
		if (!neighbor->visited) {
			vector<Node*> tempPath = DFSHelp(graph, neighbor, end);
			//if the path along this neighbor didn't lead to a dead-end,
			//the tempPath contains a path to the end. Return this path
			//with the start node as the first node in the vector.
			if (!tempPath.empty()) {
				vector<Vertex*> path;
				path.push_back(start);
				for (Vertex* v : tempPath) {
					path.push_back(v);
				}
				return path;
			}
		}
	}
	//if we made it here, either the start node has no neighbors or the neighbors
	//don't lead us to the end. Return an empty path and mark the node gray.
    vector<Vertex*> path;
	start->setColor(GRAY);
    return path;
}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
	graph.resetData();
	return DFSHelp(graph, start, end);
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
	//create an empty vector to store the path, and a queue to keep track of which
	//node to visit next.
    vector<Vertex*> path;
	queue<Vertex*> queue;
	//the start node should be visited first.
	start->setColor(YELLOW);
	start->visited = true;
	queue.push(start);
	while (!queue.empty()) {
		Vertex* curr = queue.front();
		queue.pop();
		curr->setColor(GREEN);
		if (curr == end) break;
		for (Arc* arc : curr->arcs) {
			Vertex* neighbor = arc->finish;
			if (!neighbor->visited) {
				neighbor->visited = true;
				neighbor->previous = curr;
				neighbor->setColor(YELLOW);
				queue.push(neighbor);
			}
		}
	}
	//start reconstructing path using a stack to reverse the order
	stack<Vertex*> temp;
	while (start != end) {
		temp.push(end);
		end = end->previous;
	}
	temp.push(start);
	while (!temp.empty()) {
		path.push_back(temp.top());
		temp.pop();
	}
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    // TODO: implement this function; remove these comments
    //       (The function body code provided below is just a stub that returns
    //        an empty vector so that the overall project will compile.
    //        You should remove that code and replace it with your implementation.)
    vector<Vertex*> path;
    return path;
}
