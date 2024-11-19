#pragma once
#include <vector>
#include "tasks.h"

class FileManager {
private:
    std::string filename;

public:
    FileManager(const std::string& filename);

    void loadTasks(std::vector<Task>& tasks);
    void saveTasks(const std::vector<Task>& tasks);
};
