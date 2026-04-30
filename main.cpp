/*
 ╔═══════════════════════════════════════════════╗
 ║      MeetSync — Smart Meeting Scheduler       ║
 ║      Algorithm : Greedy (Activity Selection)  ║
 ║      Language  : C++                          ║
 ╚═══════════════════════════════════════════════╝

 HOW GREEDY WORKS HERE:
   1. Sort all meetings by their END time (earliest ending first)
   2. Go through each meeting one by one
   3. If it doesn't overlap with the last picked meeting → pick it
   4. If it overlaps → reject it
   WHY IS THIS OPTIMAL?
   Picking the earliest-ending meeting always leaves maximum
   room for future meetings. This is the Greedy Choice Property.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <cstdio>
#include <cstdlib>
using namespace std;

// ─────────────────────────────────────────
//  Data Structure
// ─────────────────────────────────────────
struct Meeting {
    int    id;
    string name;
    int    start;   // stored in minutes (e.g. 09:30 → 570)
    int    end;
};

vector<Meeting> meetings;
int nextId = 1;

// ─────────────────────────────────────────
//  Time Helpers
// ─────────────────────────────────────────

// "09:30"  →  570  (minutes from midnight)
int toMin(const string &t) {
    return stoi(t.substr(0, 2)) * 60 + stoi(t.substr(3, 2));
}

// 570  →  "09:30"
string toTime(int m) {
    char buf[6];
    snprintf(buf, sizeof(buf), "%02d:%02d", m / 60, m % 60);
    return buf;
}

// ─────────────────────────────────────────
//  Print helpers
// ─────────────────────────────────────────
void printLine() {
    cout << string(52, '=') << "\n";
}

// ─────────────────────────────────────────
//  Option 1 — Load Sample Data
// ─────────────────────────────────────────
void loadSample() {
    meetings.clear();   // reset so calling twice doesn't duplicate
    nextId = 1;

    meetings = {
        {nextId++, "Team Standup",    toMin("09:00"), toMin("10:00")},
        {nextId++, "Design Sync",     toMin("09:30"), toMin("11:00")},
        {nextId++, "Client Review",   toMin("10:30"), toMin("11:30")},
        {nextId++, "Lunch Meeting",   toMin("10:00"), toMin("12:00")},
        {nextId++, "Sprint Planning", toMin("12:00"), toMin("13:00")},
        {nextId++, "Team Retro",      toMin("13:00"), toMin("14:00")},
    };
    cout << "  ✅ Sample data loaded (6 meetings).\n";
}

// ─────────────────────────────────────────
//  Option 2 — Add a Meeting
// ─────────────────────────────────────────
void addMeeting() {
    Meeting m;
    string s, e;

    // flush leftover newline from previous cin >> so getline works
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "  Meeting name  : "; getline(cin, m.name);
    cout << "  Start (HH:MM) : "; cin >> s;
    cout << "  End   (HH:MM) : "; cin >> e;

    m.start = toMin(s);
    m.end   = toMin(e);

    if (m.end <= m.start) {
        cout << "  ⚠  End time must be after start time!\n";
        return;
    }

    // warn if exact same time slot already exists
    for (auto &x : meetings) {
        if (x.start == m.start && x.end == m.end) {
            cout << "  ⚠  A meeting with the same time slot already exists!\n";
            return;
        }
    }

    m.id = nextId++;
    meetings.push_back(m);
    cout << "  ✅ Meeting \"" << m.name << "\" added!\n";
}

// ─────────────────────────────────────────
//  Option 3 — View All Meetings
// ─────────────────────────────────────────
void viewMeetings() {
    if (meetings.empty()) {
        cout << "  No meetings added yet.\n";
        return;
    }
    printLine();
    cout << "  ID    NAME                    TIME\n";
    printLine();
    for (auto &m : meetings) {
        cout << "  [" << setw(2) << m.id << "]  "
             << left << setw(24) << m.name
             << toTime(m.start) << " - " << toTime(m.end) << "\n";
    }
    printLine();
    cout << "  Total: " << meetings.size() << " meeting(s)\n";
    printLine();
}

// ─────────────────────────────────────────
//  Option 4 — Run Greedy Scheduler
// ─────────────────────────────────────────
void runScheduler() {
    if (meetings.empty()) {
        cout << "  No meetings to schedule. Add some first!\n";
        return;
    }

    // ── GREEDY STEP 1: Sort by end time ───────────
    cout << "\n  [Greedy] Step 1: Sorting " << meetings.size()
         << " meetings by end time...\n";
    vector<Meeting> sorted = meetings;
    sort(sorted.begin(), sorted.end(), [](const Meeting &a, const Meeting &b) {
        return a.end < b.end;   // earliest ending first
    });

    // ── GREEDY STEP 2: Pick non-overlapping meetings ──
    cout << "  [Greedy] Step 2: Picking meetings greedily...\n\n";

    vector<Meeting> scheduled, rejected;
    int lastEnd = -1;   // end time of last scheduled meeting

    for (auto &m : sorted) {
        if (m.start >= lastEnd) {
            // no overlap → schedule it
            scheduled.push_back(m);
            lastEnd = m.end;
        } else {
            // overlaps with last picked → reject
            rejected.push_back(m);
        }
    }

    // ── Find which scheduled meeting each rejected one conflicts with ──
    auto findConflict = [&](const Meeting &r) -> string {
        for (auto &s : scheduled)
            if (r.start < s.end && r.end > s.start)
                return s.name;
        return "another meeting";
    };

    // ── OUTPUT ────────────────────────────────────────
    cout << "\n";
    printLine();
    cout << "  MEETSYNC — MEETING SCHEDULER RESULT\n";
    printLine();
    cout << "  Total Meetings Requested : " << meetings.size() << "\n\n";

    cout << "  ✅ SCHEDULED:\n";
    for (const auto &m : scheduled) {
        cout << "    [" << setw(2) << m.id << "] "
             << left << setw(22) << m.name
             << "| " << toTime(m.start) << " - " << toTime(m.end) << "\n";
    }

    if (!rejected.empty()) {
        cout << "\n  ❌ REJECTED (Conflicts):\n";
        for (const auto &m : rejected) {
            cout << "    [" << setw(2) << m.id << "] "
                 << left << setw(22) << m.name
                 << "| " << toTime(m.start) << " - " << toTime(m.end)
                 << "  <- overlaps with \"" << findConflict(m) << "\"\n";
        }
    }

    printLine();
    cout << "  Max meetings in a day : " << scheduled.size() << "\n";
    printLine();
}

// ─────────────────────────────────────────
//  Main
// ─────────────────────────────────────────
int main() {
    cout << R"(
  ╔═══════════════════════════════════════════════╗
  ║      MeetSync — Smart Meeting Scheduler       ║
  ║      Algorithm : Greedy Activity Selection    ║
  ╚═══════════════════════════════════════════════╝
)";

    while (true) {
        cout << "\n  ┌── MENU ──────────────────────────────────┐\n";
        cout << "  │  1. Load sample meetings (demo data)     │\n";
        cout << "  │  2. Add your own meeting                 │\n";
        cout << "  │  3. View all meetings                    │\n";
        cout << "  │  4. Run Greedy Scheduler                 │\n";
        cout << "  │  5. Exit                                 │\n";
        cout << "  └──────────────────────────────────────────┘\n";
        cout << "  Choose: ";

        int ch;
        if (!(cin >> ch)) {
            cout << "  Invalid input. Exiting.\n";
            break;
        }
        cout << "\n";

        if      (ch == 1) loadSample();
        else if (ch == 2) addMeeting();
        else if (ch == 3) viewMeetings();
        else if (ch == 4) runScheduler();
        else if (ch == 5) { cout << "  Goodbye! \n\n"; break; }
        else              cout << "  Invalid option. Try 1-5.\n";
    }

    return 0;
}