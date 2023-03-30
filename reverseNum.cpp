#include <iostream>

int main()
{
    unsigned long long num, reversed_num = 0;
    std::cin >> num;
    for(;num != 0;)
    {
        reversed_num = (reversed_num * 10) + (num%10);
        num /= 10;
    }

    std::cout << reversed_num << "\n";

    return 0;
}