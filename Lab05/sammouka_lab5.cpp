// Copyright 2020 Karim Sammouri

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

// Function to return date
std::string make_daytime_string() {
  char date[26];
  std::time_t now = std::time(0);
  return ctime_r(&now, date);
}

int checkPort(std::string port) {
  int portNum;

  try {
    // Try to convert convert the input
    portNum = stoi(port);
  }
  catch (std::exception& e) {
    // Provide some error message and return 0
    cerr << "Must supply port number" << endl;
    return 0;
  }

  if (portNum < 1 || portNum > 65535) {
    cerr << "Must supply port number" << endl;
    return 0;
  }

  return portNum;
}


int main(int argc, char *argv[]) {
    // Check user inputs for port number
    if (argc != 2) {
        cerr << "Must supply port number" << endl;
        return 0;
    }

    // Validate input is numeric
    int port = checkPort(argv[1]);
    if (port == 0) {
        return 0;
    }

    // Check  port number is valid
    if (port >= 1 && port <= 1023) {
        cerr << "Cannot use privileged ports" << endl;
        return 0;
    }

    // Create the endpoint for the server
    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

    // Create the socket (and any other necessary objects)
    tcp::socket socket(io_service);

    // Wait and listen for a client to connect
    acceptor.accept(socket);

    // Prepare message to send back to client
    std::string  dateAndTime = make_daytime_string();

    boost::system::error_code ignored_error;
    // Write the message for current time to the socket
    write(socket, boost::asio::buffer(dateAndTime), ignored_error);
    return 0;
}

