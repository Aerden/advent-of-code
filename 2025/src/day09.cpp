#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Vec2 {
    int x, y;
};

struct Edge {
    Vec2 a, b;
};

std::vector<Vec2> parse(char* filename) {
    std::vector<Vec2> output;
    std::ifstream inputFile(filename);
    std::string line;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int x, y;
        char comma;

        if (ss >> x >> comma >> y) {
            output.push_back({ x, y });
        }
    }

    return output;
}

long long part1(std::vector<Vec2> input) {
    long long res = 0;
    
    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            long long width = std::abs(input[j].x - input[i].x) + 1;
            long long height = std::abs(input[j].y - input[i].y) + 1;
            res = std::max(res, width * height);
        }
    }

    return res;
}

bool intersects(Edge a, Edge b) {
    int aMinX = std::min(a.a.x, a.b.x);
    int aMinY = std::min(a.a.y, a.b.y);
    int aMaxX = std::max(a.a.x, a.b.x);
    int aMaxY = std::max(a.a.y, a.b.y);
    int bMinX = std::min(b.a.x, b.b.x);
    int bMinY = std::min(b.a.y, b.b.y);
    int bMaxX = std::max(b.a.x, b.b.x);
    int bMaxY = std::max(b.a.y, b.b.y);

    return bMaxX > aMinX && bMinX < aMaxX &&
           bMaxY > aMinY && bMinY < aMaxY;
}

long long part2(std::vector<Vec2> input) {
    long long res = 0;
    std::vector<Edge> edges(input.size());
    
    for (int i = 0; i < input.size(); i++) {
        edges[i] = { input[i], input[(i + 1) % input.size()] };
    }

    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            long long width = std::abs(input[j].x - input[i].x) + 1;
            long long height = std::abs(input[j].y - input[i].y) + 1;
            long long area = width * height;
            
            if (area > res) {
                bool hasIntersection = false;
                for (int k = 0; k < edges.size() && !hasIntersection; k++) {
                    hasIntersection = hasIntersection || intersects(edges[k], { input[i], input[j] });
                }

                res = hasIntersection ? res : area;
            }
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
    auto input = parse(argv[1]);
    printf("Part 1: %lld\n", part1(input));
    printf("Part 2: %lld\n", part2(input));

    return 0;
}
