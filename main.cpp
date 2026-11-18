#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool load_maze(
    const std::string& filename,
    std::vector<std::string>& maze
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
        // Remove a carriage return if the file uses Windows line endings.
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            std::cout << "The maze contains an empty row.\n";
            return false;
        }

        for (char cell : line) {
            if (cell == 'S') {
                ++start_count;
            } else if (cell == 'E') {
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


void display_maze(const std::vector<std::string>& maze) {
    std::cout << "\nMaze:\n";

    for (const std::string& row : maze) {
        std::cout << row << '\n';
    }

    std::cout << "\nLegend: # = wall, . = open path, "
                 "S = start, E = exit\n";
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

    if (!load_maze(filename, maze)) {
        std::cout << "Maze was not loaded. Check the file and try again.\n";
        return 1;
    }

    display_maze(maze);
    return 0;
}