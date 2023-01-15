// Copyright 2020 Karim Sammouri

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Invalid Input" << std::endl;
        return 0;
    }

    int num = stoi(argv[1]);

    std::cout << "Enter " << num << " number(s):" << std::endl;

    int numbers[num];

    int count = 0;
    for (int *i = numbers; count < num; i++, count++) {
        std::cin >> *i;
    }

    count = 0;
    for (int *i  = &numbers[num - 1]; count < num; i--, count++) {
        std::cout << "The factors of " << *i << " are:" << std::endl;
        for (int j = *i - 1; j > 1; j--) {
            if (*i % j == 0) {
                std::cout << j;
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}
