#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;           // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int priority;     // Priority (lower value indicates higher priority)
    int completion_time; // Completion time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
};

void priority_scheduling(vector<Process>& processes) {
    int current_time = 0;
    int n = processes.size();

    // Sort processes by priority (if two processes have the same priority, sort by arrival time)
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        if (a.priority == b.priority) {
            return a.arrival_time < b.arrival_time;
        }
        return a.priority < b.priority;
    });

    for (int i = 0; i < n; i++) {
        // If the current time is less than the arrival time, fast-forward time
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        // Calculate completion time, turnaround time, and waiting time
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 10, 2}, // {Process ID, Arrival Time, Burst Time, Priority}
        {2, 2, 5, 1},
        {3, 1, 8, 3},
        {4, 3, 6, 0}
    };

    priority_scheduling(processes);

    cout << "Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (const auto& process : processes) {
        cout << process.id << "\t\t" << process.arrival_time << "\t\t" 
             << process.burst_time << "\t\t" << process.priority << "\t\t"
             << process.completion_time << "\t\t" << process.waiting_time << "\t\t"
             << process.turnaround_time << "\n";
    }

    return 0;
}
