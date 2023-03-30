#include <iostream>

int main()
{
    unsigned long long num, reversed_num = 0;
    for (std::cin >> num; num != 0; num /= 10) {
        reversed_num = reversed_num * 10 + num % 10;
    }
    std::cout << reversed_num << "\n";
}
