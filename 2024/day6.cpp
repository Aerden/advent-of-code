#include <fstream>
#include <stack>
#include <vector>

using namespace std;

static const vector<pair<int, int>> DIRECTIONS = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };
static const vector<int> MASKS = { 0b0001, 0b0010, 0b0100, 0b1000 };

void parse_input(string filename, vector<vector<int>>& map, int& guard_pos_x, int& guard_pos_y) {
    ifstream file(filename);
    string line;
    int y = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            vector<int> row;
            int x = 0;

            for(char& c : line) {
                if (c == '#') {
                    row.push_back(1);
                } else if (c == '^') {
                    guard_pos_x = x;
                    guard_pos_y = y;
                    row.push_back(0);
                } else {
                    row.push_back(0);
                }
                x++;
            }

            map.push_back(row);
            y++;
        }
        file.close();
    }
}

pair<int, int> walk(const vector<vector<int>>& map, const pair<int, int>& pos, int& dir) {
    int next_x = pos.first + DIRECTIONS[dir].first;
    int next_y = pos.second + DIRECTIONS[dir].second;

    if (next_x < 0 || next_x >= map[0].size() ||
        next_y < 0 || next_y >= map.size()) {
        return { -1, -1 }; // Invalid position
    }

    while (map[next_y][next_x]) {
        dir = (dir + 1) % 4;
        next_x = pos.first + DIRECTIONS[dir].first;
        next_y = pos.second + DIRECTIONS[dir].second;

        if (next_x < 0 || next_x >= map[0].size() ||
            next_y < 0 || next_y >= map.size()) {
            return { -1, -1 }; // Invalid position
        }
    }

    return { next_x, next_y };
}

int part1(const vector<vector<int>>& map, pair<int, int> pos) {
    int count = 0;
    int dir = 0;
    int x = pos.first;
    int y = pos.second;
    vector<vector<int>> visited(map.size(), vector<int>(map[0].size(), 0));

    while (true) {
        auto next_pos = walk(map, { x, y }, dir);
        if (next_pos.first == -1) break;

        if (visited[next_pos.second][next_pos.first] == 0) {
            count++;
            visited[next_pos.second][next_pos.first] = 1;
        }

        x = next_pos.first;
        y = next_pos.second;
    }

    return count;
}

bool is_loop(const vector<vector<int>>& map, pair<int, int>& pos) {
    int x = pos.first;
    int y = pos.second;
    int dir = 0;
    vector<vector<int>> visited(map.size(), vector<int>(map[0].size(), 0));

    while (true) {
        auto next_pos = walk(map, { x, y }, dir);

        if (next_pos.first == -1) return false;
        if (visited[next_pos.second][next_pos.first] & MASKS[dir]) return true;

        visited[next_pos.second][next_pos.first] |= MASKS[dir];
        x = next_pos.first;
        y = next_pos.second;
    }

    return true;
}

int part2(vector<vector<int>> map, pair<int, int> pos) {
    int count = 0;
    int dir = 0;
    int x = pos.first;
    int y = pos.second;
    vector<vector<int>> visited(map.size(), vector<int>(map[0].size(), 0));

    while(true) {
        auto obstacle_pos = walk(map, { x, y }, dir);
        if (obstacle_pos.first == -1) break;

        map[obstacle_pos.second][obstacle_pos.first] = 1;
        if (is_loop(map, pos) && visited[obstacle_pos.second][obstacle_pos.first] == 0) {
            count++;
            visited[obstacle_pos.second][obstacle_pos.first] = 1;
        }
        map[obstacle_pos.second][obstacle_pos.first] = 0;

        x = obstacle_pos.first;
        y = obstacle_pos.second;
    }

    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    vector<vector<int>> map;
    int guard_pos_x = 0;
    int guard_pos_y = 0;

    parse_input(filename, map, guard_pos_x, guard_pos_y);
    printf("Part 1: %d\nPart 2: %d\n", part1(map, { guard_pos_x, guard_pos_y }), part2(map, { guard_pos_x, guard_pos_y } ));

    return 0;
}
