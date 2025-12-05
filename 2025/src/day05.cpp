#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::pair<std::vector<std::pair<long long, long long>>, std::vector<long long>> parse(char* filename) {
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> ids;
    std::ifstream inputFile(filename);
    std::string line;
    bool parseId = false;

    while (std::getline(inputFile, line)) {
        if (!line.length()) {
            parseId = true;
            continue;
        }

        if (!parseId) {
            long long l = stoll(line.substr(0, line.find('-')));
            long long r = stoll(line.substr(line.find('-') + 1, line.length()));
            ranges.push_back({ l, r });
        } else {
            ids.push_back(stoll(line));
        }
    }
    
    return { ranges, ids };
}

int part1(std::pair<std::vector<std::pair<long long, long long>>, std::vector<long long>> input) {
    int res = 0;

    for (auto& id : input.second) {
        for (auto& range : input.first) {
            if (id >= range.first && id <= range.second) {
                res++;
                break;
            }
        }
    }

    return res;
}

long long part2(std::pair<std::vector<std::pair<long long, long long>>, std::vector<long long>> input) {
    long long res = 0;
    std::vector<std::pair<long long, long long>> ranges(input.first.begin(), input.first.end());
    std::sort(ranges.begin(), ranges.end());

    for (int i = 0; i < ranges.size(); i++) {
        auto& range = ranges[i];

        if (i > 0) {
            range.first = std::max(range.first, ranges[i - 1].second + 1);
            range.second = std::max(range.second, ranges[i - 1].second);
        }
        res += range.second - range.first + 1;
    }

    return res;
}

int main(int argc, char* argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %d\n", part1(input));
    printf("Part 2: %lld\n", part2(input));

    return 0;
}
