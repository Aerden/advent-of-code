#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

std::vector<std::pair<long long, long long>> parse(char* filename) {
    std::vector<std::pair<long long, long long>> output;
    std::ifstream inputFile(filename);
    std::string line;
  
    while (std::getline(inputFile, line, ',')) {
        output.push_back({ stol(line.substr(0, line.find('-'))), stol(line.substr(line.find('-') + 1, line.length())) });
    }

    return output;
}

long long part1(std::vector<std::pair<long long, long long>> input) {
    long long res = 0;
    
    for (std::pair<long long, long long> ranges : input) {
        for (long long n = ranges.first; n <= ranges.second; n++) {
            std::string n_str = std::to_string(n);
            std::string l = n_str.substr(0, n_str.length() / 2);
            std::string r = n_str.substr(n_str.length() / 2, n_str.length());

            if (l == r) {
                res += n;
            }
        }
    }
    
    return res;
}

long long part2(std::vector<std::pair<long long, long long>> input) {
    long long res = 0;

    for (std::pair<long long, long long> ranges : input) {
        for (long long n = ranges.first; n <= ranges.second; n++) {
            std::string n_str = std::to_string(n);
            
            for (int i = 1; i <= n_str.length() / 2; i++) {
                if (n_str.length() % i != 0) continue;
                bool invalid = true;

                for (int j = i; j < n_str.length(); j += i) {
                    if (strncmp(n_str.c_str(), n_str.c_str() + j, i)) {
                        invalid = false;
                        break;
                    }
                }
                
                if (invalid) {
                    res += n;
                    break;
                }
            }
        }
    }
    
    return res;
}

int main(int argc, char *argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %lld\n", part1(input));
    printf("Part 2: %lld\n", part2(input));
    
    return 0;
}
