// Copyright 2020 Karim Sammouri

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

void print(string hexStr) {
    cout << "| ";

    for (int i = hexStr.size() - 2; i >= 0; i-=2) {
        cout << hexStr.substr(i, 2);
        cout << " | ";
    }

    cout << endl;
}

void process(string input) {
    ifstream inputFile(input);
    string line;

    // Process input
    while (getline(inputFile, line)) {
        // Split input data
        vector<string> strVec;
        boost::split(strVec, line, boost::is_any_of(" "));

        // Stringstream to hold the hex value
        stringstream hexVal;

        // Convert data
        int num = stoi(strVec[3]);

        // Put data into stream as hex value
        hexVal << hex << num;

        // Check to see if hex value size is even
        if (hexVal.str().size() % 2 == 1) {
            // Clear stringstream
            hexVal.str("");

            // Put data in the stream with a leading value
            hexVal << "0" << hex << num;
        }

        // Print out hex in little ending splitting the pairs
        // with a " | " character (e.g., | 01 | )
        string hexStr = hexVal.str();
        print(hexStr);
    }
}

int main(int argc, char* argv[]) {
    // Check file input
    if (argc != 2) {
        if (argc == 1) {
            std::cerr << "Need to supply input file" << std::endl;
            return 0;
        }
        std::cerr << "Usage: ./lab9 [inputFile]" << std::endl;
        return 0;
    }

    // Setup any necessary stream(s)
    string input = argv[1];
    ifstream inputFile(input);

    if (!inputFile.good()) {
        cerr << "There was an error opening the file" << endl;
        return 0;
    }

    process(input);
}
