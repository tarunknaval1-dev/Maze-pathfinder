#include <deque>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using Position = std::pair<int, int>;

bool load_maze(
    const std::string& filename,
    std::vector<std::string>& maze,
    Position& start,
    Position& exit
) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "Could not open file: " << filename << '\n';
        return false;
    }

    maze.clear();
    std::string line;
    int start_count = 0;
    int exit_count = 0;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            std::cout << "The maze contains an empty row.\n";
            return false;
        }

        int row_number = static_cast<int>(maze.size());

        for (int column = 0; column < static_cast<int>(line.size()); ++column) {
            char cell = line[column];

            if (cell == 'S') {
                start = {row_number, column};
                ++start_count;
            } else if (cell == 'E') {
                exit = {row_number, column};
                ++exit_count;
            } else if (cell != '#' && cell != '.') {
                std::cout << "Invalid maze character: " << cell << '\n';
                return false;
            }
        }

        maze.push_back(line);
    }

    if (maze.empty()) {
        std::cout << "The maze file is empty.\n";
        return false;
    }

    const std::size_t expected_width = maze[0].size();

    for (std::size_t row = 0; row < maze.size(); ++row) {
        if (maze[row].size() != expected_width) {
            std::cout << "Maze row " << row + 1
                      << " has a different width from the others.\n";
            return false;
        }
    }

    if (start_count != 1) {
        std::cout << "The maze must contain exactly one S start point.\n";
        return false;
    }

    if (exit_count != 1) {
        std::cout << "The maze must contain exactly one E exit point.\n";
        return false;
    }

    return true;
}


bool solve_maze(
    std::vector<std::string>& maze,
    Position start,
    Position exit,
    bool use_bfs,
    int& path_length,
    int& visited_count
) {
    const int rows = static_cast<int>(maze.size());
    const int columns = static_cast<int>(maze[0].size());
    const Position unvisited = {-1, -1};

    std::vector<std::vector<Position>> previous(
        rows,
        std::vector<Position>(columns, unvisited)
    );

    std::deque<Position> frontier;
    frontier.push_back(start);
    previous[start.first][start.second] = start;
    visited_count = 0;

    const int row_change[] = {-1, 1, 0, 0};
    const int column_change[] = {0, 0, -1, 1};

    while (!frontier.empty()) {
        Position current;

        if (use_bfs) {
            current = frontier.front();
            frontier.pop_front();
        } else {
            current = frontier.back();
            frontier.pop_back();
        }

        ++visited_count;

        if (current == exit) {
            break;
        }

        for (int direction = 0; direction < 4; ++direction) {
            int next_row = current.first + row_change[direction];
            int next_column = current.second + column_change[direction];

            bool inside_maze =
                next_row >= 0 && next_row < rows &&
                next_column >= 0 && next_column < columns;

            if (!inside_maze || maze[next_row][next_column] == '#') {
                continue;
            }

            if (previous[next_row][next_column] != unvisited) {
                continue;
            }

            previous[next_row][next_column] = current;
            frontier.push_back({next_row, next_column});
        }
    }

    if (previous[exit.first][exit.second] == unvisited) {
        return false;
    }

    std::vector<Position> path;
    Position current = exit;

    while (current != start) {
        path.push_back(current);
        current = previous[current.first][current.second];
    }

    path.push_back(start);

    for (std::size_t left = 0, right = path.size() - 1; left < right; ++left, --right) {
        Position temporary = path[left];
        path[left] = path[right];
        path[right] = temporary;
    }

    path_length = static_cast<int>(path.size()) - 1;

    for (Position position : path) {
        char& cell = maze[position.first][position.second];

        if (cell != 'S' && cell != 'E') {
            cell = '*';
        }
    }

    return true;
}


void display_maze(const std::vector<std::string>& maze) {
    for (const std::string& row : maze) {
        std::cout << row << '\n';
    }
}


int main() {
    std::string filename;

    std::cout << "Enter maze file path "
                 "(press Enter to use maze.txt): ";
    std::getline(std::cin, filename);

    if (filename.empty()) {
        filename = "maze.txt";
    }

    std::vector<std::string> maze;
    Position start;
    Position exit;

    if (!load_maze(filename, maze, start, exit)) {
        std::cout << "Maze was not loaded. Check the file and try again.\n";
        return 1;
    }

    std::cout << "\nChoose a solving method:\n";
    std::cout << "1. Breadth-first search (shortest route)\n";
    std::cout << "2. Depth-first search (route may not be shortest)\n";
    std::cout << "Your choice: ";

    int choice;
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cout << "Please enter 1 or 2.\n";
        return 1;
    }

    const bool use_bfs = (choice == 1);
    int path_length = 0;
    int visited_count = 0;

    if (!solve_maze(
            maze, start, exit, use_bfs, path_length, visited_count
        )) {
        std::cout << "\nNo path from S to E was found.\n";
        std::cout << "Cells explored: " << visited_count << "\n\n";
        display_maze(maze);
        return 0;
    }

    if (use_bfs) {
        std::cout << "\nBreadth-first search found a shortest route.\n";
    } else {
        std::cout << "\nDepth-first search found a route.\n";
    }

    std::cout << "Path length: " << path_length << " steps\n";
    std::cout << "Cells explored: " << visited_count << "\n\n";
    display_maze(maze);

    std::cout << "\nLegend: # = wall, . = open path, "
                 "S = start, E = exit, * = route\n";

    return 0;
}