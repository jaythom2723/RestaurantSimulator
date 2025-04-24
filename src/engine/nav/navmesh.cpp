#include "navmesh.h"

#include "common.h"

#include <ctime>

Navmesh::Navmesh()
{
    std::srand(std::time(nullptr));
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

void Navmesh::_dbg_regen()
{
    std::srand(std::time(nullptr));
    int i,j,r;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            r = std::rand() % 100;
            grid[i][j] = r <= 10 ? GSPOT_BLOCKED : GSPOT_OPEN;
        }
    }
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
