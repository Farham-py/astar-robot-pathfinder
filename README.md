# A* Robot Path Planning

A small C++ program that finds the shortest path for a robot moving across a 2D grid map, using the A* search algorithm. The robot starts at a point marked `S` and needs to reach a point marked `E`, avoiding obstacles (`#`) along the way. The found path is marked on the map and saved to a result file.

## Features

- Loads a grid map from a text file
- Finds the shortest path from start to end using A* (with Manhattan distance as the heuristic)
- Marks the path on the map with `*`
- Saves the result to a file, including:
  - The map with the path drawn on it
  - The path length (number of moves)
  - The full list of coordinates the robot passes through
- Also prints a summary to the console

## Project Structure

```
FinalProject-Farham/
├── Src/
│   ├── main.cpp       # Program entry point, ties everything together
│   ├── map.h / .cpp   # Map class: loading, saving, and grid checks
│   └── Astar.h / .cpp # Astar class: the pathfinding algorithm
├── Map/
│   ├── Map.txt           # Main map used by the program
├── Result/
│   ├── Result.txt    # Output for Map.txtt
├── Astar_Pathfinder.exe   # Run the custom map
└── README.md
```

## How the Map Works

The map is a plain text grid where each character means:

| Character | Meaning        |
|-----------|----------------|
| `S`       | Start position |
| `E`       | End position   |
| `#`       | Wall / obstacle (not walkable) |
| `o`       | Open, walkable space |
| `*`       | Path marked by the program in the result |

The provided map is 120 rows by 150 columns.

## How to Build

From the project's root folder, compile with:

```bash
g++ -std=c++17 -Wall -Wextra -o Astar_Pathfinder Src/main.cpp Src/map.cpp Src/Astar.cpp
```

This produces an `Astar_Pathfinder` executable.

## How to Run

```bash
./Astar_Pathfinder
```

By default, the program reads `Map/Map.txt` and writes the result to `Result/Result.txt`. Make sure you run it from the project's root folder, so the relative paths to `Map/` and `Result/` work correctly.

## Example Output

Console:
```
Path found sucessfully.
Path length (number of moves): 162
Path (row, col):
(4, 5) (4, 6) (4, 7) ...
```

The same information, along with the marked-up map, is written to `Result/Result.txt`.

