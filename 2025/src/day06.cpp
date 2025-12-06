#include <iostream>
#include <fstream>
#include <vector>

std::vector<std::string> parse(char* filename) {
    std::vector<std::string> output;
    std::fstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line)) {
        output.push_back(line);
    }
    
    return output;
}

long long part1(std::vector<std::string> input) {
    long long res = 0;
    std::vector<bool> multiply;
    int pos = 0;
    std::string& ops = input[input.size() - 1];

    while (true) {
        pos = ops.find_first_not_of(" ", pos);
        if (pos == ops.npos) break;
        multiply.push_back(ops[pos] == '*');
        pos++;
    }

    std::vector<long long> numbers(multiply.size());
    for(int i = 0; i < input.size() - 1; i++) {
        std::string n = input[i];
        size_t pos;

        for (int j = 0; j < multiply.size(); j++) {
            if (i == 0)
                numbers[j] = multiply[j] ? 1 : 0;

            long long num = std::stoll(n, &pos);
            n = n.substr(pos);
            
            if (multiply[j])
                numbers[j] *= num;
            else
                numbers[j] += num;

            if (i == input.size() - 2)
                res += numbers[j];
        }
    }

    return res;
}

long long part2(std::vector<std::string> input) {
    long long res = 0;
    std::vector<bool> multiply;
    int pos = 0;
    std::string& ops = input[input.size() - 1];

    while (true) {
        pos = ops.find_first_not_of(" ", pos);
        if (pos == ops.npos) break;
        multiply.push_back(ops[pos] == '*');
        pos++;
    }

    int x = 0;
    for (int i = 0; i < multiply.size(); i++) {
        long long current = multiply[i] ? 1 : 0;
        while (true) {
            int y = 0;
            bool blank = true;
            long long num = 0;

            while (true) {
                if (isdigit(input[y][x])) {
                    blank = false;
                    num *= 10;
                    num += input[y][x] - '0';
                }
                
                y++;
                if (y >= input.size() - 1) break;
            }
            x++;
            if (blank) break;
            if (multiply[i]) current *= num;
            else current += num;
        }
        res += current;
    }

    return res;
}

int main(int argc, char* argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %lld\n", part1(input));
    printf("Part 2: %lld\n", part2(input));
    
    return 0;
}
