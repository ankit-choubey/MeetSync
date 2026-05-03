# MeetSync

### **Smart. Greedy. Reliable.**
*A high-performance, lightweight C++ meeting scheduler utilizing optimal activity selection logic.*

![C++](https://img.shields.io/badge/Language-C%2B%2B17-blue)
![Interface](https://img.shields.io/badge/Interface-CLI-lightgrey)
![License](https://img.shields.io/badge/License-MIT-green)
![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey)

---

## 🎯 Mission Brief
**[MeetSync](https://github.com/ankit-choubey/MeetSync)** is a precision-engineered command-line utility designed to maximize productivity by resolving scheduling conflicts. Built with a focus on algorithmic efficiency, it provides a deterministic way to manage time blocks, ensuring you get the most out of your day without the overhead of complex enterprise software.

---

## 🧠 Core Logic & Strategy
MeetSync implements the **Greedy Activity Selection** algorithm, a proven mathematical approach to the Interval Scheduling Problem. 

### **How It Works**
1.  **Ingestion:** The system loads or accepts manual entry of meetings with defined `HH:MM` start and end times.
2.  **Sorting:** Meetings are sorted based on their **earliest end time**.
3.  **Selection:** The scheduler iterates through the sorted list, picking a meeting only if its start time is greater than or equal to the end time of the previously scheduled meeting.
4.  **Conflict Resolution:** Any overlapping slots are automatically identified and rejected to maintain a clean, conflict-free timeline.

### **The Efficiency Factor**
* **Optimal Throughput:** Selecting the earliest-ending meetings leaves the maximum possible remaining time for subsequent activities.
* **Mathematical Proof:** This greedy strategy is guaranteed to provide the maximum number of non-overlapping activities for a single resource.
* **Complexity:** The algorithm operates at $O(n \log n)$ due to the initial sorting requirement, while the selection process remains $O(n)$.

---

## 🛠 Key Features
* **Dynamic Entry:** Add custom meetings on the fly with built-in time validation.
* **Sample Data Injection:** One-click loading of pre-defined datasets for rapid testing and demonstrations.
* **Conflict Awareness:** Detailed reporting on why a specific meeting was rejected.
* **Lightweight Footprint:** Zero dependencies beyond the C++ Standard Library, ensuring portability across macOS, Linux, and Windows.

---

## 🚀 Technical Implementation

### **Safety Protocols**
* **Temporal Validation:** Rejects any meeting where the `End Time <= Start Time`.
* **Integrity Checks:** Prevents duplicate entries and handles empty states gracefully.
* **Input Sanitization:** Ensures time formats remain consistent within the CLI environment to prevent runtime errors.

### **Build & Execution**
Ensure you have a C++17 compliant compiler (such as `g++` or `clang`).

**1. Compilation**
```bash
g++ -std=c++17 main.cpp -O2 -Wall -Wextra -o meetsync
```

**2. Execution**
```bash
./meetsync
```

---

## 📋 Sample Workflow
1.  **Initialize:** Select `1` to populate the scheduler with sample data.
2.  **Verify:** Select `3` to view the current raw list of all meetings.
3.  **Optimize:** Select `4` to trigger the greedy scheduler and view the finalized, optimized agenda.
4.  **Exit:** Select `5` to terminate the session safely.

---

## 👥 Project Team
* **Ankit Choubey** (Lead Developer)
* **Vaibhav D**
* **Srujan Kasturi**
* **Ritin Nambiar**
* **Dhanush Dronagula**

---

## 📜 License & Notes
* **License:** Distributed under the [MIT License](https://github.com/ankit-choubey/MeetSync/blob/main/LICENSE).
* **Architecture:** The project is intentionally self-contained within `main.cpp` for maximum portability and ease of maintenance.

*Built for performance. Optimized for impact.*
