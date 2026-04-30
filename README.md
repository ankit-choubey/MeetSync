<div align="center">

# MeetSync
### **Smart. Greedy. Reliable.**
*A lightweight C++ meeting scheduler built around classic activity selection.*

[![C++](https://img.shields.io/badge/Language-C++17-00599C?style=for-the-badge&logo=c%2B%2B)](https://en.cppreference.com/w/cpp/17)
[![CLI](https://img.shields.io/badge/Interface-CLI-111827?style=for-the-badge)](https://en.wikipedia.org/wiki/Command-line_interface)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-macOS_%7C_Linux_%7C_Windows-lightgrey?style=for-the-badge)](https://github.com/ankit-choubey/MeetSync)

</div>

---

## Mission Brief

**MeetSync** is a compact meeting planner that helps you load, view, and schedule time blocks using a proven **greedy activity selection** approach.

The focus is clarity over complexity: keep the interface simple, keep the logic deterministic, and keep the schedule conflict-free.

---

## Core Logic

MeetSync follows the standard greedy strategy for interval scheduling.

### How It Works

1. Load or add meetings with a start and end time.
2. Sort meetings by earliest end time.
3. Pick each meeting only if it does not overlap the last scheduled one.
4. Reject overlapping meetings and show the conflict.

### Why This Works

- Earliest-ending meetings leave the most room for later meetings.
- The result maximizes the number of meetings that can fit in a day.
- The logic is easy to verify and easy to maintain.

---

## Key Features

### Scheduler Workflow

- Load sample data for a quick demo.
- Add custom meetings with `HH:MM` start and end times.
- View all saved meetings in a clean list.
- Run the greedy scheduler and inspect accepted versus rejected slots.

### Safety Checks

- Reject meetings whose end time is not after the start time.
- Prevent duplicate time-slot entries.
- Handle empty schedules gracefully.

---

## Quickstart

### Build

```bash
g++ -std=c++17 main.cpp -O2 -Wall -Wextra -o meetsync
```

### Run

```bash
./meetsync
```

### Sample Flow

1. Choose `1` to load sample meetings.
2. Choose `4` to run the greedy scheduler.
3. Choose `5` to exit.

---

## Project Team

- Vaibhav D
- Srujan Kasturi
- Ritin Nambiar
- Ankit Choubey (Me)
- Dhanush Dronagula

---

## Notes

- The project is intentionally small and self-contained.
- Only the core files are kept in the repository.
- The scheduler output is designed to be readable in a terminal.

---

<div align="center">

*Built for practical scheduling, clean logic, and easy maintenance.*

</div>
