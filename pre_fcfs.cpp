#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id;           // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int remaining_time; // Remaining time
};

void FCFS_preemptive(vector<Process>& processes) {
    int current_time = 0;
    queue<Process*> ready_queue;

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    size_t index = 0;
    while (index < processes.size() || !ready_queue.empty()) {
        // Add processes to ready queue if they have arrived
        while (index < processes.size() && processes[index].arrival_time <= current_time) {
            ready_queue.push(&processes[index]);
            index++;
        }

        if (!ready_queue.empty()) {
            // Execute the process at the front of the queue
            Process* current_process = ready_queue.front();
            ready_queue.pop();

            // Execute the process for 1 time unit
            current_process->remaining_time--;
            current_time++;

            // If the process has remaining time, add it back to the ready queue
            if (current_process->remaining_time > 0) {
                ready_queue.push(current_process);
            } else {
                cout << "Process " << current_process->id << " completed at time " << current_time << endl;
            }
        } else {
            // If no process is ready, increment the time
            current_time++;
        }
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 4, 4}, // {Process ID, Arrival Time, Burst Time, Remaining Time}
        {2, 1, 3, 3},
        {3, 2, 1, 1},
        {4, 3, 2, 2}
    };

    FCFS_preemptive(processes);

    return 0;
}
