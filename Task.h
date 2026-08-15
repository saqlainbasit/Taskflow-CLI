#pragma once
#include <string>

enum class Priority { LOW, MEDIUM, HIGH };
enum class Status   { PENDING, COMPLETED };

struct Task {
    int      id;
    std::string title;
    std::string description;
    Priority priority;
    Status   status;

    Task(int id, const std::string& title, const std::string& desc, Priority p)
        : id(id), title(title), description(desc), priority(p), status(Status::PENDING) {}

    std::string priorityStr() const {
        switch (priority) {
            case Priority::HIGH:   return "HIGH";
            case Priority::MEDIUM: return "MEDIUM";
            case Priority::LOW:    return "LOW";
        }
        return "";
    }

    std::string statusStr() const {
        return status == Status::COMPLETED ? "COMPLETED" : "PENDING";
    }
};