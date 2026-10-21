#include <cstdint>
#include <iostream>
#include <set>
#include <string>
#include <vector>

static std::u32string decode_utf8(const std::string& input) {
    std::u32string output;
    for (std::size_t index = 0; index < input.size();) {
        const unsigned char first = static_cast<unsigned char>(input[index]);
        std::uint32_t codepoint = 0;
        std::size_t length = 0;
        if (first < 0x80) {
            codepoint = first;
            length = 1;
        } else if ((first & 0xE0) == 0xC0) {
            codepoint = first & 0x1F;
            length = 2;
        } else if ((first & 0xF0) == 0xE0) {
            codepoint = first & 0x0F;
            length = 3;
        } else if ((first & 0xF8) == 0xF0) {
            codepoint = first & 0x07;
            length = 4;
        } else {
            ++index;
            continue;
        }
        if (index + length > input.size()) {
            break;
        }
        bool valid = true;
        for (std::size_t offset = 1; offset < length; ++offset) {
            const unsigned char next = static_cast<unsigned char>(input[index + offset]);
            if ((next & 0xC0) != 0x80) {
                valid = false;
                break;
            }
            codepoint = (codepoint << 6) | (next & 0x3F);
        }
        if (valid) {
            output.push_back(static_cast<char32_t>(codepoint));
            index += length;
        } else {
            ++index;
        }
    }
    return output;
}

static std::string encode_utf8(const std::u32string& input) {
    std::string output;
    for (std::uint32_t codepoint : input) {
        if (codepoint <= 0x7F) {
            output.push_back(static_cast<char>(codepoint));
        } else if (codepoint <= 0x7FF) {
            output.push_back(static_cast<char>(0xC0 | (codepoint >> 6)));
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
        } else if (codepoint <= 0xFFFF) {
            output.push_back(static_cast<char>(0xE0 | (codepoint >> 12)));
            output.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
        } else {
            output.push_back(static_cast<char>(0xF0 | (codepoint >> 18)));
            output.push_back(static_cast<char>(0x80 | ((codepoint >> 12) & 0x3F)));
            output.push_back(static_cast<char>(0x80 | ((codepoint >> 6) & 0x3F)));
            output.push_back(static_cast<char>(0x80 | (codepoint & 0x3F)));
        }
    }
    return output;
}

static bool is_word_core(char32_t symbol) {
    return (symbol >= U'0' && symbol <= U'9') ||
           (symbol >= U'A' && symbol <= U'Z') ||
           (symbol >= U'a' && symbol <= U'z') ||
           (symbol >= 0x0400 && symbol <= 0x052F);
}

static bool is_hyphen(char32_t symbol) {
    return symbol == U'-' || symbol == 0x2010 || symbol == 0x2011;
}

static char32_t lower_case(char32_t symbol) {
    if (symbol >= U'A' && symbol <= U'Z') {
        return symbol + (U'a' - U'A');
    }
    if (symbol >= 0x0410 && symbol <= 0x042F) {
        return symbol + 0x20;
    }
    if (symbol == 0x0401) {
        return 0x0451;
    }
    return symbol;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input((std::istreambuf_iterator<char>(std::cin)), std::istreambuf_iterator<char>());
    const std::u32string text = decode_utf8(input);

    std::set<std::u32string> seen;
    std::vector<std::u32string> words;
    std::u32string current;

    const auto flush = [&]() {
        if (!current.empty() && seen.insert(current).second) {
            words.push_back(current);
        }
        current.clear();
    };

    for (std::size_t index = 0; index < text.size(); ++index) {
        const char32_t symbol = text[index];
        if (is_word_core(symbol)) {
            current.push_back(lower_case(symbol));
        } else if (is_hyphen(symbol) && !current.empty() &&
                   index + 1 < text.size() && is_word_core(text[index + 1])) {
            current.push_back(U'-');
        } else {
            flush();
        }
    }
    flush();

    for (const std::u32string& word : words) {
        std::cout << encode_utf8(word) << '\n';
    }
}
