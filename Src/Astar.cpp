#include "AStar.h"
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <queue>

using namespace std;

int Astar::heuristic(const Point& a, const Point& b) const {
    
    return abs(a.row - b.row) + abs(a.col - b.col);
}


vector<Point> Astar::getNeighbors(const Point& p) const {
    vector<Point> neighbors;
    const int dRow[] = {-1, 1, 0, 0};
    const int dCol[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        Point next{p.row + dRow[i], p.col + dCol[i]};
        if (map.isWalkable(next)) {
            neighbors.push_back(next);
        }
    }
    return neighbors;
}
vector<Point> Astar::reconstructPath(const vector<vector<Point>>& cameFrom, Point current) const {
    vector<Point> path;
    while (!(current.row == -1 && current.col == -1)) {
        path.push_back(current);
        current = cameFrom[current.row][current.col];
    }
    reverse(path.begin(), path.end()); 
    return path;
}
vector<Point> Astar::findPath() {
    int rows = map.getRows();
    int cols = map.getCols();
    Point start = map.getStart();
    Point end = map.getEnd();

    vector<vector<int>> gScore(rows, vector<int>(cols, INT_MAX));
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<Point>> cameFrom(rows, vector<Point>(cols, Point{-1, -1}));

    priority_queue<Node, vector<Node>, compareNode> openSet;

    gScore[start.row][start.col] = 0;
    int startH = heuristic(start, end);
    openSet.push({start, 0, startH, startH});

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (visited[current.pos.row][current.pos.col]) {
            continue; 
        }
        visited[current.pos.row][current.pos.col] = true;

        if (current.pos == end) {
            return reconstructPath(cameFrom, current.pos);
        }

        for (const Point& neighbor : getNeighbors(current.pos)) {
            if (visited[neighbor.row][neighbor.col]) {
                continue;
            }

            int tentativeG = current.g + 1; 
            if (tentativeG < gScore[neighbor.row][neighbor.col]) {
                gScore[neighbor.row][neighbor.col] = tentativeG;
                cameFrom[neighbor.row][neighbor.col] = current.pos;
                int h = heuristic(neighbor, end);
                openSet.push({neighbor, tentativeG, h, tentativeG + h});
            }
        }
    }

    return {};
}
