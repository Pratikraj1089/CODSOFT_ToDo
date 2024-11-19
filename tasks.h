#pragma once
#pragma once
#include <string>

class Task {
public:
    int id;
    std::string description;
    bool isCompleted;

    Task(int id, const std::string& description, bool isCompleted = false);

    std::string toString() const;
    static Task fromString(const std::string& line);
};


