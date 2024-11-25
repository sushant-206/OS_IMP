#include <bits/stdc++.h>  // Includes all standard C++ libraries (useful for competitive programming).
using namespace std;

// Structure to represent a process.
struct Process {
    int pid; // Process ID
    int bt;  // Burst Time (the amount of time the process needs to complete)
    int art; // Arrival Time (the time at which the process arrives in the queue)
};

// Function to calculate waiting times for all processes.
void findWaitingTime(Process proc[], int n, int wt[]) {
    int rt[n]; // Array to store remaining burst times for each process.

    // Initialize remaining burst times (initially same as burst time).
    for (int i = 0; i < n; i++)
        rt[i] = proc[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;

    // While there are processes that are not yet completed
    while (complete != n) {
        // Check which process has the minimum remaining burst time
        for (int j = 0; j < n; j++) {
            // Check if the process has arrived and has remaining time
            if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];        // Update minimum remaining time
                shortest = j;        // Track the process with the shortest remaining burst time
                check = true;        // Flag to indicate we found a process
            }
        }

        if (check == false) {  // If no process is ready to execute, increment time and continue
            t++;
            continue;
        }

        // Decrement remaining burst time for the chosen process
        rt[shortest]--;

        // Update the minimum remaining time after the process has executed
        minm = rt[shortest];
        if (minm == 0)  // If there are no remaining burst times, set it to infinity
            minm = INT_MAX;

        // If the process is completely executed (its remaining time is 0)
        if (rt[shortest] == 0) {
            complete++;  // Increment the count of completed processes
            check = false;  // Reset the flag

            finish_time = t + 1;  // Process finishes at the current time + 1

            // Calculate the waiting time for the process (finish_time - burst_time - arrival_time)
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art;

            if (wt[shortest] < 0)  // If waiting time is negative (process executed immediately), set it to 0
                wt[shortest] = 0;
        }
        t++;  // Move to the next time unit
    }
}

// Function to calculate turnaround times for all processes.
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = proc[i].bt + wt[i];  // Turnaround time = Burst time + Waiting time
}

// Function to calculate and display average waiting time and average turnaround time.
void findavgTime(Process proc[], int n) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Calculate waiting times for all processes
    findWaitingTime(proc, n, wt);
    // Calculate turnaround times for all processes
    findTurnAroundTime(proc, n, wt, tat);

    // Print the table of process information
    cout << " P\t\t"
         << "BT\t\t"
         << "WT\t\t"
         << "TAT\t\t\n";

    // Print each process's details
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];  // Sum of waiting times
        total_tat += tat[i]; // Sum of turnaround times
        cout << " " << proc[i].pid << "\t\t"
             << proc[i].bt << "\t\t " << wt[i]
             << "\t\t " << tat[i] << endl;  // Print each process's data
    }

    // Calculate and display the average waiting time and average turnaround time
    cout << "\nAverage waiting time = "
         << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n;
}

// Main function: Entry point of the program.
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;  // Input the number of processes

    Process proc[n];  // Declare an array of 'n' processes

    // Input burst time and arrival time for each process
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;  // Process ID is assigned sequentially (1-based)
        cout << "Enter burst time for process " << proc[i].pid << ": ";
        cin >> proc[i].bt;  // Input the burst time for the process
        cout << "Enter arrival time for process " << proc[i].pid << ": ";
        cin >> proc[i].art;  // Input the arrival time for the process
    }

    // Call the function to calculate and display average times
    findavgTime(proc, n);
    return 0;  // Return from the main function
}










/*
Sample input:
Enter the number of processes: 4
Enter burst time for process 1: 6
Enter arrival time for process 1: 2
Enter burst time for process 2: 8
Enter arrival time for process 2: 3
Enter burst time for process 3: 7
Enter arrival time for process 3: 1
Enter burst time for process 4: 3
Enter arrival time for process 4: 4


output:
 P           BT          WT          TAT         
 1           6           7           13
 2           8           7           15
 3           7           0           7
 4           3           3           6

Average waiting time = 4.25
Average turn around time = 10.25

*/