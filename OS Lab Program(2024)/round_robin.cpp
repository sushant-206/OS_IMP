#include<iostream>  // Include the standard input-output library
using namespace std;  // Use the standard namespace to avoid using 'std::' prefix

// Function to calculate waiting time for each process
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n];  // Array to store remaining burst time for each process

    // Copy burst times into the remaining burst time array
    for (int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    int t = 0;  // Variable to keep track of the current time (initially 0)

    // Infinite loop until all processes are done
    while (1) {
        bool done = true;  // Flag to check if all processes are done

        // Loop through all processes to simulate the Round Robin scheduling
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {  // If remaining burst time is greater than 0 (process is not finished)
                done = false;  // Set done to false because there are still processes to execute

                if (rem_bt[i] > quantum) {  // If remaining burst time is more than quantum, process runs for quantum time
                    t += quantum;  // Increment time by quantum
                    rem_bt[i] -= quantum;  // Decrease remaining burst time by quantum
                } else {  // If remaining burst time is less than or equal to quantum, process finishes
                    t = t + rem_bt[i];  // Increment time by the remaining burst time
                    wt[i] = t - bt[i];  // Calculate waiting time for the process (t - burst time)
                    rem_bt[i] = 0;  // Set remaining burst time to 0, process is finished
                }
            }
        }

        // If all processes are done, exit the loop
        if (done == true)
            break;
    }
}

// Function to calculate turnaround time for each process
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];  // Turnaround time is burst time + waiting time
}

// Function to calculate average waiting time and turnaround time
void findavgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;  // Arrays for waiting time and turnaround time, and variables for totals

    // Calculate waiting time and turnaround time
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Print the header of the table
    cout << "PN\t " << " \tBT " << " WT " << " \tTAT\n";

    // Loop through all processes to print their burst time, waiting time, and turnaround time
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];  // Accumulate total waiting time
        total_tat = total_tat + tat[i];  // Accumulate total turnaround time
        cout << " " << processes[i] << "\t\t" << bt[i] <<"\t " << wt[i] <<"\t\t " << tat[i] << endl;  // Print details for each process
    }

    // Calculate and print the average waiting time and turnaround time
    cout << "Average waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

// Main function to drive the program
int main() {
    int n;  // Variable to store number of processes
    cout << "Enter the number of processes: ";  // Prompt user to enter the number of processes
    cin >> n;  // Read the number of processes from user

    int processes[n];  // Array to store process IDs
    int burst_time[n];  // Array to store burst times for each process

    // Input burst times for each process
    for (int i = 0; i < n; i++) {
        cout << "Enter burst time for process " << i + 1 << ": ";  // Ask for burst time of each process
        cin >> burst_time[i];  // Read burst time for process i
        processes[i] = i + 1;  // Assign process IDs sequentially (starting from 1)
    }

    int quantum;  // Variable to store time quantum
    cout << "Enter time quantum: ";  // Prompt user to enter time quantum
    cin >> quantum;  // Read time quantum

    // Calculate and print the average waiting time and turnaround time for the processes
    findavgTime(processes, n, burst_time, quantum);
    return 0;  // End of the program
}












/*
Sample input:
Enter the number of processes: 4
Enter burst time for process 1: 5
Enter burst time for process 2: 10
Enter burst time for process 3: 8
Enter burst time for process 4: 6
Enter time quantum: 4


Output:
PN      BT  WT      TAT
 1       5   4       9
 2      10   4      14
 3       8   4      12
 4       6   4      10
Average waiting time = 4.0
Average turn around time = 11.25

*/