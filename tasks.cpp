#include "tasks.h"
#include <sstream>

// Constructor
Task::Task(int id, const std::string& description, bool isCompleted)
    : id(id), description(description), isCompleted(isCompleted) {
}

// Convert a Task to a string for saving to a file
std::string Task::toString() const {
    return std::to_string(id) + "|" + description + "|" + (isCompleted ? "1" : "0");
}

// Convert a string from the file into a Task object
Task Task::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string token;
    int id;
    std::string description;
    bool isCompleted;

    std::getline(iss, token, '|');
    id = std::stoi(token);

    std::getline(iss, description, '|');
    std::getline(iss, token, '|');
    isCompleted = (token == "1");

    return Task(id, description, isCompleted);
}
