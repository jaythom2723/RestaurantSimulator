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

bool isDestination(int row, int col, navPoint dest)
{
    return (row == dest.x && col == dest.y);
}



double calculateHValue(int row, int col, navPoint dest)
{
    return (
        (double) sqrt(
            (row - dest.x) * (row - dest.y)
            + (col - dest.x) * (col - dest.y)
        )
    );
}

stack<navPoint> tracePath(cell cellDetails[][COL], navPoint dest)
{
    stack<navPoint> path;
    int row, col;

    row = dest.x;
    col = dest.y;

    while(!(cellDetails[row][col].parent_i == row
            && cellDetails[row][col].parent_j == col))
    {
        path.push((navPoint){row,col});
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path.push((navPoint){row,col});
    return path;
}

void aStarSearch(int grid[][COL], navPoint src, navPoint dest, stack<navPoint> *path)
{
    if (!isValid(src.x, src.y))
        return;

    if (!isValid(dest.x, dest.y))
        return;

    if (!isUnblocked(grid, src.x, src.y) || !isUnblocked(grid, dest.x, dest.y))
        return;

    if (isDestination(src.x, src.y, dest))
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

    i = src.x, j = src.y;
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

    navPoint src  = { 8, 0 };
    navPoint dest = { 0, 0 };
    stack<navPoint> path;

    aStarSearch(grid, src, dest, &path);

    navPoint lastPoint, curPoint;
    while(!path.empty())
    {
        lastPoint = curPoint;
        curPoint = path.top();
        path.pop();
        SDL_SetRenderDrawColor(r.getHandle(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawPoint(r.getHandle(), curPoint.x * 32, curPoint.y * 32);
    }
}
