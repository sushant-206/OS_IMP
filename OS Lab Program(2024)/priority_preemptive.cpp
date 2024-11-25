#include <bits/stdc++.h>  // Include all standard libraries in one header file
using namespace std;      // Use the standard namespace to avoid using 'std::' prefix

// Structure to represent each process with various attributes
struct Process {
    int processID;        // Unique ID for the process
    int burstTime;        // Burst time (execution time required by the process)
    int tempburstTime;    // Temporary burst time (used during scheduling)
    int responsetime;     // Response time (time taken to start executing)
    int arrivalTime;      // Arrival time (time when the process arrives)
    int priority;         // Priority of the process (lower value means higher priority)
    int outtime;          // Time at which the process finishes execution
    int intime;           // Time at which the process starts execution
};

// Function to insert a new process into the priority queue (min-heap)
void insert(Process Heap[], Process value, int* heapsize, int* currentTime) {
    int start = *heapsize, i;
    Heap[*heapsize] = value;   // Place the new process at the end of the heap
    if (Heap[*heapsize].intime == -1)
        Heap[*heapsize].intime = *currentTime;  // Set the start time if not already set
    ++(*heapsize);  // Increase the heap size

    // Maintain the min-heap property by bubbling up the process
    while (start != 0 && Heap[(start - 1) / 2].priority > Heap[start].priority) {
        Process temp = Heap[(start - 1) / 2];
        Heap[(start - 1) / 2] = Heap[start];
        Heap[start] = temp;
        start = (start - 1) / 2;
    }
}

// Function to maintain the min-heap property by heapifying down
void order(Process Heap[], int* heapsize, int start) {
    int smallest = start;
    int left = 2 * start + 1;   // Left child index
    int right = 2 * start + 2;  // Right child index

    // Compare the left child with the current smallest and update smallest if necessary
    if (left < *heapsize && Heap[left].priority < Heap[smallest].priority)
        smallest = left;

    // Compare the right child with the current smallest and update smallest if necessary
    if (right < *heapsize && Heap[right].priority < Heap[smallest].priority)
        smallest = right;

    // If smallest is not the current element, swap and continue heapifying
    if (smallest != start) {
        Process temp = Heap[smallest];
        Heap[smallest] = Heap[start];
        Heap[start] = temp;
        order(Heap, heapsize, smallest);  // Recursively heapify down
    }
}

// Function to extract the minimum priority process (root of the min-heap)
Process extractminimum(Process Heap[], int* heapsize, int* currentTime) {
    Process min = Heap[0];  // Root of the heap is the process with the highest priority (lowest priority value)
    if (min.responsetime == -1)
        min.responsetime = *currentTime - min.arrivalTime;  // Set the response time if not set
    --(*heapsize);  // Decrease heap size after extraction
    if (*heapsize >= 1) {
        Heap[0] = Heap[*heapsize];  // Move the last element to the root
        order(Heap, heapsize, 0);   // Restore the min-heap property by heapifying down
    }
    return min;  // Return the process with the highest priority
}

// Comparator function for sorting processes based on arrival time
bool compare(Process p1, Process p2) {
    return (p1.arrivalTime < p2.arrivalTime);  // Sort in ascending order of arrival time
}

// Function to simulate priority scheduling with preemption
void scheduling(Process Heap[], Process array[], int n, int* heapsize, int* currentTime) {
    if (*heapsize == 0)
        return;  // If heap is empty, exit the function

    // Extract the minimum priority process from the heap
    Process min = extractminimum(Heap, heapsize, currentTime);
    min.outtime = *currentTime + 1;   // Set the completion time of the process (finish time after executing for 1 unit)
    --min.burstTime;  // Decrease burst time after executing for 1 unit
    printf("process id = %d current time = %d\n", min.processID, *currentTime);  // Print process ID and current time

    // If the process still has remaining burst time, reinsert it into the heap for further execution
    if (min.burstTime > 0) {
        insert(Heap, min, heapsize, currentTime);
        return;
    }

    // If the process is finished, update the corresponding process in the array
    for (int i = 0; i < n; i++)
        if (array[i].processID == min.processID) {
            array[i] = min;  // Update process info in the array
            break;
        }
}

