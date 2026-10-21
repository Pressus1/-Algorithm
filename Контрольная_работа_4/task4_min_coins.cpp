#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

int main() {
    int denominationCount;
    int amount;
    if (!(std::cin >> denominationCount >> amount) || denominationCount <= 0 || amount < 0) {
        std::cerr << "Некорректные входные данные\n";
        return 1;
    }

    std::vector<int> denominations(denominationCount);
    for (int& denomination : denominations) {
        if (!(std::cin >> denomination) || denomination <= 0) {
            std::cerr << "Номиналы должны быть положительными\n";
            return 1;
        }
    }

    const int infinity = std::numeric_limits<int>::max() / 2;
    std::vector<int> minimumCoins(amount + 1, infinity);
    minimumCoins[0] = 0;

    for (int current = 1; current <= amount; ++current) {
        for (int denomination : denominations) {
            if (denomination <= current) {
                minimumCoins[current] = std::min(
                    minimumCoins[current],
                    minimumCoins[current - denomination] + 1
                );
            }
        }
    }

    std::cout << (minimumCoins[amount] == infinity ? -1 : minimumCoins[amount]) << '\n';
    return 0;
}
