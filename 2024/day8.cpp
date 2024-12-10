#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

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

unordered_map<char, vector<pair<int, int>>> get_antennas(vector<vector<char>>& map) {
    unordered_map<char, vector<pair<int, int>>> antennas;

    for (int x = 0; x < map[0].size(); x++) {
        for (int y = 0; y < map.size(); y++) {
            if (map[y][x] != '.') {
                antennas[map[y][x]].push_back({ x, y });
            }
        }
    }

    return antennas;
}

int part1(vector<vector<char>>& map) {
    int count = 0;
    auto antennas = get_antennas(map);
    bool antinodes[map.size()][map[0].size()];
    memset(antinodes, false, sizeof(antinodes));

    for (auto& a : antennas) {
        for (int i = 0; i < a.second.size(); i++) {
            for (int j = i + 1; j < a.second.size(); j++) {
                auto a1 = a.second[i];
                auto a2 = a.second[j];
                int dx = a1.first - a2.first;
                int dy = a1.second - a2.second;

                int x1 = a1.first + dx, y1 = a1.second + dy;
                int x2 = a2.first - dx, y2 = a2.second - dy;

                if (x1 >= 0 && x1 < map[0].size() && y1 >= 0 && y1 < map.size() && !antinodes[y1][x1]) {
                    antinodes[y1][x1] = true;
                    count++;
                }
                if (x2 >= 0 && x2 < map[0].size() && y2 >= 0 && y2 < map.size() && !antinodes[y2][x2]) {
                    antinodes[y2][x2] = true;
                    count++;
                }
            }
        }
    }

    return count;
}

int part2(vector<vector<char>>& map) {
    int count = 0;
    auto antennas = get_antennas(map);
    bool antinodes[map.size()][map[0].size()];
    memset(antinodes, false, sizeof(antinodes));

    for (auto& a : antennas) {
        for (int i = 0; i < a.second.size(); i++) {
            for (int j = i + 1; j < a.second.size(); j++) {
                auto a1 = a.second[i];
                auto a2 = a.second[j];
                int dx = a1.first - a2.first;
                int dy = a1.second - a2.second;

                int x = a1.first - dx, y = a1.second - dy;

                while(x >= 0 && x < map[0].size() && y >= 0 && y < map.size()) {
                    if (!antinodes[y][x]) {
                        antinodes[y][x] = true;
                        count++;
                    }

                    x -= dx;
                    y -= dy;
                }

                x += dx; y += dy;

                while(x >= 0 && x < map[0].size() && y >= 0 && y < map.size()) {
                    if (!antinodes[y][x]) {
                        antinodes[y][x] = true;
                        count++;
                    }

                    x += dx;
                    y += dy;
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
    vector<vector<char>> map = parse_input(filename);

    printf("Part 1: %d\nPart 2: %d\n", part1(map), part2(map));

    return 0;
}
