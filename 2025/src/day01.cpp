#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

std::vector<int> parse(char* filename) {
    std::vector<int> output;
    std::ifstream inputFile(filename);
    std::string line;
  
    while (std::getline(inputFile, line)) {
        std::replace(line.begin(), line.end(), 'L', '-');
        std::replace(line.begin(), line.end(), 'R', '+');
    
        output.push_back(std::stoi(line));
    }
    
    return output;
}

int part1(std::vector<int> input) {
    int res = 0;
    int dial = 50;
  
    for (int x : input) {
        dial = (dial + x) % 100;
        if (dial == 0) res++;
    }

    return res;
}

int part2(std::vector<int> input) {
    int res = 0;
    int dial = 50;
  
    for (int x : input) {
        dial += x;
        if (x < 0) {
            if (dial >= 0) {
                if (dial == 0) res++;
                continue;
            }
          
            if (dial - x != 0) res++;
    
            dial = abs(dial);
            res += dial / 100;
            dial = (100 - dial % 100) % 100;
        } else {
            res += dial / 100;
            dial %= 100;
        }
    }
    return res;
}

int main(int argc, char *argv[]) {
    std::vector<int> input = parse(argv[1]);
    printf("Part 1: %d\n", part1(input));
    printf("Part 2: %d\n", part2(input));

    return 0;
}
