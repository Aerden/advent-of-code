#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

class DisjointSet {
public:
    std::vector<int> parent, size;

    DisjointSet(int n) {
        parent.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findParent(int node) {
        if (node == parent[node]) return node;
        return parent[node] = findParent(parent[node]);
    }

    void unionBySize(int x, int y) {
        int px = findParent(x);
        int py = findParent(y);
        if (px == py) return;

        if (size[px] < size[py]) {
            parent[px] = py;
            size[py] += size[px];
        } else {
            parent[py] = px;
            size[px] += size[py];
        }
    }
};

struct Vec3 {
    int x, y, z;
};

std::vector<Vec3> parse(char* filename) {
    std::vector<Vec3> output;
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int x, y, z;
        char comma;

        if (ss >> x >> comma >> y >> comma >> z) {
            output.push_back({ x, y, z });
        }
    }

    return output;
}

int part1(std::vector<Vec3> input) {
    int res = 0;
    std::vector<std::vector<long long>> distances(input.size(), std::vector<long long>(input.size(), 0));

    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            int x1 = input[i].x, x2 = input[j].x;
            int y1 = input[i].y, y2 = input[j].y;
            int z1 = input[i].z, z2 = input[j].z;
            long long dist = std::pow(std::abs(x1 - x2), 2) + std::pow(std::abs(y1 - y2), 2) + std::pow(std::abs(z1 - z2), 2);
            distances[i][j] = dist;
            distances[j][i] = dist;
        }
    }

    std::vector<std::pair<long long, std::pair<int, int>>> edges;
    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            edges.push_back({ distances[i][j], { i, j } });
        }
    }
    std::sort(edges.begin(), edges.end());

    DisjointSet set(input.size());
    for (int i = 0; i < 1000; i++) {
        int x = edges[i].second.first;
        int y = edges[i].second.second;
        
        if (set.findParent(x) != set.findParent(y)) {
            set.unionBySize(x, y);
        }
    }

    std::sort(set.size.begin(), set.size.end(), std::greater<int>());
    res = set.size[0] * set.size[1] * set.size[2];
    return res;
}

int part2(std::vector<Vec3> input) {
    int res = 0;
    std::vector<std::vector<long long>> distances(input.size(), std::vector<long long>(input.size(), 0));

    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            int x1 = input[i].x, x2 = input[j].x;
            int y1 = input[i].y, y2 = input[j].y;
            int z1 = input[i].z, z2 = input[j].z;
            long long dist = std::pow(std::abs(x1 - x2), 2) + std::pow(std::abs(y1 - y2), 2) + std::pow(std::abs(z1 - z2), 2);
            distances[i][j] = dist;
            distances[j][i] = dist;
        }
    }

    std::vector<std::pair<long long, std::pair<int, int>>> edges;
    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            edges.push_back({ distances[i][j], { i, j } });
        }
    }
    std::sort(edges.begin(), edges.end());

    DisjointSet set(input.size());
    int count = 0;
    for (int i = 0; i < edges.size(); i++) {
        int x = edges[i].second.first;
        int y = edges[i].second.second;
        
        if (set.findParent(x) != set.findParent(y)) {
            set.unionBySize(x, y);
            count++;
            if (count == input.size() - 1) {
                res = input[x].x * input[y].x;
                break;
            }
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %d\n", part1(input));
    printf("Part 2: %d\n", part2(input));
    
    return 0;
}
