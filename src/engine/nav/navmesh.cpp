#include "navmesh.h"

#include <cstdlib>

Navmesh::Navmesh()
{
    int i,j,r;

    for(i = 0; i < ROW; i++)
    {
        for(j = 0; j < COL; j++)
        {
            r = std::rand() % 100;

            grid[i][j] = r <= 25 ? GSPOT_BLOCKED : GSPOT_OPEN;
        }
    }
}

Navmesh::~Navmesh()
{

}

void Navmesh::setGrid(GridSpot grid[][COL])
{
    // memcpy(this->grid, grid, sizeof(GridSpot) * (ROW * COL));
}

GridSpot Navmesh::getCellAt(int row, int col)
{
    return grid[row][col];
}

void Navmesh::blockCellAt(int row, int col)
{
    grid[row][col] = GSPOT_BLOCKED;
}
