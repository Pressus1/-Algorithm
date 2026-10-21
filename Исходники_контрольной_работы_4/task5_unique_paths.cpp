#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <vector>

class BigUnsigned {
public:
    explicit BigUnsigned(std::uint32_t value = 0) : digits_{value} {}

    BigUnsigned& operator+=(const BigUnsigned& other) {
        const std::size_t targetSize = std::max(digits_.size(), other.digits_.size());
        digits_.resize(targetSize, 0);

        std::uint64_t carry = 0;
        for (std::size_t index = 0; index < targetSize; ++index) {
            const std::uint64_t right =
                index < other.digits_.size() ? other.digits_[index] : 0;
            const std::uint64_t sum = digits_[index] + right + carry;
            digits_[index] = static_cast<std::uint32_t>(sum % base);
            carry = sum / base;
        }
        if (carry != 0) {
            digits_.push_back(static_cast<std::uint32_t>(carry));
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& output, const BigUnsigned& value) {
        output << value.digits_.back();
        for (auto iterator = value.digits_.rbegin() + 1;
             iterator != value.digits_.rend(); ++iterator) {
            output << std::setw(9) << std::setfill('0') << *iterator;
        }
        return output;
    }

private:
    static constexpr std::uint32_t base = 1'000'000'000;
    std::vector<std::uint32_t> digits_;
};

int main() {
    int rows;
    int columns;
    if (!(std::cin >> rows >> columns) || rows <= 0 || columns <= 0) {
        std::cerr << "Размеры сетки должны быть положительными\n";
        return 1;
    }

    std::vector<BigUnsigned> paths(columns, BigUnsigned(1));
    for (int row = 1; row < rows; ++row) {
        for (int column = 1; column < columns; ++column) {
            paths[column] += paths[column - 1];
        }
    }

    std::cout << paths.back() << '\n';
    return 0;
}
