#include <iostream>
#include <iomanip>
#include <algorithm>
#include "TaskManager.h"
#include "Display.h"

// -- Private helpers ----------------------------------------------------------

Task* TaskManager::findById(int id) {
    for (auto& t : tasks)
        if (t.id == id) return &t;
    return nullptr;
}

void TaskManager::printTask(const Task& t, int /*index*/) const {
    std::cout << Color::BOLD << Color::BWHITE
              << "  [" << std::setw(2) << t.id << "] "
              << Color::RESET
              << Color::WHITE << t.title << Color::RESET << "\n";

    if (!t.description.empty())
        std::cout << Color::DIM << "       " << t.description << Color::RESET << "\n";

    std::cout << "       "
              << colorPriority(t.priority)
              << "   " << colorStatus(t.status) << "\n";

    printDivider("-", 60);
}

// -- Public methods -----------------------------------------------------------

void TaskManager::addTask(const std::string& title, const std::string& desc, Priority p) {
    tasks.emplace_back(nextId++, title, desc, p);
}

bool TaskManager::editTask(int id, const std::string& title, const std::string& desc, Priority p) {
    Task* t = findById(id);
    if (!t) return false;
    t->title       = title;
    t->description = desc;
    t->priority    = p;
    return true;
}

bool TaskManager::deleteTask(int id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                             [id](const Task& t){ return t.id == id; });
    if (it == tasks.end()) return false;
    tasks.erase(it, tasks.end());
    return true;
}

bool TaskManager::completeTask(int id) {
    Task* t = findById(id);
    if (!t) return false;
    t->status = Status::COMPLETED;
    return true;
}

void TaskManager::listAll() const {
    if (tasks.empty()) {
        printInfo("No tasks yet. Add one!");
        return;
    }
    int i = 1;
    for (const auto& t : tasks)
        printTask(t, i++);
}

void TaskManager::listTasks(Priority filter, bool filterOn) const {
    if (tasks.empty()) {
        printInfo("No tasks yet. Add one!");
        return;
    }
    bool any = false;
    int i = 1;
    for (const auto& t : tasks) {
        if (!filterOn || t.priority == filter) {
            printTask(t, i++);
            any = true;
        }
    }
    if (!any) printInfo("No tasks match that filter.");
}