// Copyright 2020 Karim Sammouri
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

std::string letterGrade(double score) {
  if (score > 97) {
    return "(A+)";
  } else if (score > 93) {
    return "(A)";
  } else if (score > 90) {
    return "(A-)";
  } else if (score > 87) {
    return "(B+)";
  } else if (score > 83) {
    return "(B)";
  } else if (score > 80) {
    return "(B-)";
  } else if (score > 77) {
    return "(C+)";
  } else if (score > 73) {
    return "(C)";
  } else if (score > 70) {
    return "(C-)";
  } else if (score > 67) {
    return "(D+)";
  } else if (score > 63) {
    return "(D)";
  } else if (score > 60) {
    return "(D-)";
  } else {
    return "(F)";
  }
}

void printResult(std::ostream& out, double final, 
double homework, double lab, double midterm, double quiz, double courseGrade) {
  out << "final_exam: " << final << "%" << " " << 
letterGrade(final) << std::endl;
  out << "homework: " << homework << "%" << " " << 
letterGrade(homework) << std::endl;
  out << "lab: " << lab << "%" << " " <<
letterGrade(lab) << std::endl;
  out << "midterm: " << midterm << "%" << " " <<
letterGrade(midterm) << std::endl;
  out << "quiz: " << quiz << "%" << " " <<
letterGrade(quiz) << std::endl;
  out << "Course Grade: " << courseGrade << "%" << " " <<
letterGrade(courseGrade) << std::endl;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: ./homework2 [inputfile] [outputfile]";
    return 1;
  }

  ifstream inputFile(argv[1]);
  ofstream outputFile(argv[2]);

  if (!inputFile.good() || !outputFile.good()) {
    std::cerr << "Can't open input or output files.";
    return 2;
  }

  using StrStrMap = unordered_map<string, string>;
  StrStrMap earnedScoreMap;
  string line;
  vector<string> strVec;
  while (getline(inputFile, line)) {
    boost::split(strVec, line, boost::is_any_of(","));
    earnedScoreMap.insert({strVec[0], strVec[1]});
  }

  double final = 0, homework = 0, lab = 0, midterm = 0, 
quiz = 0, courseGrade = 0;

  for (const auto & entry : earnedScoreMap) {
    if (entry.first.compare("final_exam") == 0) {
      final += stod(entry.second) / 100;
    }
    if (entry.first.compare("midterm") == 0) {
      midterm += stod(entry.second) / 100;
    }
    if (entry.first.compare("homework") == 0) {
      homework += stod(entry.second) / 35;
    }
    if (entry.first.compare("lab") == 0) {
      lab += stod(entry.second) / 40;
    }
    if (entry.first.compare("quiz") == 0) {
      quiz += stod(entry.second) / 100;
    }
  }

  final *= 100;
  homework *= 100;
  lab *= 100;
  midterm *= 100;
  quiz *= 100;
  courseGrade = (final * 0.25) + (homework * 0.35) + (lab * 0.1) +
(midterm * 0.2) + (quiz * 0.1);
  
  printResult(outputFile, final, homework, lab, midterm, quiz,
courseGrade);
  printResult(std::cout, final, homework, lab, midterm, quiz,
courseGrade);
  return 0;
}
