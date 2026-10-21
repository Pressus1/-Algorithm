#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class BigInteger {
public:
    explicit BigInteger(const std::string& text = "0") {
        std::size_t start = 0;
        if (!text.empty() && text[0] == '-') {
            negative_ = true;
            start = 1;
        }

        for (std::size_t end = text.size(); end > start;) {
            const std::size_t begin = end >= start + 9 ? end - 9 : start;
            digits_.push_back(static_cast<std::uint32_t>(
                std::stoul(text.substr(begin, end - begin))));
            end = begin;
        }

        if (digits_.empty()) {
            digits_.push_back(0);
        }
        normalize();
    }

    BigInteger& operator*=(const BigInteger& other) {
        std::vector<std::uint32_t> product(digits_.size() + other.digits_.size(), 0);

        for (std::size_t i = 0; i < digits_.size(); ++i) {
            std::uint64_t carry = 0;
            for (std::size_t j = 0; j < other.digits_.size(); ++j) {
                const std::uint64_t current = product[i + j] + carry
                    + static_cast<std::uint64_t>(digits_[i]) * other.digits_[j];
                product[i + j] = static_cast<std::uint32_t>(current % BASE);
                carry = current / BASE;
            }
            product[i + other.digits_.size()] = static_cast<std::uint32_t>(carry);
        }

        digits_ = std::move(product);
        negative_ = negative_ != other.negative_;
        normalize();
        return *this;
    }

    std::string to_string() const {
        std::ostringstream output;
        if (negative_) {
            output << '-';
        }
        output << digits_.back();
        for (std::size_t i = digits_.size() - 1; i-- > 0;) {
            output << std::setw(9) << std::setfill('0') << digits_[i];
        }
        return output.str();
    }

private:
    static constexpr std::uint64_t BASE = 1'000'000'000ULL;
    std::vector<std::uint32_t> digits_;
    bool negative_ = false;

    void normalize() {
        while (digits_.size() > 1 && digits_.back() == 0) {
            digits_.pop_back();
        }
        if (digits_.size() == 1 && digits_[0] == 0) {
            negative_ = false;
        }
    }
};

BigInteger fast_power(BigInteger base, unsigned long long exponent) {
    BigInteger result("1");

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }

    return result;
}

int main() {
    std::string base;
    unsigned long long exponent;

    if (!(std::cin >> base >> exponent)) {
        return 1;
    }

    std::cout << fast_power(BigInteger(base), exponent).to_string() << '\n';
    return 0;
}
