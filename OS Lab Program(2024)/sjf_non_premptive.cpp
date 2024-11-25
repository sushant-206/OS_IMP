#include <bits/stdc++.h>  // Includes standard C++ libraries (commonly used in competitive programming).
using namespace std;

// Defining shorthand for common types and constants
#define ll long long          // Alias for long long type.
#define z 1000000007          // A large prime number, often used for modulo operations in competitive programming.
#define sh 100000             // A large constant, likely for the maximum number of processes.
#define pb push_back          // A shorthand for the push_back function of vectors.
#define pr(x) printf("%d ", x) // A macro for printing integers, used to avoid the overhead of 'cout' in some cases.

// Define a structure to represent process-related information.
struct util {
    int id;     // Process ID
    int at;     // Arrival time of the process
    int bt;     // Burst time of the process (how long the process needs to run)
    int ct;     // Completion time of the process (when the process finishes)
    int tat;    // Turnaround time (ct - at)
    int wt;     // Waiting time (tat - bt)
};

// Array to store information about each process.
util ar[sh + 1];

// A structure used in the segment tree to store the process and its burst time.
struct util1 {
    int p_id;   // Process ID
    int bt1;    // Burst time of the process
};

// Temporary structure to store the result from the segment tree query.
util1 range;

// Segment tree array for efficient querying and updates.
util1 tr[4 * sh + 5];

// Array to store the process position (used for indexing processes).
int mp[sh + 1];

// Comparison function used to sort processes based on their arrival times, and by their ID in case of ties.
bool cmp(util a, util b) {
    if (a.at == b.at)
        return a.id < b.id; // If arrival times are the same, sort by process ID
    return a.at < b.at; // Otherwise, sort by arrival time
}

// Function to update the segment tree with the process information (ID and burst time).
void update(int node, int st, int end, int ind, int id1, int b_t) {
    if (st == end) {
        tr[node].p_id = id1;  // Update the process ID at this node
        tr[node].bt1 = b_t;   // Update the burst time at this node
        return;
    }
    int mid = (st + end) / 2;  // Find the middle of the segment
    if (ind <= mid)
        update(2 * node, st, mid, ind, id1, b_t);  // If the index is in the left half, update the left child
    else
        update(2 * node + 1, mid + 1, end, ind, id1, b_t);  // Otherwise, update the right child

    // After updating the children, update this node based on the child values
    if (tr[2 * node].bt1 < tr[2 * node + 1].bt1) {
        tr[node].bt1 = tr[2 * node].bt1;
        tr[node].p_id = tr[2 * node].p_id;
    } else {
        tr[node].bt1 = tr[2 * node + 1].bt1;
        tr[node].p_id = tr[2 * node + 1].p_id;
    }
}

// Function to query the segment tree for the process with the minimum burst time in the range [lt, rt].
util1 query(int node, int st, int end, int lt, int rt) {
    if (end < lt || st > rt)
        return range;  // If the range is out of bounds, return a default 'empty' result
    if (st >= lt && end <= rt)
        return tr[node];  // If the node is fully within the query range, return its stored result

    int mid = (st + end) / 2;  // Find the middle of the segment
    util1 lm = query(2 * node, st, mid, lt, rt);  // Query the left half
    util1 rm = query(2 * node + 1, mid + 1, end, lt, rt);  // Query the right half

    // Return the result with the minimum burst time
    if (lm.bt1 < rm.bt1)
        return lm;
    return rm;
}

