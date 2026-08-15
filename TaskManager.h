#pragma once
#include <vector>
#include <optional>
#include "Task.h"

class TaskManager {
public:
    void addTask(const std::string& title, const std::string& desc, Priority p);
    bool editTask(int id, const std::string& title, const std::string& desc, Priority p);
    bool deleteTask(int id);
    bool completeTask(int id);
    void listTasks(Priority filter, bool filterOn) const;
    void listAll() const;
    bool isEmpty() const { return tasks.empty(); }

private:
    std::vector<Task> tasks;
    int nextId = 1;

    Task* findById(int id);
    void  printTask(const Task& t, int index) const;
};