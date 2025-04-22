#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include <bits/stdc++.h>
#include <stack>

#include "renderer.h"

#define ROW 9
#define COL 10

struct cell {
    int parent_i, parent_j;
    double f,g,h;
};

bool isValid(int row, int col);
bool isUnblocked(int grid[][COL], int row, int col);
bool isDestination(int row, int col, std::pair<int,int> dest);

double calculateHValue(int row, int col, std::pair<int,int> dest);

std::stack<std::pair<int,int>> tracePath(cell cellDetails[][COL], std::pair<int,int> dest);

// returns a list of points that will be used for navigational help in the game world.
// the grid used to help find these points is called our navmesh
// the grid indices [x][y] are laid out like coordinate grids and can be used to make
// 'points' on the game world that employees are guests/customers can use to walk around
// with
void aStarSearch(int grid[][COL], std::pair<int,int> src, std::pair<int,int> dest, std::stack<std::pair<int,int>> *path);

void aStarTest(Renderer& r);

#endif // ASTAR_H_INCLUDED
