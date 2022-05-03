/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

using std::vector;

int min(int a, int b) {
	if (a < b)
		return a;
	else
		return b;
}

NetworkFlow::NetworkFlow(Graph& startingGraph, Vertex source, Vertex sink) : g_(startingGraph), residual_(Graph(true, true)), flow_(Graph(true, true)), source_(source), sink_(sink) {
	//flow graph is all edges set to 0
	//residue graph is copy of startinGraph, with reverse edges set to 0

	vector<Edge> edges = g_.getEdges();
	for (auto e : edges) {
		flow_.insertEdge(e.source, e.dest);
		flow_.setEdgeWeight(e.source, e.dest, 0);

		residual_.insertEdge(e.source, e.dest);
		residual_.setEdgeWeight(e.source, e.dest, e.getWeight());
		residual_.insertEdge(e.dest, e.source);
		residual_.setEdgeWeight(e.dest, e.source, 0);
	}
}

/**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
									 std::vector<Vertex>& path, std::set<Vertex>& visited) {
	if (visited.count(source) != 0)
		return false;
	visited.insert(source);

	if (source == sink) {
		return true;
	}

	vector<Vertex> adjs = residual_.getAdjacent(source);
	for (auto it = adjs.begin(); it != adjs.end(); it++) {
		if (visited.count(*it) == 0 && residual_.getEdgeWeight(source, *it) > 0) {
			path.push_back(*it);
			if (findAugmentingPath(*it, sink, path, visited))
				return true;
			else {
				path.pop_back();
			}
		}
	}

	return false;
}

/**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex>& path) {
	std::set<Vertex> visited;
	path.clear();
	path.push_back(source);
	return findAugmentingPath(source, sink, path, visited);
}

/**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex>& path) const {
	// YOUR CODE HERE
	int cap = INT_MAX;
	for (unsigned i = 0; i < path.size() - 1; ++i) {
		if (residual_.getEdgeWeight(path[i], path[i + 1]) < cap) {
			cap = residual_.getEdgeWeight(path[i], path[i + 1]);
		}
	}
	return cap;
}

/**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph& NetworkFlow::calculateFlow() {
	vector<Vertex> p;
	while (findAugmentingPath(source_, sink_, p)) {
		int cap = pathCapacity(p);
		for (unsigned i = 0; i < p.size() - 1; ++i) {
			Edge edge;
			if (flow_.edgeExists(p[i], p[i + 1])) {
				edge = flow_.getEdge(p[i], p[i + 1]);
			}
			else {
				edge = flow_.getEdge(p[i + 1], p[i]);
			}

			//set weights
			Edge res = residual_.getEdge(edge.source, edge.dest);
			residual_.setEdgeWeight(res.source, res.dest, res.getWeight() - cap);
			residual_.setEdgeWeight(res.dest, res.source, res.getWeight() + cap);
			flow_.setEdgeWeight(edge.source, edge.dest, edge.getWeight() + cap);
		}
		p.clear();
	}

	vector<Vertex> adj = flow_.getAdjacent(source_);
	int flow = 0;
	for (unsigned i = 0; i < adj.size(); ++i) {
		flow += flow_.getEdgeWeight(source_, adj[i]);
	}
	maxFlow_ = flow;
	return flow_;
}

int NetworkFlow::getMaxFlow() const {
	return maxFlow_;
}

const Graph& NetworkFlow::getGraph() const {
	return g_;
}

const Graph& NetworkFlow::getFlowGraph() const {
	return flow_;
}

const Graph& NetworkFlow::getResidualGraph() const {
	return residual_;
}
