#ifndef NAVMESH_H_INCLUDED
#define NAVMESH_H_INCLUDED

#include "vector.h"

typedef enum
{
    // lol "g-spot"
    GSPOT_OPEN,
    GSPOT_BLOCKED,
    GSPOT_INTERACT_POINT,
} GridSpot;

struct navPoint
{
    int x,y;

    operator Vector2()
    {
        return Vector2(x, y);
    }
};

class Navmesh
{
public:
    static const int ROW = 20;
    static const int COL = 25;

    Navmesh();
    ~Navmesh();

    void _dbg_regen();
    void setGrid(GridSpot grid[][COL]);
    GridSpot getCellAt(int row, int col);
    void blockCellAt(int row, int col);

    static navPoint MeshPointToWorldPoint(navPoint p);
    static navPoint WorldPointToMeshPoint(navPoint p);
    static navPoint Vector2ToMeshPoint(Vector2 v);

private:
    GridSpot grid[ROW][COL];
};

#endif // NAVMESH_H_INCLUDED
