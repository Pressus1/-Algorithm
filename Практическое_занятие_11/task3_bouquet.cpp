#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 0;
    int k = 0;
    int limit = 0;
    if (!(std::cin >> n >> k >> limit) || n <= 0 || k <= 0 || k > n || limit <= 0 || limit > k) {
        std::cerr << "Expected N > 0, 1 <= K <= N and 1 <= L <= K\n";
        return 1;
    }

    std::vector<long long> cost(n);
    for (long long& value : cost) {
        if (!(std::cin >> value)) {
            std::cerr << "Not enough plant costs\n";
            return 1;
        }
    }

    // The methodical material provides only costs and explicitly calls all plants distinct.
    // Therefore every plant type has multiplicity one and L cannot further restrict the choice.
    std::sort(cost.begin(), cost.end(), std::greater<long long>());
    long long answer = 0;
    for (int index = 0; index < k; ++index) {
        answer += cost[index];
    }
    std::cout << answer << '\n';
}
