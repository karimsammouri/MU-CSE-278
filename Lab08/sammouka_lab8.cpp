// Copyright 2020 Karim Sammouri

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

void interactive() {
    // Connect to database with: database, server, userID, password
    mysqlpp::Connection database("cse278", "localhost", "cse278", "S3rul3z");

    // Variable to build query string
    std::string qString;
    
    // Get user input for query
    while (getline(std::cin, qString) && qString.compare("quit") != 0) { 
        // Create a query
        mysqlpp::Query query = database.query();
        query << qString;

        try {
            // Check query is correct
            query.parse();

            // Execute query
            mysqlpp::StoreQueryResult result = query.store();

            // Results is a 2D vector of mysqlpp::String objects.
            // Print the results.
            std::cout << "-----Query Result-----" << std::endl;
            for (size_t row = 0; (row < result.size()); row++) {
                 std::cout << "|";
                 for (size_t col = 0; (col < result[0].size()); col++) {
                      std::cout << " " << result[row][col] << " ";
                      std::cout << "|";
                 }
                 std::cout << std::endl;
            }
            std::cout << "------End Result------" << std::endl;
        } catch(mysqlpp::BadQuery e) {
            std::cerr << "Query: " << qString << std::endl;
            std::cerr << "Query is not correct SQL syntax" << std::endl;
        }
    }
}

std::string generateLoadQuery(std::string& line) {
    // Create base insert query string
    std::string query = "INSERT INTO ";

    // Split file on commas
    std::vector<std::string> strVec;
    boost::split(strVec, line, boost::is_any_of(","));

    // Start building query from split files (table name)
    query += strVec[0] + " (";

    // Strings to hold attributes and values
    std::vector<std::string> attributes, attributeValues;

    // Build attribute and value strings
    for (int i = 1; i < strVec.size(); i++) {
        attributes.push_back(strVec[i].substr(0, strVec[i].find(":")));
        attributeValues.push_back(strVec[i].substr(strVec[i].find(":") + 1));
    }

    // Form full query string
    for (int i = 0; i < attributes.size(); i++) {
        if (i < attributes.size() - 1) {
            query += attributes[i] + ", ";
        } else {
            query += attributes[i] + ") VALUES (";
        }
    }

    for (int i = 0; i < attributeValues.size(); i++) {
        if (i < attributeValues.size() - 1) {
            query += attributeValues[i] + ", ";
        } else {
            query += attributeValues[i] + ");";
        }
    }

    return query;
}

void loadData(std::string& path) {
    // Open file stream
    std::ifstream input(path);

    // Connect to database with: database, server, userID, password
    mysqlpp::Connection database("cse278", "localhost", "cse278", "S3rul3z");

    // Some necessary variables for the file IO
    std::string line;
    std::string queryStr;
    int lineNum = 0;

    // Read file line-by-line
    while (getline(input, line)) {
        // Create query string from current line
        queryStr = generateLoadQuery(line);

        // Create mysql++ query
        mysqlpp::Query query = database.query();
        query << queryStr;

        try {
            // Check query is correct
            query.parse();

            // Execute Query
            mysqlpp::StoreQueryResult result = query.store();
            lineNum++;
            std::cout << "Data Line " << lineNum << " Loaded" << std::endl;   
        } catch(mysqlpp::BadQuery e) {
            std::cerr << "Query: " << queryStr<< std::endl;
            std::cerr << "Query is not correct SQL syntax" << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    // Ensure files are specified
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: ./lab8 -I (for interactive mode)" << 
            " or ./lab8 -L [filename] (to load file to database)" << std::endl;
        return 1;
    }

    std::string option = argv[1];
    std::ifstream input(argv[2]);

    if (option.compare("-I") == 0) {
        interactive();
    } else if (option.compare("-L") == 0 && input.good()) {
        std::string path = argv[2];
        loadData(path);
    } else {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }

    // All done
    return 0;
}
