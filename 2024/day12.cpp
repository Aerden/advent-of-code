#include <cstring>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const vector<pair<int, int>> DIRECTIONS = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

vector<vector<char>> parse_input(string filename) {
    ifstream file(filename);
    string line;
    vector<vector<char>> map;

    if (file.is_open()) {
        while(getline(file, line)) {
            vector<char> row;

            for(char& c : line) {
                row.push_back(c);
            }
            map.push_back(row);
        }
    }

    return map;
}

struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

bool in_grid(const vector<vector<char>>& map, int x, int y) {
    return x >= 0 && x < map[0].size() && y >= 0 && y < map.size();
}

bool is_diff_cell(const vector<vector<char>>& map, int x, int y, char c) {
    return !in_grid(map, x, y) || map[y][x] != c;
}

bool is_same_cell(const vector<vector<char>>& map, int x, int y, char c) {
    return in_grid(map, x, y) && map[y][x] == c;
}

vector<pair<int, int>> get_region(const vector<vector<char>>& map, int x, int y, unordered_set<pair<int, int>, pair_hash>& visited) {
    queue<pair<int, int>> q;
    vector<pair<int, int>> region;
    char c = map[y][x];

    visited.insert({ x, y });
    q.push({ x, y });
    region.push_back({ x, y });

    while (!q.empty()) {
        auto current = q.front();
        int new_x = current.first;
        int new_y = current.second;
        q.pop();

        for (auto& dir : DIRECTIONS) {
            pair<int, int> pos = { new_x + dir.first, new_y + dir.second };
            if (!in_grid(map, pos.first, pos.second)) continue;

            if (is_diff_cell(map, pos.first, pos.second, c)) continue;

            if (find(visited.begin(), visited.end(), pos) != visited.end()) continue;

            q.push(pos);
            visited.insert(pos);
            region.push_back(pos);
        }
    }

    return region;
}

int get_perimeter(const vector<vector<char>>& map, const vector<pair<int, int>>& region) {
    int perimeter = 0;

    for (auto& cell : region) {
        for (auto& dir : DIRECTIONS) {
            pair<int, int> new_pos = { cell.first + dir.first, cell.second + dir.second };

            if (find(region.begin(), region.end(), new_pos) == region.end()) {
                perimeter++;
            }
        }
    }

    return perimeter;
}

int get_sides(const vector<vector<char>>& map, const vector<pair<int, int>>& region) {
    int count = 0;

    for (auto& cell : region) {
        const char& c = map[cell.second][cell.first];
        pair<int, int> right_neighbor = { cell.first + DIRECTIONS[0].first, cell.second + DIRECTIONS[0].second };
        pair<int, int> left_neighbor = { cell.first + DIRECTIONS[2].first, cell.second + DIRECTIONS[2].second };
        pair<int, int> bottom_neighbor = { cell.first + DIRECTIONS[1].first, cell.second + DIRECTIONS[1].second };
        pair<int, int> top_neighbor = { cell.first + DIRECTIONS[3].first, cell.second + DIRECTIONS[3].second };

        // Outer corners
        // Top left corner
        if (is_diff_cell(map, top_neighbor.first, top_neighbor.second, c) &&
            is_diff_cell(map, left_neighbor.first, left_neighbor.second, c) &&
            is_diff_cell(map, left_neighbor.first, top_neighbor.second, c)) {
            count++;
        }
        // Top right corner
        if (is_diff_cell(map, top_neighbor.first, top_neighbor.second, c) &&
            is_diff_cell(map, right_neighbor.first, right_neighbor.second, c) &&
            is_diff_cell(map, right_neighbor.first, top_neighbor.second, c)) {
            count++;
        }
        // Bottom left corner
        if (is_diff_cell(map, bottom_neighbor.first, bottom_neighbor.second, c) &&
            is_diff_cell(map, left_neighbor.first, left_neighbor.second, c) &&
            is_diff_cell(map, left_neighbor.first, bottom_neighbor.second, c)) {
            count++;
        }
        // Bottom right corner
        if (is_diff_cell(map, bottom_neighbor.first, bottom_neighbor.second, c) &&
            is_diff_cell(map, right_neighbor.first, right_neighbor.second, c) &&
            is_diff_cell(map, right_neighbor.first, bottom_neighbor.second, c)) {
            count++;
        }
        // Inner corners
        // Top left corner
        if (is_diff_cell(map, top_neighbor.first, top_neighbor.second, c) && is_same_cell(map, left_neighbor.first, top_neighbor.second, c)) {
            count++;
        }
        // Top right corner
        if (is_diff_cell(map, top_neighbor.first, top_neighbor.second, c) && is_same_cell(map, right_neighbor.first, top_neighbor.second, c)) {
            count++;
        }
        // Bottom left corner
        if (is_diff_cell(map, bottom_neighbor.first, bottom_neighbor.second, c) && is_same_cell(map, left_neighbor.first, bottom_neighbor.second, c)) {
            count++;
        }
        // Bottom right corner
        if (is_diff_cell(map, bottom_neighbor.first, bottom_neighbor.second, c) && is_same_cell(map, right_neighbor.first, bottom_neighbor.second, c)) {
            count++;
        }
    }

    return count;
}

int part1(const vector<vector<char>>& map) {
    unordered_set<pair<int, int>, pair_hash> visited;
    int total = 0;

    for (int x = 0; x < map[0].size(); x++) {
        for (int y = 0; y < map.size(); y++) {
            pair<int, int> pos = { x, y };
            if (find(visited.begin(), visited.end(), pos) != visited.end()) continue;

            auto region = get_region(map, x, y, visited);
            int perimeter = get_perimeter(map, region);
            total += perimeter * region.size();
        }
    }

    return total;
}

int part2(const vector<vector<char>>& map) {
    unordered_set<pair<int, int>, pair_hash> visited;
    int total = 0;

    for (int x = 0; x < map[0].size(); x++) {
        for (int y = 0; y < map.size(); y++) {
            pair<int, int> pos = { x, y };
            if (find(visited.begin(), visited.end(), pos) != visited.end()) continue;

            auto region = get_region(map, x, y, visited);
            int sides = get_sides(map, region);
            total += sides * region.size();
        }
    }

    return total;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    vector<vector<char>> map = parse_input(filename);

    printf("Part 1: %d\nPart 2: %d\n", part1(map), part2(map));

    return 0;
}
