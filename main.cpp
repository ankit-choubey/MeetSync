/*
 ╔═══════════════════════════════════════════════╗
 ║      MeetSync — Smart Meeting Scheduler       ║
 ║      Algorithm : Greedy (Activity Selection)  ║
 ║      Language  : C++                          ║
 ╚═══════════════════════════════════════════════╝

 HOW GREEDY WORKS HERE:
   1. Sort all meetings by their END time
   2. Go one by one — if no overlap with last picked → take it
   3. If overlap → reject it
   WHY OPTIMAL? Earliest-ending meeting leaves most room
   for future meetings. This is the Greedy Choice Property.
*/

#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

// ─────────────────────────────────────────
//  Data Structure
// ─────────────────────────────────────────
struct Meeting {
    int    id;
    string name;
    int    start;   // in minutes e.g. 09:30 → 570
    int    end;
};

const int MAX = 50;
Meeting meetings[MAX];
int total  = 0;
int nextId = 1;

// ─────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────

// "09:30" → 570
int toMin(const string &t) {
    return (t[0]-'0')*600 + (t[1]-'0')*60
         + (t[3]-'0')*10  + (t[4]-'0');
}

// 570 → "09:30"
string toTime(int m) {
    int h = m / 60, mn = m % 60;
    string s = "  :  ";
    s[0] = '0' + h  / 10;
    s[1] = '0' + h  % 10;
    s[3] = '0' + mn / 10;
    s[4] = '0' + mn % 10;
    return s;
}

// pad string to fixed width (replaces setw)
string pad(string s, int width) {
    while ((int)s.size() < width) s += ' ';
    return s;
}

void printLine() {
    cout << "====================================================\n";
}

// ─────────────────────────────────────────
//  Compare function for sort (by end time)
// ─────────────────────────────────────────
bool byEndTime(const Meeting &a, const Meeting &b) {
    return a.end < b.end;
}

// ─────────────────────────────────────────
//  Option 1 — Load Sample Data
// ─────────────────────────────────────────
void loadSample() {
    total  = 0;
    nextId = 1;

    meetings[total++] = {nextId++, "Team Standup",    toMin("09:00"), toMin("10:00")};
    meetings[total++] = {nextId++, "Design Sync",     toMin("09:30"), toMin("11:00")};
    meetings[total++] = {nextId++, "Client Review",   toMin("10:30"), toMin("11:30")};
    meetings[total++] = {nextId++, "Lunch Meeting",   toMin("10:00"), toMin("12:00")};
    meetings[total++] = {nextId++, "Sprint Planning", toMin("12:00"), toMin("13:00")};
    meetings[total++] = {nextId++, "Team Retro",      toMin("13:00"), toMin("14:00")};

    cout << "  Sample data loaded (6 meetings).\n";
}

// ─────────────────────────────────────────
//  Option 2 — Add a Meeting
// ─────────────────────────────────────────
void addMeeting() {
    if (total >= MAX) { cout << "  List full!\n"; return; }

    Meeting m;
    string s, e;
    cin.ignore(1000, '\n');

    cout << "  Meeting name  : "; getline(cin, m.name);
    cout << "  Start (HH:MM) : "; cin >> s;
    cout << "  End   (HH:MM) : "; cin >> e;

    m.start = toMin(s);
    m.end   = toMin(e);

    if (m.end <= m.start) {
        cout << "  End must be after start!\n"; return;
    }
    for (int i = 0; i < total; i++) {
        if (meetings[i].start == m.start && meetings[i].end == m.end) {
            cout << "  Same time slot already exists!\n"; return;
        }
    }

    m.id = nextId++;
    meetings[total++] = m;
    cout << "  Meeting \"" << m.name << "\" added!\n";
}

// ─────────────────────────────────────────
//  Option 3 — View All Meetings
// ─────────────────────────────────────────
void viewMeetings() {
    if (total == 0) { cout << "  No meetings yet.\n"; return; }

    printLine();
    cout << "  ID   NAME                     TIME\n";
    printLine();
    for (int i = 0; i < total; i++) {
        cout << "  [" << meetings[i].id << "]  "
             << pad(meetings[i].name, 24)
             << toTime(meetings[i].start) << " - "
             << toTime(meetings[i].end) << "\n";
    }
    printLine();
    cout << "  Total: " << total << " meeting(s)\n";
    printLine();
}

// ─────────────────────────────────────────
//  Option 4 — Run Greedy Scheduler
// ─────────────────────────────────────────
void runScheduler() {
    if (total == 0) { cout << "  No meetings to schedule.\n"; return; }

    // ── GREEDY STEP 1: Copy and sort by end time ──
    cout << "\n  [Greedy] Step 1: Sorting " << total
         << " meetings by end time...\n";

    Meeting sorted[MAX];
    for (int i = 0; i < total; i++) sorted[i] = meetings[i];
    sort(sorted, sorted + total, byEndTime);

    // ── GREEDY STEP 2: Pick non-overlapping meetings ──
    cout << "  [Greedy] Step 2: Picking meetings greedily...\n\n";

    Meeting scheduled[MAX], rejected[MAX];
    int schedCount = 0, rejCount = 0;
    int lastEnd = -1;

    for (int i = 0; i < total; i++) {
        if (sorted[i].start >= lastEnd) {
            scheduled[schedCount++] = sorted[i];  // no overlap → pick it
            lastEnd = sorted[i].end;
        } else {
            rejected[rejCount++] = sorted[i];     // overlap → reject
        }
    }

    // ── Find which meeting each rejected one conflicts with ──
    auto findConflict = [&](const Meeting &r) -> string {
        for (int i = 0; i < schedCount; i++)
            if (r.start < scheduled[i].end && r.end > scheduled[i].start)
                return scheduled[i].name;
        return "another meeting";
    };

    // ── OUTPUT ────────────────────────────────
    cout << "\n";
    printLine();
    cout << "  MEETSYNC — MEETING SCHEDULER RESULT\n";
    printLine();
    cout << "  Total Meetings Requested : " << total << "\n\n";

    cout << "  SCHEDULED:\n";
    for (int i = 0; i < schedCount; i++) {
        cout << "    [" << scheduled[i].id << "] "
             << pad(scheduled[i].name, 22)
             << "| " << toTime(scheduled[i].start)
             << " - " << toTime(scheduled[i].end) << "\n";
    }

    if (rejCount > 0) {
        cout << "\n  REJECTED (Conflicts):\n";
        for (int i = 0; i < rejCount; i++) {
            cout << "    [" << rejected[i].id << "] "
                 << pad(rejected[i].name, 22)
                 << "| " << toTime(rejected[i].start)
                 << " - " << toTime(rejected[i].end)
                 << "  <- overlaps with \""
                 << findConflict(rejected[i]) << "\"\n";
        }
    }

    printLine();
    cout << "  Max meetings in a day : " << schedCount << "\n";
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
        else if (ch == 5) { cout << "  Goodbye!\n\n"; break; }
        else              cout << "  Invalid option. Try 1-5.\n";
    }

    return 0;
}