// Function to execute the Non-Preemptive Shortest Job First (SJF) scheduling algorithm.
void non_preemptive_sjf(int n) {
    int counter = n;  // Counter for the remaining processes
    int upper_range = 0;  // Index for processes that have arrived
    int tm = min(INT_MAX, ar[upper_range + 1].at);  // Initialize the current time (tm)

    // While there are processes left to execute
    while (counter) {
        // Update the segment tree with all processes that have arrived until the current time
        for (; upper_range <= n;) {
            upper_range++;
            if (ar[upper_range].at > tm || upper_range > n) {
                upper_range--;  // Stop if no more processes are ready or we exceed the total process count
                break;
            }
            update(1, 1, n, upper_range, ar[upper_range].id, ar[upper_range].bt);  // Update the segment tree with process info
        }

        // Query the segment tree for the process with the shortest burst time
        util1 res = query(1, 1, n, 1, upper_range);
        if (res.bt1 != INT_MAX) {  // If a valid process is found
            counter--;
            int index = mp[res.p_id];  // Find the index of the process
            tm += res.bt1;  // Update the current time by adding the burst time of the process
            ar[index].ct = tm;  // Set the completion time of the process
            ar[index].tat = ar[index].ct - ar[index].at;  // Calculate the turnaround time
            ar[index].wt = ar[index].tat - ar[index].bt;  // Calculate the waiting time
            update(1, 1, n, index, INT_MAX, INT_MAX);  // Mark this process as completed in the segment tree
        } else {
            tm = ar[upper_range + 1].at;  // If no process is available, move to the next arrival time
        }
    }
}

// Function to execute the entire scheduling and calculation process.
void execute(int n) {
    sort(ar + 1, ar + n + 1, cmp);  // Sort processes by arrival time (and by ID if tied)
    for (int i = 1; i <= n; i++)
        mp[ar[i].id] = i;  // Store the position of each process in the mp array
    non_preemptive_sjf(n);  // Call the non-preemptive SJF function to perform scheduling
}

// Function to print the results in a formatted table.
void print(int n) {
    cout << "ProcessId "
         << "Arrival Time "
         << "Burst Time "
         << "Completion Time "
         << "Turn Around Time "
         << "Waiting Time\n";
    for (int i = 1; i <= n; i++) {
        cout << ar[i].id << " \t\t "
             << ar[i].at << " \t\t "
             << ar[i].bt << " \t\t "
             << ar[i].ct << " \t\t "
             << ar[i].tat << " \t\t "
             << ar[i].wt << " \n";  // Print the results for each process
    }
}

// Function to calculate and print the average waiting time and average turnaround time.
void calculate_averages(int n) {
    double total_wt = 0, total_tat = 0;
    for (int i = 1; i <= n; i++) {
        total_wt += ar[i].wt;  // Sum up the waiting times
        total_tat += ar[i].tat;  // Sum up the turnaround times
    }
    cout << "\nAverage Waiting Time: " << total_wt / n << "\n";  // Print average waiting time
    cout << "Average Turnaround Time: " << total_tat / n << "\n";  // Print average turnaround time
}

// Main function: Entry point of the program
int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;  // Input the number of processes

    range.p_id = INT_MAX;  // Initialize range with a very large process ID (used in segment tree)
    range.bt1 = INT_MAX;   // Initialize range with a very large burst time

    // Initialize the segment tree with default values
    for (int i = 1; i <= 4 * sh + 1; i++) {
        tr[i].p_id = INT_MAX;
        tr[i].bt1 = INT_MAX;
    }

    // Input the arrival and burst times for each process
    for (int i = 1; i <= n; i++) {
        cout << "Enter arrival time and burst time for process " << i << ": ";
        cin >> ar[i].at >> ar[i].bt;  // Take input for each process
        ar[i].id = i;  // Set the process ID
    }

    execute(n);  // Execute the SJF scheduling
    print(n);    // Print the results
    calculate_averages(n);  // Calculate and display the averages

    return 0;  // Return from main function
}










/*
Sample input:
Enter the number of processes: 4
Enter arrival time and burst time for process 1: 0 5
Enter arrival time and burst time for process 2: 1 2
Enter arrival time and burst time for process 3: 2 8
Enter arrival time and burst time for process 4: 3 1

Output:
ProcessId  Arrival Time  Burst Time  Completion Time  Turn Around Time  Waiting Time
1           0            5           6                6                1
2           1            2           3                2                0
3           2            8           14               12               4
4           3            1           7                4                3

Average Waiting Time: 2.0
Average Turnaround Time: 7.33333

*/