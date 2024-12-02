#include <cmath>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace std;

void parse_input(vector<vector<int>> *reports, string input_filename) {
    ifstream file(input_filename);
    string line;

    if (file.is_open()) {
        while(getline(file, line)) {
            vector<int> result;
            regex rgx("\\s+");
            sregex_token_iterator iter(line.begin(), line.end(), rgx, -1);
            sregex_token_iterator end;

            while (iter != end) {
                result.push_back(stoi(*iter));
                ++iter;
            }

            reports->push_back(result);
        }

        file.close();
    }
}

bool is_safe(vector<int> report) {
    bool sign = signbit(report[1] - report[0]);

    for (int i = 1; i < report.size(); i++) {
        int diff = report[i] - report[i - 1];

        if (sign != signbit(diff) || abs(diff) < 1 || abs(diff) > 3) {
            return false;
        }
    }
    return true;
}

int part1(vector<vector<int>> reports) {
    int safe_count = 0;
    for (vector<int> report : reports) {
        if (is_safe(report)) {
            safe_count++;
        }
    }

    return safe_count;
}

int part2(vector<vector<int>> reports) {
    int safe_count = 0;

    for (vector<int> report : reports) {
        if (is_safe(report)) {
            safe_count++;
            continue;
        }

        for (int i = 0; i < reports.size(); i++) {
            vector<int> new_report(report);
            new_report.erase(new_report.begin() + i);

            if (is_safe(new_report)) {
                safe_count++;
                break;
            }
        }
    }

    return safe_count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    vector<vector<int>> reports;
    string filename = argv[1];

    parse_input(&reports, filename);

    printf("Part 1: %d\nPart 2: %d\n", part1(reports), part2(reports));

    return 0;
}
