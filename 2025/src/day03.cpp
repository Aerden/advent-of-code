#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> parse(char* filename) {
    std::vector<std::vector<int>> output;
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line)) {
        std::vector<int> bank;
        for (char& digit : line) {
            bank.push_back(digit - '0');
        }
        output.push_back(bank);
    }

    return output;
}

int part1(std::vector<std::vector<int>> input) {
    int res = 0;
    for (auto bank : input) {
        int l = 0, r = 0;

        for (int i = 0; i < bank.size(); i++) {
            if (bank[i] > l && i != bank.size() - 1) {
                l = bank[i];
                r = bank[i + 1];
            }
            else if (bank[i] > r) {
                r = bank[i];
            }
        }

        res += l * 10 + r;
    }
    return res;
}

long long part2(std::vector<std::vector<int>> input) {
    long long res = 0;
    for (auto bank : input) {
        std::vector<int> digits(12, 0);
        int prev = 0;

        for (int i = 0; i < digits.size(); i++) {
            for (int j = prev; j < bank.size() - (digits.size() - i) + 1; j++) {
                if (digits[i] < bank[j]) {
                    digits[i] = bank[j];
                    prev = j + 1;
                    
                    if (digits[i] == 9)
                        break;
                }
            }
        }

        long long pow = 1;
        for (int i = digits.size() - 1; i >= 0; i--) {
            res += pow * digits[i];
            pow *= 10;
        }
    }
    
    return res;
}

int main(int argc, char *argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %d\n", part1(input));
    printf("Part 2: %lld\n", part2(input));
    
    return 0;
}
