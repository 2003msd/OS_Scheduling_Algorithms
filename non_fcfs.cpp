#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;           // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int completion_time; // Completion time
};

void FCFS_non_preemptive(vector<Process>& processes) {
    int current_time = 0;
    for (auto& process : processes) {
        if (current_time < process.arrival_time) {
            current_time = process.arrival_time;
        }
        current_time += process.burst_time;
        process.completion_time = current_time;
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 4}, // {Process ID, Arrival Time, Burst Time}
        {2, 1, 3},
        {3, 2, 1},
        {4, 3, 2}
    };

    // Sorting by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    FCFS_non_preemptive(processes);

    cout << "Process ID\tArrival Time\tBurst Time\tCompletion Time\n";
    for (auto& process : processes) {
        cout << process.id << "\t\t" << process.arrival_time << "\t\t" 
             << process.burst_time << "\t\t" << process.completion_time << "\n";
    }

    return 0;
}
