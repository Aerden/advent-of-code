// I don't like how I did this puzzle tbh
#include <cmath>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

const string XMAS = "XMAS";

vector<vector<char>> parse_input(string input_filename) {
    vector<vector<char>> rows;
    ifstream file(input_filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            istringstream ss(line);
            vector<char> row;

            char letter { 0 };
            while (ss >> letter) {
                row.push_back(letter);
            }

            rows.push_back(row);
        }
        file.close();
    }

    return rows;
}

bool is_xmas(vector<vector<char>> grid, int start_x, int start_y, int dir_x, int dir_y) {
    int width = grid[0].size();
    int height = grid.size();

    int current_x = start_x;
    int current_y = start_y;

    for (int i = 1; i < 4; i++) {
        current_x += dir_x;
        current_y += dir_y;

        if (current_x < 0 || current_x >= width ||
            current_y < 0 || current_y >= height) {
            return false;
        }

        if (grid[current_y][current_x] != XMAS[i]) {
            return false;
        }
    }

    return true;
}

int part1(vector<vector<char>> grid) {
    int count = 0;

    for (int x = 0; x < grid[0].size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            if (grid[y][x] == 'X') {
                for (int dir_x = -1; dir_x <= 1; dir_x++) {
                    for (int dir_y = -1; dir_y <= 1; dir_y++) {
                        if (dir_x == 0 && dir_y == 0) continue;

                        if (is_xmas(grid, x, y, dir_x, dir_y)) {
                            count++;
                        }
                    }
                }
            }
        }
    }

    return count;
}

int part2(vector<vector<char>> grid) {
    int count = 0;

    for (int x = 0; x < grid[0].size(); x++) {
        for (int y = 0; y < grid.size(); y++) {
            if (x == 0 || y == 0 || x == grid[0].size() - 1 || y == grid.size() - 1) continue;
            if (grid[y][x] == 'A') {
                if (((grid[y - 1][x - 1] == 'M' && grid[y + 1][x + 1] == 'S') || (grid[y - 1][x - 1] == 'S' && grid[y + 1][x + 1] == 'M')) &&
                    ((grid[y + 1][x - 1] == 'M' && grid[y - 1][x + 1] == 'S') || (grid[y + 1][x - 1] == 'S' && grid[y - 1][x + 1] == 'M'))) {
                    count++;
                }
            }
        }
    }

    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    vector<vector<char>> grid = parse_input(filename);

    printf("Part 1: %d\nPart 2: %d\n", part1(grid), part2(grid));

    return 0;
}
