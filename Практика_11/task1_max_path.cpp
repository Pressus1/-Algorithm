#include <algorithm>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int m = 0;
    if (!(std::cin >> n >> m) || n <= 0 || m <= 0) {
        std::cerr << "Expected positive N and M\n";
        return 1;
    }

    std::vector<std::vector<long long>> value(n, std::vector<long long>(m));
    for (auto& row : value) {
        for (long long& cell : row) {
            if (!(std::cin >> cell)) {
                std::cerr << "Not enough matrix values\n";
                return 1;
            }
        }
    }

    const long long minus_infinity = std::numeric_limits<long long>::lowest() / 4;
    std::vector<std::vector<long long>> best(n, std::vector<long long>(m, minus_infinity));
    std::vector<std::vector<char>> parent(n, std::vector<char>(m, 0));
    best[0][0] = value[0][0];

    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < m; ++column) {
            if (row == 0 && column == 0) {
                continue;
            }

            const long long from_top = row > 0 ? best[row - 1][column] : minus_infinity;
            const long long from_left = column > 0 ? best[row][column - 1] : minus_infinity;
            if (from_top >= from_left) {
                best[row][column] = from_top + value[row][column];
                parent[row][column] = 'U';
            } else {
                best[row][column] = from_left + value[row][column];
                parent[row][column] = 'L';
            }
        }
    }

    std::vector<std::pair<int, int>> path;
    int row = n - 1;
    int column = m - 1;
    while (true) {
        path.emplace_back(row, column);
        if (row == 0 && column == 0) {
            break;
        }
        if (parent[row][column] == 'U') {
            --row;
        } else {
            --column;
        }
    }
    std::reverse(path.begin(), path.end());

    for (const auto& [path_row, path_column] : path) {
        std::cout << path_row << ' ' << path_column << '\n';
    }
}
