#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

int main() {
    std::string str {"hello world"};
    std::string str_reversed;
    std::vector<char> up_vec;

    // Transform lower case string into upper case vector
    std::transform(str.begin(), str.end(), std::back_inserter(up_vec),
            [](char c) { return std::toupper(c); });

    std::cout << "Vector: ";
    std::for_each(up_vec.begin(), up_vec.end(), [](char c){std::cout << c;});
    std::cout << std::endl;

    // Transfrom string into upper case and store the value in the same string
    std::for_each(str.begin(), str.end(), [](char &c) {c = std::toupper(c);} );

    // Count the number of upper case characters
    int nchar = std::count_if(str.begin(), str.end(), [](char c) {return std::isupper(c);});
    std::cout << nchar << " upper case letters: " << str << std::endl;

    // Reverse string
    str_reversed.resize(str.size());
    std::reverse_copy(str.begin(), str.end(), str_reversed.begin());
    std::cout << "Reversed string: " << str_reversed << std::endl;

    return 0;
}
