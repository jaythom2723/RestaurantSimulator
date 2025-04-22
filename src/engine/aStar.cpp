#include "aStar.h"

#include <set>
#include <stack>
#include <iostream>
#include <cmath>

using namespace std;

bool isValid(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnblocked(int grid[][COL], int row, int col)
{
    return grid[row][col] == 1;
}

bool isDestination(int row, int col, pair<int,int> dest)
{
    return (row == dest.first && col == dest.second);
}



double calculateHValue(int row, int col, pair<int,int> dest)
{
    return (
        (double) sqrt(
            (row - dest.first) * (row - dest.first)
            + (col - dest.second) * (col - dest.second)
        )
    );
}

stack<pair<int,int>> tracePath(cell cellDetails[][COL], pair<int,int> dest)
{
    stack<pair<int,int>> path;
    int row, col;

    row = dest.first;
    col = dest.second;

    while(!(cellDetails[row][col].parent_i == row
            && cellDetails[row][col].parent_j == col))
    {
        path.push(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path.push(make_pair(row, col));
    return path;
}

void aStarSearch(int grid[][COL], pair<int,int> src, pair<int,int> dest, stack<pair<int,int>> *path)
{
    if (!isValid(src.first, src.second))
        return;

    if (!isValid(dest.first, dest.second))
        return;

    if (!isUnblocked(grid, src.first, src.second) || !isUnblocked(grid, dest.first, dest.second))
        return;

    if (isDestination(src.first, src.second, dest))
        return;

    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    cell cellDetails[ROW][COL];
    int i,j;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    set<pair<int,pair<int,int>>> openList;
    openList.insert(make_pair(0.0, make_pair(i, j)));

    bool foundDest = false;
    while (!openList.empty())
    {
        pair<int,pair<int,int>> p = (*openList.begin());
        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        /*
         Generating all the 8 successor of this cell

             N.W   N   N.E
               \   |   /
                \  |  /
             W----Cell----E
                  / | \
                /   |  \
             S.W    S   S.E

         Cell-->Popped Cell (i, j)
         N -->  North       (i-1, j)
         S -->  South       (i+1, j)
         E -->  East        (i, j+1)
         W -->  West           (i, j-1)
         N.E--> North-East  (i-1, j+1)
         N.W--> North-West  (i-1, j-1)
         S.E--> South-East  (i+1, j+1)
         S.W--> South-West  (i+1, j-1)*/

        double gNew, hNew, fNew;

        // north
        if (isValid(i - 1, j))
        {
            if (isDestination(i - 1, j, dest))
            {
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                printf("Destination cell is found\n");
                (*path) = tracePath(cellDetails, dest);
                foundDest = true;
                return;
            } else if ((!closedList[i - 1][j])
                       && isUnblocked(grid, i - 1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j].f == FLT_MAX
                    || cellDetails[i - 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j)));

                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                }
            }
        }

        // south
        if (isValid(i + 1, j))
        {
            if (isDestination(i + 1, j, dest))
            {
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                printf("Destination cell is found\n");
                (*path) = tracePath(cellDetails, dest);
                foundDest = true;
                return;
            } else if ((!closedList[i + 1][j]) && isUnblocked(grid, i + 1, j))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i + 1, j, dest);
                fNew = gNew + hNew;

                if (cellDetails[i + 1][j].f == FLT_MAX
                    || cellDetails[i + 1][j].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i + 1, j)));

                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                }
            }
        }

        // east
        if (isValid(i, j + 1))
        {
            if (isDestination(i, j + 1, dest))
            {
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                printf("Destination cell found\n");
                (*path) = tracePath(cellDetails, dest);
                foundDest = true;
                return;
            } else if ((!closedList[i][j + 1]) && isUnblocked(grid, i, j + 1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j + 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j + 1].f == FLT_MAX
                    || cellDetails[i][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i, j + 1)));

                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                }
            }
        }

        // west
        if (isValid(i, j - 1))
        {
            if (isDestination(i, j - 1, dest))
            {
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                printf("Destination cell is found\n");
                (*path) = tracePath(cellDetails, dest);;
                foundDest = true;
                return;
            } else if ((!closedList[i][j - 1]) && isUnblocked(grid, i, j - 1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i, j - 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i][j - 1].f == FLT_MAX
                    || cellDetails[i][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i, j - 1)));

                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                }
            }
        }

        // north east
        if (isValid(i - 1, j + 1))
        {
            if (isDestination(i - 1, j + 1, dest))
            {
                cellDetails[i - 1][j + 1].parent_i = i;
                cellDetails[i - 1][j + 1].parent_j = j;
                printf("Destination cell found\n");
                (*path) = tracePath(cellDetails, dest);;
                foundDest = true;
                return;
            } else if ((!closedList[i - 1][j + 1]) && isUnblocked(grid, i-1, j+1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j + 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j + 1].f == FLT_MAX
                    || cellDetails[i - 1][j + 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j + 1)));

                    cellDetails[i - 1][j + 1].f = fNew;
                    cellDetails[i - 1][j + 1].g = gNew;
                    cellDetails[i - 1][j + 1].h = hNew;
                    cellDetails[i - 1][j + 1].parent_i = i;
                    cellDetails[i - 1][j + 1].parent_j = j;
                }
            }
        }

        // north west
        if (isValid(i - 1, j - 1))
        {
            if (isDestination(i - 1, j - 1, dest))
            {
                cellDetails[i - 1][j - 1].parent_i = i;
                cellDetails[i - 1][j - 1].parent_j = j;
                printf("Destination cell is found\n");
                (*path) = tracePath(cellDetails, dest);;
                foundDest = true;
                return;
            } else if (!(closedList[i - 1][j - 1]) && isUnblocked(grid, i-1,j-1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i - 1, j - 1, dest);
                fNew = gNew + hNew;

                if (cellDetails[i - 1][j - 1].f == FLT_MAX
                    || cellDetails[i - 1][j - 1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i - 1, j - 1)));

                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                }
            }
        }

        // south east
        if (isValid(i+1,j+1))
        {
            if (isDestination(i+1,j+1,dest))
            {
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                printf("Destination cell found\n");
                (*path) = tracePath(cellDetails, dest);;
                foundDest = true;
                return;
            } else if ((!closedList[i+1][j+1]) && isUnblocked(grid,i+1,j+1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1,j+1,dest);
                fNew = gNew+hNew;

                if (cellDetails[i+1][j+1].f == FLT_MAX
                    || cellDetails[i+1][j+1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i+1,j+1)));

                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                }
            }
        }

        // south west
        if (isValid(i+1,j-1))
        {
            if (isDestination(i+1,j-1,dest))
            {
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;
                printf("Destination cell found\n");
                (*path) = tracePath(cellDetails, dest);;
                foundDest = true;
                return;
            } else if ((!closedList[i+1][j-1]) && isUnblocked(grid, i+1, j-1))
            {
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculateHValue(i+1,j-1,dest);
                fNew = gNew + hNew;

                if (cellDetails[i+1][j-1].f == FLT_MAX
                    || cellDetails[i+1][j-1].f > fNew)
                {
                    openList.insert(make_pair(fNew, make_pair(i+1, j-1)));

                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                }
            }
        }
    }

    if (!foundDest)
        printf("Failed to find the destination cell\n");

    return;
}

void aStarTest(Renderer& r)
{
    int grid[ROW][COL]
        = { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
            { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
            { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
            { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
            { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
            { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } };

    pair<int,int> src = make_pair(8,0);
    pair<int,int> dest = make_pair(0,0);
    stack<pair<int,int>> path;
    int i;

    aStarSearch(grid, src, dest, &path);

    pair<int,int> lastPoint, curPoint;
    while(!path.empty())
    {
        lastPoint = curPoint;
        curPoint = path.top();
        path.pop();
        SDL_SetRenderDrawColor(r.getHandle(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawPoint(r.getHandle(), curPoint.first * 32, curPoint.second * 32);
    }
}
