#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
int main() {
    std::string s = "Hello World";
    std::fill_n(std::back_inserter(s), 3, '!');
    for (const auto& n : s)
        std::cout << n << ' ';
    std::cout << '\n';
}