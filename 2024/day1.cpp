#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

void parse_input(vector<int> *a, vector<int> *b, string input_filename) {
    ifstream file(input_filename);
    string line;

    if (file.is_open()) {
        while(getline(file, line)) {
            vector<string> result;
            regex rgx("\\s+");
            sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);
            sregex_token_iterator end;

            while (iter != end) {
                result.push_back(*iter);
                ++iter;
            }

            a->push_back(stoi(result[0]));
            b->push_back(stoi(result[1]));
        }

        file.close();
    }
}

int part1(vector<int> a, vector<int> b) {
    sort(begin(a), end(a));
    sort(begin(b), end(b));

    int sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += abs(a[i] - b[i]);
    }

    return sum;
}

int part2(vector<int> a, vector<int> b) {
    int sum = 0;
    for (int i : a) {
        int occurences = 0;
        for (int j : b) {
            if (i == j) {
                occurences++;
            }
        }

        sum += (i * occurences);
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    vector<int> a, b;
    string filename = argv[1];

    parse_input(&a, &b, filename);
    int first = part1(a, b);
    int second = part2(a, b);

    printf("Part 1: %d\nPart 2: %d\n", first, second);
    return 0;
}
