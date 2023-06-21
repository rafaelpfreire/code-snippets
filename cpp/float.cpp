#include <iostream>
#include <iomanip>

size_t ndigits(size_t n) {
    int d = 0;
    while(n != 0) {
        n = n / 10;
        d++;
    }

    return d;
}

void print_spaces(size_t n) {
    for(size_t i = 0; i < n; i++)
        std::cout << " ";
}

int main() {
    const size_t max = 10000001;
    const size_t maxdig = 8;
    const float fvar = 1.0f / 3.0f;
    const double dvar = 1.0 / 3.0;

    std::cout << std::fixed << std::setprecision(10);

    for(size_t x = 1; x < max; x*=10) {
        float fres = fvar + x;
        double dres = dvar + x;

        size_t spaces = maxdig - ndigits(x);
        print_spaces(spaces);
        std::cout << fres;
        print_spaces(spaces+5);
        std::cout << dres << std::endl;
    }

    return 0;
}
