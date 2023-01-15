// Copyright 2020 Karim Sammouri

#include <iostream>
#include <string>

int main() {
    int count = 0;
    std::string vowels = "aeiouAEIOU";

    std::cout << "Enter a sentence: ";

    std::string word;
    while (std::cin >> word) {
        if (vowels.find(word[0]) != std::string::npos) {
            count++;
        }
    }

    std::cout << count << std::endl;
}




