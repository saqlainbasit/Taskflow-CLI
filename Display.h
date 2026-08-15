#pragma once
#include <string>
#include "Task.h"

// ANSI color codes
namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string DIM     = "\033[2m";

    // Text colors
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";

    // Bright variants
    const std::string BRED    = "\033[91m";
    const std::string BGREEN  = "\033[92m";
    const std::string BYELLOW = "\033[93m";
    const std::string BCYAN   = "\033[96m";
    const std::string BWHITE  = "\033[97m";
}

inline std::string colorPriority(Priority p) {
    switch (p) {
        case Priority::HIGH:   return Color::BRED    + "[HIGH]"   + Color::RESET;
        case Priority::MEDIUM: return Color::BYELLOW + "[MEDIUM]" + Color::RESET;
        case Priority::LOW:    return Color::BGREEN  + "[LOW]"    + Color::RESET;
    }
    return "";
}

inline std::string colorStatus(Status s) {
    if (s == Status::COMPLETED)
        return Color::BGREEN + "[DONE]" + Color::RESET;
    return Color::CYAN + "[PENDING]" + Color::RESET;
}

inline void printDivider(const std::string& c = "-", int width = 60) {
    std::cout << Color::DIM;
    for (int i = 0; i < width; i++) std::cout << c;
    std::cout << Color::RESET << "\n";
}

inline void printHeader(const std::string& title) {
    std::cout << "\n";
    printDivider("=");
    std::cout << Color::BOLD << Color::BCYAN
              << "  " << title << "\n"
              << Color::RESET;
    printDivider("=");
}

inline void printSuccess(const std::string& msg) {
    std::cout << Color::BGREEN << "  [OK] " << msg << Color::RESET << "\n";
}

inline void printError(const std::string& msg) {
    std::cout << Color::BRED << "  [ERR] " << msg << Color::RESET << "\n";
}

inline void printInfo(const std::string& msg) {
    std::cout << Color::BCYAN << "  [i] " << msg << Color::RESET << "\n";
}