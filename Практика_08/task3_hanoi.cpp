#include <iostream>

void move_ingredients(int count, int from, int to, int auxiliary) {
    if (count <= 0) {
        return;
    }

    move_ingredients(count - 1, from, auxiliary, to);
    std::cout << "Ingredient " << count << " move from " << from << " to " << to << '\n';
    move_ingredients(count - 1, auxiliary, to, from);
}

int main() {
    int n;
    if (!(std::cin >> n) || n < 0) {
        return 1;
    }

    move_ingredients(n, 1, 3, 2);
    return 0;
}
