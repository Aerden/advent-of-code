#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <limits>

std::vector<std::string> parse(char* filename) {
    std::vector<std::string> output;
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line)) {
        output.push_back(line);
    }

    return output;
}

int part1(std::vector<std::string> input) {
    int res = 0;
    
    for (int y = 1; y < input.size(); y++) {
        for (int x = 0; x < input[0].size(); x++) {
            if ((input[y - 1][x] == 'S' || input[y - 1][x] == '|')) {
                if (input[y][x] == '.') {
                    input[y][x] = '|';
                } else if (input[y][x] == '^') {
                    input[y][x - 1] = '|';
                    input[y][x + 1] = '|';
                    res++;
                }
            }
        }
    }

    return res;
}

unsigned long long part2(std::vector<std::string> input) {
    std::vector<long long> beams(input[0].size(), 0);
    beams[input[0].find('S')] = 1;

    for (int y = 2; y < input.size(); y += 2) {
        std::string row = input[y];
        for (int x = row.find('^'); x < std::string::npos; x = row.find('^', x + 1)) {
            if (beams[x] > 0) {
                beams[x - 1] += beams[x];
                beams[x + 1] += beams[x];
                beams[x] = 0;
            }
        }
    }

    return std::accumulate(beams.begin(), beams.end(), 0ull);
}

int main(int argc, char* argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %d\n", part1(input));
    printf("Part 2: %llu\n", part2(input));
    
    return 0;
}
