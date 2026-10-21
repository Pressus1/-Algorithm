#include <algorithm>
#include <iostream>
#include <vector>

static bool can_partition(const std::vector<long long>& calories, int days, long long limit) {
    int groups = 1;
    long long first_in_group = calories.front();
    for (long long value : calories) {
        if (value - first_in_group > limit) {
            ++groups;
            first_in_group = value;
        }
    }
    return groups <= days;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int days = 0;
    if (!(std::cin >> n >> days) || n <= 0 || days <= 0 || days > n) {
        std::cerr << "Expected 1 <= D <= N\n";
        return 1;
    }

    std::vector<long long> calories(n);
    for (long long& value : calories) {
        if (!(std::cin >> value)) {
            std::cerr << "Not enough calorie values\n";
            return 1;
        }
    }
    std::sort(calories.begin(), calories.end());

    long long low = 0;
    long long high = calories.back() - calories.front();
    while (low < high) {
        const long long middle = low + (high - low) / 2;
        if (can_partition(calories, days, middle)) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }

    std::cout << low << '\n';
}
