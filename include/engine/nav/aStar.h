#ifndef ASTAR_H_INCLUDED
#define ASTAR_H_INCLUDED

#include <bits/stdc++.h>
#include <stack>

#include "renderer.h"
#include "navmesh.h"

struct cell
{
    int parent_i, parent_j;
    double f,g,h;
};

bool isValid(int row, int col);
bool isUnblocked(Navmesh& mesh, int row, int col);
bool isDestination(int row, int col, navPoint dest);

double calculateHValue(int row, int col, navPoint dest);

std::stack<navPoint> tracePath(cell cellDetails[][Navmesh::COL], navPoint dest);

// returns a list of points that will be used for navigational help in the game world.
// the grid used to help find these points is called our navmesh
// the grid indices [x][y] are laid out like coordinate grids and can be used to make
// 'points' on the game world that employees are guests/customers can use to walk around
// with
void aStarSearch(Navmesh& mesh, navPoint src, navPoint dest, std::stack<navPoint> *path);

#endif // ASTAR_H_INCLUDED