// Main function to handle the priority scheduling logic
void priority(Process array[], int n) {
    sort(array, array + n, compare);  // Sort processes based on arrival time

    int totalwaitingtime = 0, totalbursttime = 0, totalturnaroundtime = 0, insertedprocess = 0, heapsize = 0, currentTime = array[0].arrivalTime, totalresponsetime = 0;

    Process Heap[4 * n];  // Create a heap array to store processes (max size 4n)

    // Calculate total burst time and initialize processes
    for (int i = 0; i < n; i++) {
        totalbursttime += array[i].burstTime;
        array[i].tempburstTime = array[i].burstTime;  // Store original burst time in tempburstTime
    }

    do {
        if (insertedprocess != n) {
            // If not all processes are inserted, insert processes that have arrived
            for (int i = 0; i < n; i++) {
                if (array[i].arrivalTime == currentTime) {
                    ++insertedprocess;   // Increase the inserted process counter
                    array[i].intime = -1;  // Set the start time to -1 initially
                    array[i].responsetime = -1;  // Set the response time to -1 initially
                    insert(Heap, array[i], &heapsize, &currentTime);  // Insert process into the heap
                }
            }
        }
        scheduling(Heap, array, n, &heapsize, &currentTime);  // Execute one step of scheduling
        ++currentTime;  // Move time forward by 1 unit

        // Break out of the loop when all processes are completed
        if (heapsize == 0 && insertedprocess == n)
            break;
    } while (1);  // Infinite loop, exits when all processes are done

    // Calculate and print the average times for waiting, response, and turnaround
    for (int i = 0; i < n; i++) {
        totalresponsetime += array[i].responsetime;
        totalwaitingtime += (array[i].outtime - array[i].intime - array[i].tempburstTime);
        totalbursttime += array[i].burstTime;
    }

    // Output average waiting time, response time, and turnaround time
    printf("Average waiting time = %f\n", ((float)totalwaitingtime / (float)n));
    printf("Average response time =%f\n", ((float)totalresponsetime / (float)n));
    printf("Average turn around time = %f\n", ((float)(totalwaitingtime + totalbursttime) / (float)n));
}

// Main function to drive the program
int main() {
    int n;
    cout << "Enter the number of processes: ";  // Prompt user to enter the number of processes
    cin >> n;  // Read the number of processes

    Process a[n];  // Create an array of processes
    // Get process details from the user
    for (int i = 0; i < n; i++) {
        a[i].processID = i + 1;  // Assign process ID starting from 1
        cout << "Enter arrival time, burst time, and priority for process " << a[i].processID << ": ";
        cin >> a[i].arrivalTime >> a[i].burstTime >> a[i].priority;  // Input arrival time, burst time, and priority
    }

    // Start priority scheduling algorithm
    priority(a, n);
    return 0;  // End of program
}







/*
Sample input:
Enter the number of processes: 4
Enter arrival time, burst time, and priority for process 1: 0 8 1
Enter arrival time, burst time, and priority for process 2: 1 4 2
Enter arrival time, burst time, and priority for process 3: 2 9 3
Enter arrival time, burst time, and priority for process 4: 3 5 4

Output:
process id = 1 current time = 0
process id = 2 current time = 1
process id = 2 current time = 2
process id = 2 current time = 3
process id = 3 current time = 4
process id = 3 current time = 5
process id = 3 current time = 6
process id = 3 current time = 7
process id = 3 current time = 8
process id = 3 current time = 9
process id = 1 current time = 10
process id = 1 current time = 11
process id = 1 current time = 12
process id = 1 current time = 13
process id = 1 current time = 14
process id = 1 current time = 15
process id = 1 current time = 16
process id = 1 current time = 17
process id = 4 current time = 18
process id = 4 current time = 19
process id = 4 current time = 20
process id = 4 current time = 21
process id = 4 current time = 22

Average waiting time = 11.500000
Average response time = 3.000000
Average turn around time = 18.500000

*/