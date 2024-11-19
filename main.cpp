#include <iostream>
#include <vector>
#include "tasks.h"
#include "file.h"

void displayMenu();
void viewTasks(const std::vector<Task>& tasks);
void addTask(std::vector<Task>& tasks, FileManager& fileManager);
void markTaskCompleted(std::vector<Task>& tasks, FileManager& fileManager);
void removeTask(std::vector<Task>& tasks, FileManager& fileManager);

int main() {
    FileManager fileManager("tasks.txt");
    std::vector<Task> tasks;

    // Load tasks from the file
    fileManager.loadTasks(tasks);

    int choice;
    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Ignore leftover newline character in the input buffer

        switch (choice) {
        case 1:
            viewTasks(tasks);
            break;
        case 2:
            addTask(tasks, fileManager);
            break;
        case 3:
            markTaskCompleted(tasks, fileManager);
            break;
        case 4:
            removeTask(tasks, fileManager);
            break;
        case 5:
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    std::cout << "\n=== To-Do List Manager ===" << std::endl;
    std::cout << "1. View Tasks" << std::endl;
    std::cout << "2. Add Task" << std::endl;
    std::cout << "3. Mark Task as Completed" << std::endl;
    std::cout << "4. Remove Task" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "==========================" << std::endl;
}

void viewTasks(const std::vector<Task>& tasks) {
    if (tasks.empty()) {
        std::cout << "\nNo tasks in your to-do list." << std::endl;
    }
    else {
        std::cout << "\nYour Tasks:" << std::endl;
        for (const auto& task : tasks) {
            std::cout << task.id << ". " << task.description
                << " [" << (task.isCompleted ? "Completed" : "Pending") << "]" << std::endl;
        }
    }
}

void addTask(std::vector<Task>& tasks, FileManager& fileManager) {
    std::string description;
    std::cout << "\nEnter a new task: ";
    std::getline(std::cin, description);

    if (!description.empty()) {
        int id = tasks.empty() ? 1 : tasks.back().id + 1;
        tasks.emplace_back(id, description);
        fileManager.saveTasks(tasks);
        std::cout << "Task added successfully!" << std::endl;
    }
    else {
        std::cout << "Task description cannot be empty!" << std::endl;
    }
}

void markTaskCompleted(std::vector<Task>& tasks, FileManager& fileManager) {
    if (tasks.empty()) {
        std::cout << "\nNo tasks to mark as completed." << std::endl;
        return;
    }

    viewTasks(tasks);
    std::cout << "\nEnter the task ID to mark as completed: ";
    int taskID;
    std::cin >> taskID;

    for (auto& task : tasks) {
        if (task.id == taskID) {
            if (!task.isCompleted) {
                task.isCompleted = true;
                fileManager.saveTasks(tasks);
                std::cout << "Task marked as completed!" << std::endl;
            }
            else {
                std::cout << "Task is already completed." << std::endl;
            }
            return;
        }
    }
    std::cout << "Task with ID " << taskID << " not found." << std::endl;
}

void removeTask(std::vector<Task>& tasks, FileManager& fileManager) {
    if (tasks.empty()) {
        std::cout << "\nNo tasks to remove." << std::endl;
        return;
    }

    viewTasks(tasks);
    std::cout << "\nEnter the task ID to remove: ";
    int taskID;
    std::cin >> taskID;

    auto it = std::remove_if(tasks.begin(), tasks.end(),
        [taskID](const Task& task) { return task.id == taskID; });

    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        fileManager.saveTasks(tasks);
        std::cout << "Task removed successfully!" << std::endl;
    }
    else {
        std::cout << "Task with ID " << taskID << " not found." << std::endl;
    }
}
