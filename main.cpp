#include <iostream>
#include <ext/number.hpp>


int main(int argc, char** argv)
{
    ext::number<int> number_a {1};
    ext::number<int> number_b {2};
    ext::number<int> number_c {3};

    std::cout << (number_a + number_b) << std::endl;

    return 0;
}
