#include "file.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
FileManager::FileManager(const std::string& filename)
    : filename(filename) {
}

// Load tasks from the file into the vector
void FileManager::loadTasks(std::vector<Task>& tasks) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        tasks.push_back(Task::fromString(line));
    }

    file.close();
}

// Save the vector of tasks to the file
void FileManager::saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file(filename, std::ios::trunc);
    if (!file) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    for (const auto& task : tasks) {
        file << task.toString() << std::endl;
    }

    file.close();
}
