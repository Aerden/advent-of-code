#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

vector<int> parse_input(string filename) {
    ifstream file(filename);
    string line;
    vector<int> disk_map;

    char ch;
    int idx = 0;
    int file_id = 0;
    while (file >> noskipws >> ch) {
        if (ch == '\n') break; // Just in case, will break on CRLF files
        if (idx % 2 == 0) {
            disk_map.insert(disk_map.end(), (int)ch - '0', file_id);
            file_id++;
        } else {
            disk_map.insert(disk_map.end(), (int)ch - '0', -1);
        }

        idx++;
    }

    return disk_map;
}

long long checksum(const vector<int>& disk_map) {
    long long sum = 0;

    for (int i = 0; i < disk_map.size(); i++) {
        if (disk_map[i] == -1) continue;

        sum += i * disk_map[i];
    }
    return sum;
}

long long part1(vector<int> disk_map) {
    int start = 0;
    int end = disk_map.size() - 1;
    
    while (start < end) {
        while (disk_map[start] != -1) start++;
        while (disk_map[end] == -1) end--;

        if (start < end) {
            disk_map[start] = disk_map[end];
            disk_map[end] = -1;
        }
    }

    return checksum(disk_map);
}

long long part2(vector<int> disk_map) {
    vector<pair<int, int>> files;
    vector<pair<int, int>> free;
    
    int last = 0;
    for (int i = 0, count = 1; i < disk_map.size(); i++) {
        if (i < disk_map.size() - 1 && disk_map[i] == disk_map[i + 1]) {
            count++;
        } else {
            if (disk_map[i] == -1) {
                free.push_back({ count, last });
            } else {
                files.push_back({ count, last });
            }

            last = i + 1;
            count = 1;
        }
    }

    for (int i = files.size() - 1; i >= 0; i--) {
        int length = files[i].first;
        auto it = find_if(free.begin(), free.end(), [length](const auto&p) { return p.first >= length; });

        if (it != free.end()) {
            if (it->second > files[i].second) continue; // Make sure we're not moving blocks to the right

            for (int j = 0; j < length; j++) {
                disk_map[it->second + j] = disk_map[files[i].second + j];
                disk_map[files[i].second + j] = -1;
            }
            if (it->first == length) {
                free.erase(it);
            } else {
                it->first -= length;
                it->second += length;
            }
        }
    }

    return checksum(disk_map);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    vector<int> disk_map = parse_input(filename);

    printf("Part 1: %lld\nPart 2: %lld\n", part1(disk_map), part2(disk_map));

    return 0;
}
