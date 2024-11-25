#include <iostream>
using namespace std;

// Function to calculate waiting time, turnaround time, and completion time
void CalculateTimes(int at[], int bt[], int N) {
    // Declare arrays for waiting time, turnaround time, and completion time
    int wt[N], tat[N], ct[N];

    // Waiting time for the first process is 0
    wt[0] = 0;

    // Completion time of the first process
    ct[0] = at[0] + bt[0];

    // Turnaround time for the first process
    tat[0] = ct[0] - at[0];

    // Print waiting time, completion time, and turnaround time headers
    cout << "PN\t\tAT\t\tBT\t\tWT\t\tCT\t\tTAT\n\n";
    cout << "1"
         << "\t\t" << at[0] << "\t\t"
         << bt[0] << "\t\t" << wt[0] << "\t\t"
         << ct[0] << "\t\t" << tat[0] << endl;

    // Calculating waiting time, turnaround time, and completion time for each process
    for (int i = 1; i < N; i++) {
        // Calculate waiting time for process i
        wt[i] = (at[i - 1] + bt[i - 1] + wt[i - 1]) - at[i];
        
        // Calculate completion time for process i
        ct[i] = at[i] + bt[i] + wt[i];

        // Calculate turnaround time for process i
        tat[i] = ct[i] - at[i];

        // Print the waiting time, completion time, and turnaround time for each process
        cout << i + 1 << "\t\t" << at[i]
             << "\t\t" << bt[i] << "\t\t"
             << wt[i] << "\t\t" << ct[i]
             << "\t\t" << tat[i] << endl;
    }
}

// Driver code
int main() {
    int N;

    // Prompt user for the number of processes
    cout << "Enter the number of processes: ";
    cin >> N;

    // Dynamically allocate arrays based on the number of processes
    int *at = new int[N];
    int *bt = new int[N];

    // Input arrival times
    for (int i = 0; i < N; i++) {
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> at[i];
    }

    // Input burst times
    for (int i = 0; i < N; i++) {
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> bt[i];
    }

    // Function call to find waiting time, turnaround time, and completion time
    CalculateTimes(at, bt, N);

    // Free allocated memory
    delete[] at;
    delete[] bt;

    return 0;
}









/*
Sample input: 
Enter the number of processes: 3
Enter arrival time for process 1: 0
Enter burst time for process 1: 4
Enter arrival time for process 2: 1
Enter burst time for process 2: 3
Enter arrival time for process 3: 2
Enter burst time for process 3: 5

Output:
PN		AT		BT		WT		CT		TAT

1		0		4		0		4		4
2		1		3		3		7		6
3		2		5		5		12		10

*/