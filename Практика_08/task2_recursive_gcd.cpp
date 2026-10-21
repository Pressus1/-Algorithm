#include <cstdint>
#include <iostream>

std::uint64_t gcd_recursive(std::uint64_t a, std::uint64_t b) {
    return b == 0 ? a : gcd_recursive(b, a % b);
}

int main() {
    std::uint64_t a;
    std::uint64_t b;

    if (!(std::cin >> a >> b)) {
        return 1;
    }

    std::cout << gcd_recursive(a, b) << '\n';
    return 0;
}
