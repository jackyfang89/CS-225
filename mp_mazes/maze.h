/* Your code here! */
#pragma once

#include "dsets.h"
#include "cs225/PNG.h"
#include <vector>

using std::vector;
using namespace cs225;

//SquareMaze class
//!D array of Squares

class SquareMaze {
public:
	//constructor to create empty maze
	SquareMaze();

	//copy constructor
	SquareMaze(const SquareMaze& other);

	//copy assignment operator
	SquareMaze& operator=(const SquareMaze& other);

	//destructor
	~SquareMaze();

	//constructs maze with given width and height
	//param: width and height are dimensions of the maze
	void makeMaze(int width, int height);

	//returns if can travel in dir at (x, y)
	//param: dir is direction to travel in:
	//       0 = right, 1 = down, 2 = left, 3 = up
	//       x and y specifies the location to travel from
	bool canTravel(int x, int y, int dir) const;

	//sets if specified wall exists or not
	//param: x and y is the cell of the wall,
	//       dir is the direction of the wall in relation the cell
	//       0 = right, 1 = down
	void setWall(int x, int y, int dir, bool exists);

	//returns a vector of directions to solve the maze
	//path is from top left(start) to cell in bottom row(end)
	//end is chosen as the cell with longest distance to start on bottom row
	vector<int> solveMaze() const;

	//returns a new PNG with maze drawn without solution
	PNG* drawMaze() const;

	//returns a maze drawn with the solution
	PNG* drawMazeWithSolution() const;

private:
	//track each square's right and down walls.
	//_right and _down mark if the walls exist.
	class Square {
	public:
		Square() {
			_right = true;
			_down = true;
		}
		Square(bool right, bool down) {
			_right = right;
			_down = down;
		}
		bool _right;
		bool _down;
	};

	//represent the maze as a disjoint set
	//each cell is numbered like a 2D array
	//represented as a 1D aray
	//ex. 2D[i][j] = 1D[i*colCount + j]
	DisjointSets _dset;

	Square** _maze;

	//Square** _maze;
	int _width, _height;

	//helpers for big three
	void _destroy();
	void _copy(const SquareMaze& other);
	void _buildMaze();
};