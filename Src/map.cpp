#include "map.h" 
#include <iostream>
#include <fstream> 
using namespace std ; 

bool Map::load(const string &filename){
    ifstream file(filename);
    if(file.is_open() == false){
        cout << "Error: could not open " << filename << endl;
        return false;
    }
    string line ; 
    bool startFound = false ; 
    bool endFound = false ;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back(); 
        }
        if (line.empty()) {
            continue;
        }
        if (cols == 0) {
            cols = static_cast<int>(line.size());
        } else if (static_cast<int>(line.size()) != cols) {
            cout << "Error: invalid or inconsistent map dimensions" << endl;
            return false;
        }
        for (int c = 0; c < static_cast<int>(line.size()); c++) {
            if (line[c] == 'S') {
                start = {rows, c};
                startFound = true;
            } else if (line[c] == 'E') {
                end = {rows, c};
                endFound = true;
            }
        }
        grid.push_back(line);
        rows++;
    }
    if (rows == 0) {
        cout << "Error: the map is empty" << endl;
        return false;
    }
    if (!startFound) {
        cout << "Error: start point (S) was not found" << endl;
        return false;
    }
    if (!endFound) {
        cout << "Error: end point (E) was not found" << endl;
        return false;
    }


    return true;

}
bool Map::save(const string &filename)const{
    ofstream file(filename);
    if(file.is_open() == false){
        cout << "Error: could not open " << filename << endl;
        return false ;
    }
    for(const string &row :grid){
        file<<row<<endl ; 
    }
    return true ; 

}
void Map::markPath(const vector<Point>& path) {
    for (const Point& p : path) {
        char& cell = grid[p.row][p.col];
        if (cell != 'S' && cell != 'E') {
            cell = '*';
        }
    }
}
bool Map::isInside(const Point& p) const {
    return p.row >= 0 && p.row < rows && p.col >= 0 && p.col < cols;
}

bool Map::isWalkable(const Point& p) const {
    return isInside(p) && grid[p.row][p.col] != '#';
}
