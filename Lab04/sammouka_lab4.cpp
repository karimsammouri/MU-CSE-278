// Copyright 2020 Alan M. Ferrenberg & Karim Sammouri
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

void createWeekMap(unordered_map<string, int>& weekMap) {
  // Create an unordered map of the days of the week to integers
  // Sunday should be one, etc.  Make sure to capitalize the names of the
  // days.
  weekMap = {{"Sunday", 1}, {"Monday", 2}, {"Tuesday", 3}, 
  {"Wednesday", 4}, {"Thursday", 5}, {"Friday", 6}, {"Saturday", 7}};
}

void createMonthMap(unordered_map<string, int>& monthMap) {
  // Create an unordered map of the months of the year to integers
  // January should be one, etc.  Make sure to capitalize the names of the
  // Months.
  monthMap  = {{"January", 1}, {"February", 2}, {"March", 3}, 
  {"April", 4}, {"May", 5}, {"June", 6}, {"July", 7}, {"August", 8}, 
  {"September", 9}, {"October", 10}, {"November", 11}, {"December", 12}};
}

bool dayValid(unordered_map<string, int>& weekMap, string day) {
  if (weekMap.find(day) == weekMap.end()) {
    return false;
  }
  return true;
}

bool monthValid(unordered_map<string, int>& monthMap, string month) {
  if (monthMap.find(month) == monthMap.end()) {
    return false;
  }
  return true;
}

int main() {
  // Create an appropriate unordered_map that will map a std::string to
  // an int
  using StrIntMap = unordered_map<string, int>;
  
  // Declare instances of the map called weekMap and monthMap
  StrIntMap weekMap, monthMap;
  
  // Invoke the function that will populate your week map
  createWeekMap(weekMap);
  
  // Invoke the function that will populate your week map  
  createMonthMap(monthMap);

  // Prompt the user for a month and day of the week continuously
  // (i.e. in a loop) until both of them are valid keys.  That is, the
  // user enters a valid month and day of the week.  You should use
  // an appropriate method acting on your week and month map instances
  // to determine whether their input is valid or not.
  bool dayInputValid, monthInputValid;
  string input, monthKey, dayKey;
  do {
    cout << "Enter a month and weekday: ";
    getline(cin, input);
    monthKey = input.substr(0, input.find(" "));
    dayKey = input.substr(input.find(' ') + 1);
    dayInputValid = dayValid(weekMap, dayKey); 
    monthInputValid = monthValid(monthMap, monthKey);
  
  // If the user enters an incorrect month, inform them with a message to
  // standard error with this format:
  //    "The month " << monthTheyEntered << " is not valid\n";
    if (!monthInputValid) {
      cerr << "The month " << monthKey << " is not valid\n";
      continue;
    }
  // If the user enters an incorrect day of the week, inform them with a
  // message to standard error with this format:
  //    "The day " << dayTheyEntered << " is not valid\n";    
    if (!dayInputValid) {
      cerr << "The day " << dayKey << " is not valid\n";
    }
  } while (!dayInputValid || !monthInputValid);

  // Once both the month and day are valid, write the mapping of their
  // month and day to the appropriate integer value.  The output should
  // look like this (without the quotes): "March, Tuesday => 3, 3"
  cout << monthKey << ", " << dayKey << " => " << monthMap[monthKey] 
  << ", " << weekMap[dayKey] << std::endl;

  return 0;
}
