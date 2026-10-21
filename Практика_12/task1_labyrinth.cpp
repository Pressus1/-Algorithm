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

    std::vector<std::vector<char>> maze(n, std::vector<char>(m));
    std::pair<int, int> exit_cell{-1, -1};
    int exit_count = 0;
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < m; ++column) {
            if (!(std::cin >> maze[row][column])) {
                std::cerr << "Not enough maze cells\n";
                return 1;
            }
            const char cell = maze[row][column];
            if (cell != '0' && cell != '1' && cell != 'P' && cell != 'E') {
                std::cerr << "Unknown cell symbol: " << cell << '\n';
                return 1;
            }
            if (cell == 'E') {
                exit_cell = {row, column};
                ++exit_count;
            }
        }
    }

    if (exit_count != 1) {
        std::cerr << "The maze must contain exactly one E cell\n";
        return 1;
    }

    const int unreachable = std::numeric_limits<int>::lowest() / 4;
    std::vector<std::vector<int>> best(n, std::vector<int>(m, unreachable));
    if (maze[0][0] != '1') {
        best[0][0] = maze[0][0] == 'P' ? 1 : 0;
    }

    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < m; ++column) {
            if ((row == 0 && column == 0) || maze[row][column] == '1') {
                continue;
            }
            int previous = unreachable;
            if (row > 0) {
                previous = std::max(previous, best[row - 1][column]);
            }
            if (column > 0) {
                previous = std::max(previous, best[row][column - 1]);
            }
            if (previous != unreachable) {
                best[row][column] = previous + (maze[row][column] == 'P' ? 1 : 0);
            }
        }
    }

    const int answer = best[exit_cell.first][exit_cell.second];
    std::cout << (answer == unreachable ? -1 : answer) << '\n';
}
