#ifndef NAVMESH_H_INCLUDED
#define NAVMESH_H_INCLUDED

typedef enum
{
    // lol "g-spot"
    GSPOT_OPEN,
    GSPOT_BLOCKED
} GridSpot;

struct navPoint
{
    int x,y;
};

class Navmesh
{
public:
    static const int ROW = 20;
    static const int COL = 25;

    Navmesh();
    ~Navmesh();

    void setGrid(GridSpot grid[][COL]);
    GridSpot getCellAt(int row, int col);
    void blockCellAt(int row, int col);

private:
    GridSpot grid[ROW][COL];
};

#endif // NAVMESH_H_INCLUDED
