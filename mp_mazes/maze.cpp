#include "maze.h"
#include <vector>

//stuff for random generation
// #include <cstdlib>
// #include <ctime>
#include <time.h>
#include <random>

#include <queue>

using std::queue;
using std::rand;
using std::vector;

//constructor to create empty maze
SquareMaze::SquareMaze() {
	_width = 0;
	_height = 0;
	_maze = NULL;
}

//copy constructor
SquareMaze::SquareMaze(const SquareMaze& other) {
	_copy(other);
}

//copy assignment operator
SquareMaze& SquareMaze::operator=(const SquareMaze& other) {
	if (this != &other) {
		_destroy();
		_copy(other);
	}
	return *this;
}

//destructor
SquareMaze::~SquareMaze() {
	_destroy();
}

//constructs maze with given width and height
//clear existing maze if needed
//param: width and height are dimensions of the maze
void SquareMaze::makeMaze(int width, int height) {
	//delete existing maze if needed
	if (_maze != NULL) {
		_destroy();
	}

	//build maze with all walls existing
	_width = width;
	_height = height;
	_buildMaze();

	//remove walls randomly until no walls
	//can be removed without creating a cycle
	//if all elements not in same set, there
	//must be some wall that can be removed

	//random number generator
	timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	std::default_random_engine rng(ts.tv_nsec);
	//std::srand(std::time(0));
	while (_dset.size(0) < (int)_dset._up.size()) {
		int x = rng() % _width;
		int y = rng() % _height;
		int dir = rng() % 2;

		switch (dir) {
			case 0:
				if (x < _width - 1 && !canTravel(x, y, dir)) {
					if (_dset.find(y * _width + x) == _dset.find(y * _width + (x + 1))) {
						break;
					}
					setWall(x, y, dir, false);
					_dset.setunion(y * _width + x, y * _width + (x + 1));
				}
				break;
			case 1:
				if (y < _height - 1 && !canTravel(x, y, dir)) {
					if (_dset.find(y * _width + x) == _dset.find((y + 1) * _width + x)) {
						break;
					}
					setWall(x, y, dir, false);
					_dset.setunion(y * _width + x, (y + 1) * _width + x);
				}
				break;
		}
	}
}

//returns if can travel in dir at (x, y)
//param: dir is direction to travel in:
//       0 = right, 1 = down, 2 = left, 3 = up
//       x and y specifies the location to travel from
bool SquareMaze::canTravel(int x, int y, int dir) const {
	//check bounds
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return false;

	switch (dir) {
		case 0:
			if (x == _width - 1) {
				return false;
			}
			return !_maze[y][x]._right;
		case 1:
			if (y == _height - 1) {
				return false;
			}
			return !_maze[y][x]._down;
		case 2:
			if (x == 0) {
				return false;
			}
			return !_maze[y][x - 1]._right;
		case 3:
			if (y == 0) {
				return false;
			}
			return !_maze[y - 1][x]._down;
		default:
			return false;
	}
}

//sets if specified wall exists or not
//param: x and y is the cell of the wall,
//       dir is the direction of the wall in relation the cell
//       0 = right, 1 = down
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
	if (dir == 0) {
		_maze[y][x]._right = exists;
	}
	else if (dir == 1) {
		_maze[y][x]._down = exists;
	}
}

//returns a vector of directions to solve the maze
//path is from top left(start) to cell in bottom row(end)
//end is chosen as the cell with longest distance to start on bottom row
vector<int> SquareMaze::solveMaze() const {
	//note: given maze has no cycles, there is
	//only one path from origin to any square on bottom row
	vector<int> ans;
	// vector<int> pred;
	queue<int> q;
	bool* visited = new bool[_height * _width];
	int* prev = new int[_height * _width];
	int* path = new int[_height * _width];
	int dest = -1;

	//setup variables
	q.push(0);
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			visited[i * _width + j] = false;
			prev[i * _width + j] = -1;
			path[i * _width + j] = -1;
		}
	}

	//solve
	while (q.size() > 0) {
		int x = q.front() % _width;
		int y = q.front() / _width;
		q.pop();
		if (y == _height - 1) {
			//mark as possible answer?
			dest = y * _width + x;
		}
		//adjacent edges
		for (int i = 0; i < 4; ++i) {
			int next;
			switch (i) {
				case 0:
					next = y * _width + (x + 1);
					break;
				case 1:
					next = (y + 1) * _width + x;
					break;
				case 2:
					next = y * _width + (x - 1);
					break;
				case 3:
					next = (y - 1) * _width + x;
					break;
			}
			if (canTravel(x, y, i) && !visited[next]) {
				q.push(next);
				visited[next] = true;
				prev[next] = y * _width + x;
				path[next] = i;
			}
		}
	}
	while (dest != 0) {
		ans.insert(ans.begin(), path[dest]);
		//ans.push_back(path[dest]);
		dest = prev[dest];
	}

	delete[] visited;
	delete[] prev;
	delete[] path;

	return ans;
}

//returns a new PNG with maze drawn without solution
PNG* SquareMaze::drawMaze() const {
	PNG* ans = new PNG(_width * 10 + 1, _height * 10 + 1);
	//blacken topmost row
	for (unsigned x = 0; x < ans->width(); ++x) {
		if (x == 0 || x > 9) {
			HSLAPixel& p = ans->getPixel(x, 0);
			p.l = 0;
		}
	}
	//blacken leftmost column
	for (unsigned y = 0; y < ans->height(); ++y) {
		HSLAPixel& p = ans->getPixel(0, y);
		p.l = 0;
	}
	//blacken walls
	for (int x = 0; x < _width; ++x) {
		for (int y = 0; y < _height; ++y) {
			if (_maze[y][x]._right) {
				for (int k = 0; k <= 10; ++k) {
					HSLAPixel& p = ans->getPixel((x + 1) * 10, y * 10 + k);
					p.l = 0;
				}
			}
			if (_maze[y][x]._down) {
				for (int k = 0; k <= 10; ++k) {
					HSLAPixel& p = ans->getPixel(x * 10 + k, (y + 1) * 10);
					p.l = 0;
				}
			}
		}
	}
	return ans;
}

//returns a maze drawn with the solution
PNG* SquareMaze::drawMazeWithSolution() const {
	PNG* maze = drawMaze();
	vector<int> solution = solveMaze();
	int x = 5, y = 5;
	for (auto dir : solution) {
		for (int i = 0; i < 11; ++i) {
			HSLAPixel& p = maze->getPixel(x, y);
			p.h = 0;
			p.s = 1;
			p.l = 0.5;
			p.a = 1;

			if (i == 10) {
				break;
			}

			switch (dir) {
				case 0:
					x++;
					break;
				case 1:
					y++;
					break;
				case 2:
					x--;
					break;
				case 3:
					y--;
					break;
			}
		}
	}
	int i = y / 10, j = x / 10;
	for (unsigned k = 1; k <= 9; ++k) {
		HSLAPixel& p = maze->getPixel(j * 10 + k, (i + 1) * 10);
		p.l = 1;
	}
	return maze;
}

//big three helpers
void SquareMaze::_destroy() {
	_dset._up.clear();
	for (int i = 0; i < _height; ++i) {
		delete[] _maze[i];
	}
	delete[] _maze;
}

void SquareMaze::_copy(const SquareMaze& other) {
	_width = other._width;
	_height = other._height;
	_buildMaze();
}

void SquareMaze::_buildMaze() {
	_dset.addelements(_height * _width);
	_maze = new Square*[_height];
	for (int i = 0; i < _height; ++i) {
		_maze[i] = new Square[_width];
	}
}