#include <cmath>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

int part1(vector<string> *muls, string input_filename) {
    ifstream file(input_filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string buffer_string = buffer.str();

    regex rgx(R"~(mul\(([0-9]{1,3}),([0-9]{1,3})\))~");

    sregex_iterator begin(buffer_string.begin(), buffer_string.end(), rgx);
    sregex_iterator end;

    int sum = 0;
    for (auto iter = begin; iter != end; ++iter) {
        smatch match = *iter;
        sum += stoi(match[1]) * stoi(match[2]);
    }

    return sum;
}

int part2(vector<string> *muls, string input_filename) {
    ifstream file(input_filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string buffer_string = buffer.str();

    regex rgx(R"~(mul\(([0-9]{1,3}),([0-9]{1,3})\)|(don\'t\(\))|(do\(\)))~");

    sregex_iterator begin(buffer_string.begin(), buffer_string.end(), rgx);
    sregex_iterator end;

    int sum = 0;
    bool multiplying = true;
    for (auto iter = begin; iter != end; ++iter) {
        smatch match = *iter;
        
        if (match[0] == "don't()") {
            multiplying = false;
        } else if (match[0] == "do()") {
            multiplying = true;
        } else if (multiplying) {
            sum += stoi(match[1].str()) * stoi(match[2].str());
        }
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    vector<string> muls;
    string filename = argv[1];

    printf("Part 1: %d\nPart 2: %d\n", part1(&muls, filename), part2(&muls, filename));

    return 0;
}
