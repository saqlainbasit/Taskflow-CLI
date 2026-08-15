# TaskFlow CLI

A fast, color-coded command-line task manager built in **C++17**.

## Features
- Add, Edit, Delete tasks
- Priority levels — High / Medium / Low
- Mark tasks as complete
- Color-coded terminal output
- Works on Windows, Linux & macOS

## Build & Run

```bash
make
./taskflow        # Linux / macOS
Taskflow-CLI.exe  # Windows
```

## Project Structure

```
Taskflow-CLI/
├── Makefile
└── src/
    ├── main.cpp         — Menu loop & UI
    ├── Task.h           — Task struct & enums
    ├── TaskManager.h    — Class declaration
    ├── TaskManager.cpp  — Core logic
    └── Display.h        — Colors & formatting
```

## Requirements
- g++ with C++17 support
- make

