#include <algorithm>
#include <cstring>
#include <queue>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int>> parse_input(string filename) {
    ifstream file(filename);
    string line;
    vector<vector<int>> map;

    if (file.is_open()) {
        while(getline(file, line)) {
            vector<int> row;

            for(char& c : line) {
                if (c == '\n') continue;
                row.push_back(c - '0');
            }
            map.push_back(row);
        }
    }

    return map;
}

vector<pair<int, int>> get_starting_locations(const vector<vector<int>>& map) {
    vector<pair<int, int>> starting_locations;

    for (int x = 0; x < map[0].size(); x++) {
        for (int y = 0; y < map.size(); y++) {
            if (map[y][x] == 0) {
                starting_locations.push_back({ x, y });
            }
        }
    }

    return starting_locations;
}

vector<pair<int, int>> walk(const vector<vector<int>>& map, int x, int y) {
    const vector<pair<int, int>> directions = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    queue<pair<int, int>> q;
    vector<pair<int, int>> ends;
    q.push({ x, y });

    while (!q.empty()) {
        auto current = q.front();
        int x = current.first;
        int y = current.second;
        q.pop();

        if (map[y][x] == 9) {
            ends.push_back(current);
        } else {
            for (auto dir : directions) {
                if (x + dir.first < 0 || x + dir.first >= map[0].size() ||
                    y + dir.second < 0 || y + dir.second >= map.size()) continue;

                if (map[y + dir.second][x + dir.first] == map[y][x] + 1) {
                    q.push({ x + dir.first, y + dir.second });
                }
            }
        }
    }

    return ends;
}

int part1(const vector<vector<int>>& map) {
    auto starting_locations = get_starting_locations(map);
    int sum = 0;
    
    for (auto start : starting_locations) {
        auto paths = walk(map, start.first, start.second);
        sort(paths.begin(), paths.end());
        paths.erase(unique(paths.begin(), paths.end()), paths.end());

        sum += paths.size();
    }

    return sum;
}

int part2(const vector<vector<int>>& map) {
    auto starting_locations = get_starting_locations(map);
    int sum = 0;
    
    for (auto start : starting_locations) {
        auto paths = walk(map, start.first, start.second);
        sum += paths.size();
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    vector<vector<int>> map = parse_input(filename);

    printf("Part 1: %d\nPart 2: %d\n", part1(map), part2(map));

    return 0;
}
