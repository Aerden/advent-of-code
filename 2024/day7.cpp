#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

vector<pair<long long, vector<int>>> parse_input(string filename) {
    ifstream file(filename);
    string line;
    vector<pair<long long, vector<int>>> operations;
    bool update = false;
    string delimiter = ": ";

    if (file.is_open()) {
        while (getline(file, line)) {
            long long target;
            vector<int> numbers;

            target = stoll(line.substr(0, line.find(':')));
            line.erase(0, line.find(':') + delimiter.length());

            istringstream ss(line);
            string num;

            while (getline(ss, num, ' ')) {
                numbers.push_back(stoi(num));
            }
            operations.push_back({ target, numbers });
        }
        file.close();
    }

    return operations;
}

bool is_valid(long long target, vector<int>& numbers, long long current, int index) {
    if (current > target) return false;
    if (index >= numbers.size()) return current == target;

    current += numbers[index];
    if (is_valid(target, numbers, current, index + 1)) return true;
    current -= numbers[index];

    current *= numbers[index];
    return is_valid(target, numbers, current, index + 1);
}

bool is_valid_part2(long long target, vector<int>& numbers, long long current, int index) {
    if (current > target) return false;
    if (index >= numbers.size()) return current == target;

    current += numbers[index];
    if (is_valid_part2(target, numbers, current, index + 1)) return true;
    current -= numbers[index];

    current *= numbers[index];
    if (is_valid_part2(target, numbers, current, index + 1)) return true;
    current /= numbers[index];

    string a = to_string(current);
    string b = to_string(numbers[index]);
    a += b;
    current = stoll(a);
    return is_valid_part2(target, numbers, current, index + 1);
}

long long part1(vector<pair<long long, vector<int>>>& operations) {
    long long sum = 0;
    
    for (auto operation : operations) {
        if (is_valid(operation.first, operation.second, 0, 0)) {
            sum += operation.first;
        }
    }

    return sum;
}

long long part2(vector<pair<long long, vector<int>>>& operations) {
    long long sum = 0;
    
    for (auto operation : operations) {
        if (is_valid_part2(operation.first, operation.second, 0, 0)) {
            sum += operation.first;
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    vector<vector<int>> map;
    int guard_pos_x = 0;
    int guard_pos_y = 0;

    vector<pair<long long, vector<int>>> input = parse_input(filename);
    printf("Part 1: %lld\nPart 2: %lld\n", part1(input), part2(input));

    return 0;
}
