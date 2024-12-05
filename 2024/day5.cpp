#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <set>

using namespace std;

void parse_input(string filename, set<pair<int, int>> *order_rules, vector<vector<int>> *updates) {
    ifstream file(filename);
    string line;
    bool update = false;

    if (file.is_open()) {
        while (getline(file, line)) {
            if (line.empty()) {
                update = true;
                continue;
            }

            if (!update) {
                int delim_idx = line.find('|');
                order_rules->insert({ stoi(line.substr(0, delim_idx)), stoi(line.substr(delim_idx + 1)) });
            } else {
                istringstream ss(line);
                string update;
                vector<int> pages;

                while (getline(ss, update, ',')) {
                    pages.push_back(stoi(update));
                }
                updates->push_back(pages);
            }
        }
        file.close();
    }
}

bool is_ordered(set<pair<int, int>> order_rules, vector<int> pages) {
    for (int i = 0; i < pages.size() - 1; i++) {
        if (order_rules.find({ pages[i + 1], pages[i] }) != order_rules.end()) {
            return false;
        }
    }

    return true;
}

int part1(set<pair<int, int>> order_rules, vector<vector<int>> updates) {
    int sum = 0;
    for (vector<int> pages : updates) {
        if (is_ordered(order_rules, pages)) {
            sum += pages[pages.size() / 2];
        }
    }

    return sum;
}

int part2(set<pair<int, int>> order_rules, vector<vector<int>> updates) {
    int sum = 0;
    vector<vector<int>> unordered_pages;

    for (int i = 0; i < updates.size(); i++) {
        if (!is_ordered(order_rules, updates[i])) {
            unordered_pages.push_back(updates[i]);
        }
    }

    for (vector<int> pages : unordered_pages) {
        bool unordered = true;
        while (unordered) {
            unordered = false;
            for (int i = 0; i < pages.size(); i++) {
                for (int j = i + 1; j < pages.size(); j++) {
                    if (order_rules.find({ pages[j], pages[i] }) != order_rules.end()) {
                        unordered = true;
                        swap(pages[i], pages[j]);
                    }
                }
            }
        }
        sum += pages[pages.size() / 2];
    }

    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    set<pair<int, int>> order_rules;
    vector<vector<int>> updates;

    parse_input(filename, &order_rules, &updates);
    printf("Part 1: %d\nPart 2: %d\n", part1(order_rules, updates), part2(order_rules, updates));

    return 0;
}
