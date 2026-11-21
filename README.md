# C++ Maze Pathfinder

A command-line program that loads a maze from a text file and searches for a route from the start to the exit.

## Features

- Load a maze from a text file
- Check that the maze is rectangular and contains valid symbols
- Require exactly one start (`S`) and one exit (`E`)
- Solve with breadth-first search (BFS) or depth-first search (DFS)
- Display the route and report its length and explored-cell count

BFS finds a shortest route. DFS finds a route if one is available, but it may not be the shortest.

## Maze symbols

- `#` — wall
- `.` — open space
- `S` — start
- `E` — exit
- `*` — route displayed by the program

## Build and run

Requires a C++17 compiler.

With `g++`, build the program:

```bash
g++ -std=c++17 main.cpp -o maze
```

Run it from the project folder so it can find `maze.txt`:

```bash
./maze
```

On Windows, the executable may be named `maze.exe`; run it with:

```powershell
.\maze.exe
```

Enter a maze filename when prompted, or press Enter to use `maze.txt`. Then choose `1` for BFS or `2` for DFS.

## Sample mazes

- `maze.txt` — a maze with a route
- `maze_no_path.txt` — a maze with no route

## Project status

This project was built in stages as a C++ learning project. It has not been compiled or tested on a computer without a C++ compiler.

## Author

Tarun Kumar naval