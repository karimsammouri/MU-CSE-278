/**
 * Copyright 2020 Karim Sammouri
 * Student: Karim R. Sammouri
 * Instructor: Prof. Alan Ferrenberg
 * Course: CSE 278 - F
 * Date: Sep 1, 2020
 * Description: Lab 2 - part 2 (programming) assignment
 * Attribution: All code aside from the template given by the
 * course is written by me.
 */

#include <iostream>
#include <string>

/*
 * A simple string operation program
 */
int main(int argc, char** argv) {
    // Variables to track word count and largest word
    std::string line;
    size_t wordCount = 0;
    std::string largestWord;
    std::string currentWord;

    // Get user input from the user
    std::cout << "Enter a line: ";
    std::getline(std::cin, line);

    // Variable to track current position in string
    size_t pointer = 0;

    // Loop through the input while it has spaces
    while (pointer < line.size()) {
        // Increase word count
        wordCount++;
        // Get the current word
        if (line.find(" ", pointer) != std::string::npos) {
            currentWord = line.substr(pointer, 
line.find(" ", pointer) - pointer);
        } else {
            currentWord = line.substr(pointer);
        }
        // Check if the current word is the new largest
        if (currentWord.size() >=  largestWord.size()) {
            largestWord = currentWord;
        }
        // Move to the next word in the line
        pointer += currentWord.size() + 1;
    }

    // Print the output
    std::cout << "Number of words: " << wordCount << "\n";
    std::cout << "Largest word: " << largestWord << "\n";
    return 0;
}

