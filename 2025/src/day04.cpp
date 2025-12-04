#include <iostream>
#include <fstream>
#include <vector>

static constexpr int offsets[8][2] = {
    { -1, -1 }, { 0, -1 }, { 1, -1 },
    { -1,  0 },            { 1,  0 },
    { -1,  1 }, { 0,  1 }, { 1,  1 }
};

std::vector<std::vector<char>> parse(char* filename) {
    std::vector<std::vector<char>> output;
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<char> row;
        for (char& cell : line) {
            row.push_back(cell);
        }
        output.push_back(row);
    }

    return output;
}

int part1(std::vector<std::vector<char>> input) {
    int res = 0;

    for (int y = 0; y < input.size(); y++) {
        for (int x = 0; x < input[0].size(); x++) {
            if (input[y][x] == '.') continue;
            int count = 0;

            for (auto& pos : offsets) {
                int nx = x + pos[0];
                int ny = y + pos[1];
                if (nx < 0 || nx >= input[0].size() ||
                    ny < 0 || ny >= input.size())
                    continue;
                if (input[ny][nx] == '@') count++;
            }

            if (count < 4) res++;
        }
    }
    
    return res;
}

int part2(std::vector<std::vector<char>> input) {
    int res = 0;
    bool rollsRemoved = true;

    while (rollsRemoved) {
        rollsRemoved = false;
        for (int y = 0; y < input.size(); y++) {
            for (int x = 0; x < input[0].size(); x++) {
                if (input[y][x] == '.') continue;
                int count = 0;

                for (auto& pos : offsets) {
                    int nx = x + pos[0];
                    int ny = y + pos[1];
                    if (nx < 0 || nx >= input[0].size() ||
                        ny < 0 || ny >= input.size())
                        continue;
                    if (input[ny][nx] == '@') count++;
                }

                if (count < 4) {
                    res++;
                    input[y][x] = '.';
                    rollsRemoved = true;
                }
            }
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %d\n", part1(input));
    printf("Part 2: %d\n", part2(input));
    
    return 0;
}
