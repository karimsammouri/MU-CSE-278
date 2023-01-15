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
    mysqlpp::Connection database("cse278", "localhost", "cse278", "S3rul3z");

    std::string qString;

    while (getline(std::cin, qString) && qString.compare("quit") != 0) { 
        mysqlpp::Query query = database.query();
        query << qString;

        try {
            query.parse();

            mysqlpp::StoreQueryResult result = query.store();

            std::cout << "-----Query Result-----" << std::endl;
            for (size_t row = 0; (row < result.size()); row++) {
                 std::cout << "|";
                 for (size_t col = 0; (col < result[0].size()); col++) {
                      std::cout << " " << result[row][col] << " |";
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
    std::string query = "INSERT INTO ";

    std::vector<std::string> strVec;
    boost::split(strVec, line, boost::is_any_of(","));

    query += strVec[0] + " (";

    std::vector<std::string> attributes, attributeValues;

    for (int i = 1; i < strVec.size(); i++) {
        attributes.push_back(strVec[i].substr(0, strVec[i].find(":")));
        attributeValues.push_back(strVec[i].substr(strVec[i].find(":") + 1));
    }

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
    std::ifstream input(path);

    mysqlpp::Connection database("cse278", "localhost", "cse278", "S3rul3z");

    std::string line;
    std::string queryStr;
    int lineNum = 0;

    while (getline(input, line)) {
        queryStr = generateLoadQuery(line);

        mysqlpp::Query query = database.query();
        query << queryStr;

        try {
            query.parse();

            mysqlpp::StoreQueryResult result = query.store();
            lineNum++;
            std::cout << "Data Line " << lineNum << " Loaded" << std::endl;
        } catch(mysqlpp::BadQuery e) {
            std::cerr << "Query: " << queryStr<< std::endl;
            std::cerr << "Query is not correct SQL syntax" << std::endl;
        }
    }
}

std::string generateCreateQuery(std::string& line) {
    std::string query = "CREATE TABLE ";

    std::vector<std::string> strVec;
    boost::split(strVec, line, boost::is_any_of(","));

    std::vector<std::string> tableName;
    boost::split(tableName, strVec[0], boost::is_any_of(":"));

    query += tableName[1] + " (";

    std::vector<std::string> attributes, attributeTypes;
    bool key = false;
    std::string keyAttribute;

    for (int i = 1; i < strVec.size(); i++) {
        std::vector<std::string> strVec2;
        boost::split(strVec2, strVec[i], boost::is_any_of(":"));
        if (strVec[i].find("key") != std::string::npos) {
            key = true;
            keyAttribute = strVec2[0];
        }
        attributes.push_back(strVec2[0]);
        attributeTypes.push_back(strVec2[1]);
    }

    for (int i = 0; i < attributes.size(); i++) {
        if (strVec[i + 1].find("not_null") != std::string::npos)
            query += attributes[i] + " " + attributeTypes[i] + " NOT NULL, ";
        else
            query += attributes[i] + " " + attributeTypes[i] + ", ";
    }

    if (key == true) {
        query += "PRIMARY KEY (" + keyAttribute + "));";
    } else {
        query = query.substr(0, query.size() - 2);
        query += ");";
    }

    return query;
}

void createTable(std::string& path) {
    std::ifstream input(path);

    mysqlpp::Connection database("cse278", "localhost", "cse278", "S3rul3z");

    std::string line;
    std::string queryStr;

    while (getline(input, line)) {
        queryStr = generateCreateQuery(line);

        mysqlpp::Query query = database.query();
        query << queryStr;

        try {
            query.parse();

            mysqlpp::StoreQueryResult result = query.store();
            std::cout << "Table " << line.substr(0, line.find(","))
             << " Created" << std::endl;
        } catch (mysqlpp::BadQuery e) {
            std::cerr << "Query: " << queryStr << std::endl;
            std::cerr << "Query is not correct SQL syntax" << std::endl;
        }
    }
}

void dropTable(std::string& tableName) {
    mysqlpp::Connection database("cse278", "localhost", "cse278", "S3rul3z");

    std::string queryStr = "DROP TABLE " + tableName + ";";
    mysqlpp::Query query = database.query();
    query << queryStr;

    try {
        query.parse();

        mysqlpp::StoreQueryResult result = query.store();
        std::cout << "Table " << tableName  << " Dropped" << std::endl;
    } catch (mysqlpp::BadQuery e) {
        std::cerr << "Query: " << queryStr << std::endl;
        std::cerr << "Query is not correct SQL syntax" << std::endl;
    }
}

void filePrint(mysqlpp::StoreQueryResult& result, std::ofstream& output) {
    output << "-----Query Result-----" << std::endl;
    for (size_t row = 0; (row < result.size()); row++) {
        output << "|";
        for (size_t col = 0; (col < result[0].size()); col++) {
            output << " " << result[row][col] << " |";
        }
        output << std::endl;
    }
    output << "------End Result------" << std::endl << std::endl;
}


void writeFile(std::string& inputPath, std::string& outputPath) {
    mysqlpp::Connection database("cse278", "localhost", "cse278", "S3rul3z");
    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    std::string qString;

    while (getline(input, qString) && qString.compare("quit") != 0) { 
        mysqlpp::Query query = database.query();
        query << qString;

        try {
            query.parse();
            mysqlpp::StoreQueryResult result = query.store();

            if (result.size() > 0) {
                filePrint(result, output);
            }
        } catch(mysqlpp::BadQuery e) {
            std::cerr << "Query: " << qString << std::endl << 
            "Query is not correct SQL syntax" << std::endl;
        }
    }
}

int relay(int argc, char *argv[]) {
    std::string option = argv[1];
    std::ifstream input(argv[2]);
    std::ofstream output(argv[3]);

    if (option.compare("-I") == 0 && argc == 2) {
        interactive();
    } else if (option.compare("-L") == 0 && input.good() && argc == 3) {
        std::string path = argv[2];
        loadData(path);
    } else if (option.compare("-C") == 0 && input.good() && argc == 3) {
        std::string path = argv[2];
        createTable(path);
    } else if (option.compare("-D")== 0 && argc == 3) {
        std::string tableName = argv[2];
        dropTable(tableName);
    } else if (option.compare("-W") == 0 && input.good() && output.good() 
    && argc == 4) {
        std::string inputPath = argv[2];
        std::string outputPath = argv[3];
        writeFile(inputPath, outputPath);
    } else {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 4) {
        std::cerr << "Usage: ./lab8 -I (for interactive mode)" << 
        " or ./lab8 -L [fileName] (to load file to database)" << 
        " or ./lab8 -W [inputFile] [outputFile] (to write to a file)" << 
        " or ./lab8 -D [tableName] (to drop a table)" << 
        " or ./lab8 -C [tableName] (to create a table)." << std::endl;
        return 1;
    }

    return relay(argc, argv);
}
