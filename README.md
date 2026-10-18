# A* Robot Path Planning

A C++ implementation of the **A* (A-Star) search algorithm** for robot path planning on a 2D grid map. The program finds a route from a start position (`S`) to a destination (`E`) while avoiding obstacles (`#`).

Unlike basic A* implementations that assign the same cost to every movement, this project introduces a **wall-proximity penalty system**. The robot considers nearby obstacles when calculating movement costs, encouraging paths that maintain a safer distance from walls whenever possible.

The resulting path is reconstructed, marked on the map with `*`, and saved to an output file.

## Features

- **Grid-based map loading:** Reads a 2D environment from a plain text file.
- **A* pathfinding:** Uses the A* search algorithm to find a minimum-cost path.
- **Manhattan distance heuristic:** Estimates the remaining distance to the destination using four-directional movement.
- **Wall-proximity penalty:** Assigns additional movement costs based on nearby obstacles.
- **Four-directional movement:** Supports moving up, down, left, and right.
- **Obstacle avoidance:** Prevents the robot from moving through walls or other non-walkable cells.
- **Path reconstruction:** Records the sequence of grid coordinates from start to destination.
- **Map visualization:** Marks the calculated path using `*`.
- **Result export:** Saves the marked map, path information, and path cost or length (depending on the output implementation) to a result file.
- **Console output:** Displays a summary of the pathfinding result.

## How the Wall-Proximity Penalty Works

The algorithm assigns an additional cost to a cell depending on how close it is to an obstacle.

| Distance to nearest obstacle | Additional cost |
|---|---:|
| 1 grid cell | 10 |
| 2 grid cells | 6 |
| 3 grid cells | 3 |
| 4 grid cells | 1 |
| More than 4 grid cells | 0 |

The algorithm checks the surrounding area in expanding square-shaped regions. When it finds an obstacle at the nearest distance, it returns the corresponding penalty.

For each movement, the cost is calculated as:

```cpp
tentativeG = current.g + wallPenalty(neighbor) + 1;
```

Where:

- `current.g` is the accumulated cost of reaching the current cell.
- `wallPenalty(neighbor)` is the additional cost associated with nearby obstacles.
- `1` is the base cost of moving to an adjacent cell.

This encourages the robot to prefer routes with more clearance from walls, even when those routes require more movements.

**Important:** The penalty system encourages wall clearance, but it does not guarantee a particular physical safety distance. The penalty values are configurable and should be tuned to the map resolution and robot dimensions.

## How A* Works in This Project

The algorithm uses the following cost function:

\[
f(n)=g(n)+h(n)
\]

Where:

- \(g(n)\): Accumulated movement cost, including wall penalties.
- \(h(n)\): Manhattan distance from the current cell to the destination.
- \(f(n)\): Estimated total cost of a route through the current cell.

The Manhattan distance heuristic is:

\[
h(n)=|r_n-r_g|+|c_n-c_g|
\]

Here, \(r_n,c_n\) are the current cell coordinates and \(r_g,c_g\) are the goal coordinates.

The implementation maintains:

- **Open set:** A priority queue of nodes waiting to be explored, ordered by their estimated total cost.
- **G-score grid:** Stores the best known cost to reach each cell.
- **Visited grid:** Tracks cells that have already been processed.
- **Came-from grid:** Stores predecessor cells to reconstruct the final path.

The algorithm stops when it reaches the destination or when no reachable route remains.

## Project Structure

```text
FinalProject-Farham/
├── Src/
│   ├── main.cpp       # Program entry point
│   ├── map.h / .cpp   # Map loading and grid operations
│   └── AStar.h / .cpp # A* algorithm and wall penalties
├── Map/
│   └── Farhams_map.txt # Custom test map
├── Result/
│   └── Farham_custom_result.txt    # Custom map output
├── Astar_Farham_map   # Custom map executable (after building)
└── README.md
```

## Map Format

The map is represented as a plain-text grid. Each character represents a cell in the environment.

| Character | Meaning |
|---|---|
| `S` | Robot's starting position |
| `E` | Destination |
| `#` | Obstacle or wall |
| `o` | Open, walkable space |
| `*` | Calculated path, marked in the result map |

The original map is described as **120 rows by 150 columns**. Make sure the map file contains valid start and destination markers and that the map dimensions match the loaded grid.

## Requirements

- A C++ compiler supporting C++17
- Standard C++ library
- A terminal or IDE, such as VS Code

No external pathfinding libraries are required.

## How to Build

Open a terminal in the project's root directory and run:

```bash
g++ -std=c++17 -Wall -Wextra -o Farham_custom_map \
    Src/main.cpp Src/map.cpp Src/AStar.cpp
```

This generates the `Farham_custom_map` executable.

## How to Run

From the project root:

```bash
./Farham_custom_map
```

## Example Output

A successful run may display output similar to the following, depending on the map and output format implemented in `main.cpp`:

```text
Path found successfully.
Path length (number of moves): 162
Path (row, col):
(4, 5) (4, 6) (4, 7) ...
```

The result file contains the map with the calculated path marked using `*`, along with the path information supported by the output implementation.

## Author

**Farham**

GitHub: [@Farham-py](https://github.com/Farham-py)
