#ifndef ASTTAR_H 
#define ASTAR_H

#include <vector>
#include "map.h" 
struct Node{

    Point pos ; 
    int g,h,f ; 
};
struct compareNode{
    bool operator()(const Node &a , const Node &b)const{
        return a.f > b.f ; 
    }
};
class Astar {

public :
    explicit Astar(const Map &map) : map(map){}
    std::vector<Point> findPath() ;
private :
    const Map& map;

    int heuristic(const Point& a, const Point& b) const;
    std::vector<Point> getNeighbors(const Point& p) const;
    std::vector<Point> reconstructPath(const std::vector<std::vector<Point>>& cameFrom, Point current) const;
};




















#endif