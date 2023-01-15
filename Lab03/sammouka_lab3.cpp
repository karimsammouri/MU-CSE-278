// Copyright 2020 Karim Sammouri

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <climits>

int computeSum(std::vector<int> vector) {
    int sum = 0;

    for (auto num : vector) {
        sum += num;
    }

    return sum;
}

double computeAverage(std::vector<int> vector) {
    double sum = 0.0;
    int count = 0;
    double average;

    for (auto num : vector) {
        count++;
        sum += num;
    }

    average = sum / count;

    return average;
}

int computeMax(std::vector<int> vector) {
    int max = INT_MIN;

    for (auto num : vector) {
        if (num > max) {
            max = num;
        }
    }

    return max;
}

int computeMin(std::vector<int> vector) {
    int min = INT_MAX;

    for (auto num : vector) {
        if (num < min) {
            min = num;
        }
    }

    return min;
}

void printResult(std::ostream& out, int sum, int min, double average, int max) {
    out << "Sum: " << sum << std::endl;
    out << "Min: " << min << std::endl;
    out << "Average: " << average << std::endl;
    out << "Max: " << max << std::endl;
}


int main(int argc, char* argv[]) {
    // Verify the correct number of arguments
    if (argc != 3) {
        std::cerr << "Specify input and output files" << std::endl;
        return 0;
    }

    // Create streams with command line arguments
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);

    // Check streams were successfully created
    if (!input.good() || !output.good()) {
        std::cerr << "Error opening input or output streams" << std::endl;
        return 0;
    }

    // Read input file to some data structure
    std::vector<int> vector;
    std::string numStr;
    int num;
    while (getline(input, numStr)) {
        num = stoi(numStr);
        vector.push_back(num);
    }

    // Compute the sum, average, min, max
    int sum = computeSum(vector);
    double average = computeAverage(vector);
    int min = computeMin(vector);
    int max = computeMax(vector);

    // Display results -- DO NOT MODIFY BELOW THIS LINE
    printResult(output, sum, min, average, max);
    printResult(std::cout, sum, min, average, max);
}
