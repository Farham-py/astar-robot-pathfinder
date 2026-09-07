#ifndef MAP_H 
#define MAP_H

#include <string>
#include <vector>

struct Point {
    int row;
    int col;

    bool operator==(const Point& other) const {
        return row == other.row && col == other.col;
    }
};

class Map {
public:
    bool load(const std::string& filename);
    bool save(const std::string& filename) const;
    void markPath(const std::vector<Point>& path);

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    Point getStart() const { return start; }
    Point getEnd() const { return end; }

    bool isInside(const Point& p) const;
    bool isWalkable(const Point& p) const;
private:
    std::vector<std::string> grid;
    int rows = 0;
    int cols = 0;
    Point start{-1, -1};
    Point end{-1, -1};

};



#endif 