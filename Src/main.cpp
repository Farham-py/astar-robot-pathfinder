#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "AStar.h"
#include "Map.h"
using namespace std;

bool appendPathInfo(const string& filename, const vector<Point>& path) ; 
int main() {

    const string inputFile = "Map/Map.txt";
    const string outputFile = "Result/Result.txt";

    Map map;
    if (!map.load(inputFile)) {
        return 1; 
    }
    Astar astar(map);
    vector<Point> path= astar.findPath();
    if (path.empty()) {
        cout<<"No path found from S to E." <<endl;
        return 0;
    }
    cout<<"Path found sucessfully."<<endl;
    cout<<"Path length (number of moves): " << path.size() - 1 << endl;
    cout<<"Path (row, col):" << endl;
    for (const Point &p:path) {
        cout<< "(" << p.row << ", " << p.col << ") ";
    }
    cout<<endl;

    map.markPath(path);
    if (!map.save(outputFile)) {
        cout<<"Error: couldn't save the result ."<<outputFile << endl;
        return 1;
    }
    if (!appendPathInfo(outputFile, path)) {
        cout << "Error: couldn't append path info to  result file ."<< endl;
        return 1;
    }
    cout<<"Result saved to "<<outputFile<< endl;
    return 0;
}

bool appendPathInfo(const string& filename, const vector<Point>& path) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        return false;
    }
    file<<endl ;
    file<<"Path length (number of moves): " << path.size() - 1 << endl;
    file<<"Path (row, col):"<<endl;
    for (const Point& p : path) {
        file<< "(" << p.row << ", " << p.col << ") ";
    }
    file<<endl ;
    return true;
}