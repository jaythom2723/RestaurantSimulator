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
    int i,j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            grid[i][j] = GSPOT_OPEN;
        }
    }
}

void Navmesh::setGrid(GridSpot grid[][COL])
{
    // TODO: prototype
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

navPoint Navmesh::MeshPointToWorldPoint(navPoint p)
{
    return (navPoint){ 16 + (32 * p.x), 15 + (30 * p.y) };
}

navPoint Navmesh::WorldPointToMeshPoint(navPoint p)
{
    return (navPoint){ (p.x / 32), (p.y / 30) };
}

navPoint Navmesh::Vector2ToMeshPoint(Vector2 v)
{
    return (navPoint){ (v.x / 32), (v.y / 30) };
}
