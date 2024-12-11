#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<long long> parse_input(string filename) {
    ifstream file(filename);
    string line;
    vector<long long> stones;

    if (file.is_open()) {
        while (getline(file, line, ' ')) {
            stones.push_back(stoll(line));
        }
        file.close();
    }

    return stones;
}

void add_stone(unordered_map<long long, size_t>& cache, long long key, size_t value) {
    if (cache.count(key)) cache[key] += value;
    else cache.insert({ key, value });
}

unordered_map<long long, size_t> blink(unordered_map<long long, size_t>& stones) {
    auto new_stones = stones;

    for (auto const stone : stones) {
        string num = to_string(stone.first);

        if (stone.first == 0) add_stone(new_stones, 1, stone.second);
        else if (num.length() % 2 == 0) {
            string a = num.substr(0, num.length() / 2);
            string b = num.substr(num.length() / 2);
            add_stone(new_stones, stoll(a), stone.second);
            add_stone(new_stones, stoll(b), stone.second);
        } else add_stone(new_stones, stone.first * 2024, stone.second);

        new_stones[stone.first] -= stone.second;
    }

    return new_stones;
}

size_t part1(unordered_map<long long, size_t> stones) {
    size_t sum = 0;

    for (int i = 0; i < 25; i++) {
        stones = blink(stones);
    }

    for(auto stone : stones) {
        sum += stone.second;
    }

    return sum;
}

size_t part2(unordered_map<long long, size_t> stones) {
    size_t sum = 0;

    for (int i = 0; i < 75; i++) {
        stones = blink(stones);
    }

    for(auto stone : stones) {
        sum += stone.second;
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    vector<long long> input = parse_input(filename);
    unordered_map<long long, size_t> stones;

    for(auto i : input) {
        stones.insert({ i, 1 });
    }

    printf("Part 1: %zu\nPart 2: %zu\n", part1(stones), part2(stones));

    return 0;
}
