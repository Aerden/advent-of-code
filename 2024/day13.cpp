#include <cmath>
#include <fstream>
#include <vector>
#include <regex>

using namespace std;

const int A_COST = 3;
const int B_COST = 1;

struct machine {
    long long ax, ay, bx, by, prize_x, prize_y;
};

vector<machine> parse_input(string filename) {
    ifstream file(filename);
    stringstream buffer;
    buffer << file.rdbuf();
    string buffer_string = buffer.str();

    regex rgx(R"~((Button A: X\+(\d+), Y\+(\d+)\nButton B: X\+(\d+), Y\+(\d+)\nPrize: X=(\d+), Y=(\d+)))~");

    sregex_iterator begin(buffer_string.begin(), buffer_string.end(), rgx);
    sregex_iterator end;

    vector<machine> machines;
    for (auto iter = begin; iter != end; ++iter) {
        smatch match = *iter;
        machines.push_back({ stoi(match[2]), stoi(match[3]),
                             stoi(match[4]), stoi(match[5]),
                             stoi(match[6]), stoi(match[7]) });
    }

    return machines;
}

long long calc(const machine& machine) {
    double a1 = machine.ax, a2 = machine.ay;
    double b1 = machine.bx, b2 = machine.by;
    double c1 = machine.prize_x, c2 = machine.prize_y;

    double D = a1 * b2 - a2 * b1;
    double Dx = c1 * b2 - c2 * b1;
    double Dy = a1 * c2 - a2 * c1;

    if (D == 0) {
        return 0;
    } else {
        double A = Dx / D;
        double B = Dy / D;
        
        if (floor(A) != A || floor(B) != B) {
            return 0;
        }

        return (long)A * A_COST + (long)B * B_COST;
    }
}

long long part1(const vector<machine>& machines) {
    long long sum = 0;
    for (auto& machine : machines) {
        sum += calc(machine);
    }
    return sum;
}

long long part2(const vector<machine>& machines) {
    long long sum = 0;
    for (auto machine : machines) {
        machine.prize_x += 10000000000000;
        machine.prize_y += 10000000000000;
        sum += calc(machine);
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }
    string filename = argv[1];
    auto machines = parse_input(filename);

    printf("Part 1: %lld\nPart 2: %lld\n", part1(machines), part2(machines));

    return 0;
}
