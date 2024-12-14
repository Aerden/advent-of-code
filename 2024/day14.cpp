#include <cmath>
#include <fstream>
#include <queue>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

const int WIDTH = 101;
const int HEIGHT = 103;
const int THRESHOLD = 200;

struct robot {
    pair<int, int> pos, vel;
};

vector<robot> parse_input(string filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string buffer_string = buffer.str();

    regex rgx(R"~((p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+)))~");

    sregex_iterator begin(buffer_string.begin(), buffer_string.end(), rgx);
    sregex_iterator end;

    vector<robot> robots;
    int robot_id = 0;
    for (auto iter = begin; iter != end; ++iter) {
        smatch match = *iter;
        robots.push_back({ { stoi(match[2]), stoi(match[3]) },
                           { stoi(match[4]), stoi(match[5]) } });
        robot_id++;
    }

    return robots;
}

void tick(vector<robot>& robots, int count) {
    for (auto& r : robots) {
        r.pos.first = (r.pos.first + r.vel.first * count) % WIDTH;
        r.pos.second = (r.pos.second + r.vel.second * count) % HEIGHT;

        if (r.pos.first < 0) r.pos.first += WIDTH;
        if (r.pos.second < 0) r.pos.second += HEIGHT;
    }
}

void output_map(const vector<robot>& robots) {
    vector<pair<int, int>> positions;
    for (auto& r : robots) {
        positions.push_back(r.pos);
    }
    ofstream ofs("robots.ppm", ios_base::out | ios_base::binary);
    ofs << "P1\n" << WIDTH << ' ' << HEIGHT << "\n";

    for (int y = 0u; y < HEIGHT; y++) {
        for (int x = 0u; x < WIDTH; x++) {
            pair<int, int> pos = { x, y };
            if (find(positions.begin(), positions.end(), pos) != positions.end()) {
                ofs << "0";
            } else {
                ofs << "1";
            }
        }
    }
}

int part1(vector<robot> robots) {
    int upper_left_count = 0;
    int upper_right_count = 0;
    int lower_left_count = 0;
    int lower_right_count = 0;
    tick(robots, 100);

    for (auto& r : robots) {
        if (r.pos.first < WIDTH / 2 && r.pos.second < HEIGHT / 2) upper_left_count++;
        if (r.pos.first > WIDTH / 2 && r.pos.second < HEIGHT / 2) upper_right_count++;
        if (r.pos.first < WIDTH / 2 && r.pos.second > HEIGHT / 2) lower_left_count++;
        if (r.pos.first > WIDTH / 2 && r.pos.second > HEIGHT / 2) lower_right_count++;
    }
    return upper_left_count * upper_right_count * lower_left_count * lower_right_count;
}

int part2(vector<robot>& robots) {
    const vector<pair<int, int>> directions = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
    int seconds = 0;
    bool done = false;

    while (!done) {
        tick(robots, 1);
        seconds++;
        vector<vector<bool>> map(HEIGHT, vector<bool>(WIDTH, false));
        vector<vector<bool>> visited(HEIGHT, vector<bool>(WIDTH, false));
        
        for (auto& r : robots) {
            map[r.pos.second][r.pos.first] = true;
        }

        for (auto& r : robots) {
            if (visited[r.pos.second][r.pos.first]) continue;
            int num_adjacent = 0;
            queue<pair<int, int>> q;
            q.push(r.pos);
            visited[r.pos.second][r.pos.first] = true;

            while (!q.empty()) {
                auto current = q.front();
                q.pop();
                num_adjacent++;
                visited[current.second][current.first] = true;
                
                for (auto dir : directions) {
                    int x = current.first + dir.first;
                    int y = current.second + dir.second;

                    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) continue;
                    if (visited[y][x]) continue;
                    if (!map[y][x]) continue;

                    q.push({ x, y });
                }
            }

            if (num_adjacent > THRESHOLD) {
                done = true;
                break;
            }
        }
    }

    output_map(robots);
    return seconds;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    auto robots = parse_input(filename);

    printf("Part 1: %d\nPart 2: %d\n", part1(robots), part2(robots));

    return 0;
}
