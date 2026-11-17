#include <iostream>
#include <string>
#include <vector>

int main() {
    const std::vector<std::string> maze = {
        "#########",
        "#S...#..#",
        "#.#.#.#.#",
        "#.#...#E#",
        "#########"
    };

    std::cout << "Maze Pathfinder\n\n";

    for (const std::string& row : maze) {
        std::cout << row << '\n';
    }

    std::cout << "\nLegend: # = wall, . = open path, S = start, E = exit\n";

    return 0;
}