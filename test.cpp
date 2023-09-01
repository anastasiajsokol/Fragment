#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
template <typename iter_t>
void bubble(iter_t begin, iter_t end){
    for(iter_t i = begin; i < end; ++i){
        for(iter_t j = begin; j < end - (i - begin); ++j){
            iter_t n = j + 1;
            if(*j > *n){
                std::iter_swap(j, n);
            }
        }
    }
}

int main() {
    int values[] = {4, 2, 3, 1};

    bubble(values, values + sizeof(values) / sizeof(int));

    for(size_t i = 0; i < sizeof(values) / sizeof(int); ++i){
        std::cout << values[i] << " ";
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
}