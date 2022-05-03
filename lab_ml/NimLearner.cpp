/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>

using std::stringstream;

/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
	stringstream ss;
	for (unsigned i = 0; i <= startingTokens; ++i) {
		//build vertex label and insert
		for (unsigned j = 1; j <= 2; ++j) {
			ss << "p" << to_string(j) << "-" << to_string(i);
			g_.insertVertex(ss.str());

			if (i == 0) {
				//no need to add edges, so move on
				ss.str("");
				continue;
			}

			if (i == startingTokens && j == 1) {
				startingVertex_ = ss.str();
			}

			ss.str("");

			unsigned max = (i == 1) ? 1 : 2;

			//add edges and set their weights to 0
			for (unsigned k = 1; k <= max; ++k) {
				stringstream ss1;
				ss << "p" << to_string(j) << "-" << to_string(i);
				if (j == 1) {
					ss1 << "p2-" << to_string(i - k);
				}
				else {
					ss1 << "p1-" << to_string(i - k);
				}
				g_.insertEdge(ss.str(), ss1.str());
				g_.setEdgeWeight(ss.str(), ss1.str(), 0);
				ss.str("");
				ss1.str("");
			}
		}
	}
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
	vector<Edge> path;
	unsigned remaining = (unsigned)std::stoi(startingVertex_.substr(3), nullptr), player = 1;
	stringstream orig, dest;
	while (remaining > 0) {
		//each turn takes 1 or 2 tokens
		unsigned tokens = rand() % 2 + 1;
		if (tokens > remaining) {
			tokens = remaining;
		}
		unsigned otherPlayer = (player == 1) ? 2 : 1;
		//get vertices and make edge
		orig << "p" << to_string(player) << "-" << to_string(remaining);
		dest << "p" << to_string(otherPlayer) << "-" << to_string(remaining - tokens);
		path.push_back(g_.getEdge(orig.str(), dest.str()));

		orig.str("");
		dest.str("");

		//switch players and remaining tokens
		player = otherPlayer;
		remaining -= tokens;
	}

	return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge>& path) {
	//find winner
	char winner = path.back().source.at(1);
	for (auto e : path) {
		if (e.source.at(1) == winner) {
			g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) + 1);
		}
		else {
			g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest) - 1);
		}
	}
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
	for (const Vertex& v : g_.getVertices()) {
		for (const Vertex& w : g_.getAdjacent(v)) {
			int weight = g_.getEdgeWeight(v, w);

			// Label all edges with positve weights as "WINPATH"
			if (weight > threshold) {
				g_.setEdgeLabel(v, w, "WIN");
			}
			else if (weight < -1 * threshold) {
				g_.setEdgeLabel(v, w, "LOSE");
			}
		}
	}
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph& NimLearner::getGraph() const {
	return g_;
}
