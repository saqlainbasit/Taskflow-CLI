#include <iostream>
#include <limits>
#include <string>
#include "TaskManager.h"
#include "Display.h"

// Enable ANSI colors on Windows 10+
#ifdef _WIN32
  #include <windows.h>
  void enableAnsi() {
      HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
      DWORD mode = 0;
      GetConsoleMode(hOut, &mode);
      SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
      SetConsoleOutputCP(CP_UTF8);
  }
#else
  void enableAnsi() {}
#endif

// ── Input helpers ─────────────────────────────────────────────────────────────

static int getInt(const std::string& prompt) {
    int val;
    while (true) {
        std::cout << Color::BYELLOW << "  >> " << prompt << Color::RESET;
        if (std::cin >> val) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return val;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printError("Please enter a valid number.");
    }
}

static std::string getString(const std::string& prompt) {
    std::string val;
    std::cout << Color::BYELLOW << "  >> " << prompt << Color::RESET;
    std::getline(std::cin, val);
    return val;
}

static Priority getPriority() {
    while (true) {
        std::cout << Color::BYELLOW << "  >> Priority  [1] High  [2] Medium  [3] Low : " << Color::RESET;
        int c;
        if (std::cin >> c) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (c == 1) return Priority::HIGH;
            if (c == 2) return Priority::MEDIUM;
            if (c == 3) return Priority::LOW;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        printError("Enter 1, 2, or 3.");
    }
}

// ── Screens ───────────────────────────────────────────────────────────────────

static void splash() {
    std::cout << "\n";
    std::cout << Color::BOLD << Color::BRED;
    std::cout << "   _____  _    ____  _  _______ _     _____        __ \n";
    std::cout << "  |_   _|/ \\  / ___|| |/ /  ___| |   / _ \\ \\      / / \n";
    std::cout << "    | | / _ \\ \\___ \\| ' /| |_  | |  | | | \\ \\ /\\ / /  \n";
    std::cout << "    | |/ ___ \\ ___) | . \\|  _| | |__| |_| |\\ V  V /   \n";
    std::cout << "    |_/_/   \\_\\____/|_|\\_\\_|   |_____\\___/  \\_/\\_/    \n";
    std::cout << Color::RESET;
    std::cout << Color::DIM;
    std::cout << "  ----------------------------------------------------------\n";
    std::cout << "               CLI Task Manager  --  v1.0                  \n";
    std::cout << "  ----------------------------------------------------------\n";
    std::cout << Color::RESET << "\n";
}

static void showMenu() {
    std::cout << "\n";
    printDivider("─", 40);
    std::cout << Color::BOLD << Color::BWHITE << "  MAIN MENU\n" << Color::RESET;
    printDivider("─", 40);
    std::cout << Color::CYAN   << "  [1]" << Color::RESET << "  View all tasks\n";
    std::cout << Color::CYAN   << "  [2]" << Color::RESET << "  Filter by priority\n";
    std::cout << Color::BGREEN << "  [3]" << Color::RESET << "  Add task\n";
    std::cout << Color::YELLOW << "  [4]" << Color::RESET << "  Edit task\n";
    std::cout << Color::BGREEN << "  [5]" << Color::RESET << "  Mark task as complete\n";
    std::cout << Color::BRED   << "  [6]" << Color::RESET << "  Delete task\n";
    std::cout << Color::DIM    << "  [0]" << Color::RESET << "  Exit\n";
    printDivider("─", 40);
}

// ── Actions ───────────────────────────────────────────────────────────────────

static void doAdd(TaskManager& mgr) {
    printHeader("ADD TASK");
    std::string title = getString("Title       : ");
    if (title.empty()) { printError("Title cannot be empty."); return; }
    std::string desc  = getString("Description : ");
    Priority    p     = getPriority();
    mgr.addTask(title, desc, p);
    printSuccess("Task added successfully!");
}

static void doEdit(TaskManager& mgr) {
    printHeader("EDIT TASK");
    mgr.listAll();
    if (mgr.isEmpty()) return;
    int id = getInt("Enter Task ID to edit : ");
    std::string title = getString("New title       : ");
    if (title.empty()) { printError("Title cannot be empty."); return; }
    std::string desc  = getString("New description : ");
    Priority    p     = getPriority();
    if (mgr.editTask(id, title, desc, p))
        printSuccess("Task updated.");
    else
        printError("Task ID not found.");
}

static void doComplete(TaskManager& mgr) {
    printHeader("COMPLETE TASK");
    mgr.listAll();
    if (mgr.isEmpty()) return;
    int id = getInt("Enter Task ID to mark complete : ");
    if (mgr.completeTask(id))
        printSuccess("Task marked as completed!");
    else
        printError("Task ID not found.");
}

static void doDelete(TaskManager& mgr) {
    printHeader("DELETE TASK");
    mgr.listAll();
    if (mgr.isEmpty()) return;
    int id = getInt("Enter Task ID to delete : ");
    std::cout << Color::BRED << "  Are you sure? [y/N] : " << Color::RESET;
    char confirm; std::cin >> confirm;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (confirm != 'y' && confirm != 'Y') { printInfo("Cancelled."); return; }
    if (mgr.deleteTask(id))
        printSuccess("Task deleted.");
    else
        printError("Task ID not found.");
}

static void doFilter(TaskManager& mgr) {
    printHeader("FILTER BY PRIORITY");
    std::cout << Color::CYAN   << "  [1]" << Color::RESET << Color::BRED    << "  High\n"   << Color::RESET;
    std::cout << Color::CYAN   << "  [2]" << Color::RESET << Color::BYELLOW << "  Medium\n" << Color::RESET;
    std::cout << Color::CYAN   << "  [3]" << Color::RESET << Color::BGREEN  << "  Low\n"    << Color::RESET;
    int c = getInt("Choose filter : ");
    Priority p;
    if      (c == 1) p = Priority::HIGH;
    else if (c == 2) p = Priority::MEDIUM;
    else if (c == 3) p = Priority::LOW;
    else { printError("Invalid choice."); return; }
    printDivider("─");
    mgr.listTasks(p, true);
}

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    enableAnsi();
    TaskManager mgr;
    splash();

    while (true) {
        showMenu();
        int choice = getInt("Choose an option : ");

        switch (choice) {
            case 1:
                printHeader("ALL TASKS");
                mgr.listAll();
                break;
            case 2: doFilter(mgr);   break;
            case 3: doAdd(mgr);      break;
            case 4: doEdit(mgr);     break;
            case 5: doComplete(mgr); break;
            case 6: doDelete(mgr);   break;
            case 0:
                std::cout << "\n" << Color::BCYAN
                          << "  Goodbye! Stay productive.\n\n"
                          << Color::RESET;
                return 0;
            default:
                printError("Invalid option. Try again.");
        }
    }
}