#include<iostream>           // Include input-output stream for handling input/output operations
#include<limits>             // Include limits library for numeric limits (used for initializing highest priority)
using namespace std;         // Use standard namespace to avoid using 'std::' prefix

// Class to represent a process
class Process {
    public:
        string processName;      // Name of the process
        int arrivalTime;         // Time when the process arrives
        int burstTime;           // Time the process requires to complete
        int priority;            // Priority of the process

        int remainingTime;       // Remaining time for the process to complete (used for scheduling)
        int responseTime;        // Time taken to respond (when the process starts executing)
        int completionTime;      // Time when the process finishes executing
        int waitingTime;         // Time the process spends waiting before execution
        int turnAroundTime;      // Total time spent in the system (completionTime - arrivalTime)

        // Method to initialize remaining time of a process
        void initialize() {
            remainingTime = burstTime; // Initially, remaining time equals the burst time
        }
};

int main() {
    int numOfProcesses;  // Variable to store the number of processes
    cout << "Enter no. of processes: ";    // Ask user to input number of processes
    cin >> numOfProcesses;   // Take input for the number of processes

    // Create an array of 'Process' objects based on the number of processes
    Process processes[numOfProcesses];

    // Input details for each process
    for (int n = 0; n < numOfProcesses; n++) {
        cout << "\nEnter Process Name for " << (n + 1) << ": ";  // Prompt for process name
        cin >> processes[n].processName;  // Take input for process name
        cout << "Enter Arrival Time for Process " << (n + 1) << ": ";  // Prompt for arrival time
        cin >> processes[n].arrivalTime;  // Take input for arrival time
        cout << "Enter Burst Time for Process " << (n + 1) << ": ";    // Prompt for burst time
        cin >> processes[n].burstTime;    // Take input for burst time
        cout << "Enter Priority for Process " << (n + 1) << ": ";   // Prompt for priority
        cin >> processes[n].priority;     // Take input for priority

        processes[n].initialize();        // Initialize the remaining time of the process
    }

    cout << "\n" << endl;

    // Sort the processes by arrival time in ascending order
    for (int i = 0; i < numOfProcesses - 1; i++) {
        for (int j = i + 1; j < numOfProcesses; j++) {
            if (processes[j].arrivalTime < processes[i].arrivalTime) {
                // Swap the processes if the arrival time of process j is earlier than process i
                Process temp = processes[j];
                processes[j] = processes[i];
                processes[i] = temp;
            }
        }
    }

    int currentTime = 0;  // Variable to track the current time during execution

    // Loop until all processes are completed
    while (true) {
        int currentHighestPriorityIndex = -1;  // Index to keep track of the process with the highest priority
        int currentHighestPriority = numeric_limits<int>::max();  // Set the initial highest priority to the maximum value

        bool isAllCompleted = true;  // Flag to check if all processes are completed

        // Iterate over all processes
        for (int i = 0; i < numOfProcesses; i++) {
            if (processes[i].remainingTime > 0) {  // If the process is not yet completed
                isAllCompleted = false;  // Set flag to false because there are still incomplete processes
                if (processes[i].arrivalTime <= currentTime) {  // Check if process has arrived
                    // Check if the process has a higher priority (lower priority value is higher priority)
                    if (processes[i].priority < currentHighestPriority) {
                        currentHighestPriority = processes[i].priority;  // Update the highest priority
                        currentHighestPriorityIndex = i;  // Update the index of the highest priority process
                    }
                }
            }
        }

        if (isAllCompleted) {
            break;  // If all processes are completed, exit the loop
        }

        // Start executing the process with the highest priority
        processes[currentHighestPriorityIndex].responseTime = currentTime;  // Record the response time (start time)
        processes[currentHighestPriorityIndex].remainingTime = 0;  // Set the remaining time to 0 as the process is completed
        currentTime += processes[currentHighestPriorityIndex].burstTime;  // Update current time by adding the burst time of the process
        processes[currentHighestPriorityIndex].completionTime = currentTime;  // Record the completion time
    }

    // Variables to store the sum of response time, completion time, waiting time, and turnaround time
    int sumResponseTime = 0;
    int sumCompletionTime = 0;
    int sumWaitingTime = 0;
    int sumTurnAroundTime = 0;

    // Output the details of each process and calculate the average times
    for (int n = 0; n < numOfProcesses; n++) {
        cout << "\nProcess " << processes[n].processName << ":\n";  // Display the process name
        cout << "Response Time: " << processes[n].responseTime << endl;  // Display the response time
        cout << "Completion Time: " << processes[n].completionTime << endl;  // Display the completion time
        processes[n].turnAroundTime = processes[n].completionTime - processes[n].arrivalTime;  // Calculate turnaround time
        processes[n].waitingTime = processes[n].turnAroundTime - processes[n].burstTime;  // Calculate waiting time
        cout << "Waiting Time: " << processes[n].waitingTime << endl;  // Display waiting time
        cout << "Turn Around Time: " << processes[n].turnAroundTime << "\n" << endl;  // Display turnaround time

        // Add the process's times to the respective sums
        sumResponseTime += processes[n].responseTime;
        sumCompletionTime += processes[n].completionTime;
        sumWaitingTime += processes[n].waitingTime;
        sumTurnAroundTime += processes[n].turnAroundTime;
    }

    // Calculate and display the average times for response time, completion time, waiting time, and turnaround time
    cout << "\n\nAverage Response Time for " << (numOfProcesses) << " Processes: " << (float)sumResponseTime / numOfProcesses;
    cout << "\n\nAverage Completion Time for " << (numOfProcesses) << " Processes: " << (float)sumCompletionTime / numOfProcesses;
    cout << "\n\nAverage Waiting Time for " << (numOfProcesses) << " Processes: " << (float)sumWaitingTime / numOfProcesses;
    cout << "\n\nAverage Turn Around Time for " << (numOfProcesses) << " Processes: " << (float)sumTurnAroundTime / numOfProcesses;

    return 0;  // End of program
}







/*
Sample input:
Enter no. of processes: 3

Enter Process Name for 1: P1
Enter Arrival Time for Process 1: 0
Enter Burst Time for Process 1: 4
Enter Priority for Process 1: 3

Enter Process Name for 2: P2
Enter Arrival Time for Process 2: 1
Enter Burst Time for Process 2: 3
Enter Priority for Process 2: 2

Enter Process Name for 3: P3
Enter Arrival Time for Process 3: 2
Enter Burst Time for Process 3: 2
Enter Priority for Process 3: 1

Output:
Process P1:
Response Time: 0
Completion Time: 4
Waiting Time: 0
Turn Around Time: 4

Process P2:
Response Time: 4
Completion Time: 7
Waiting Time: 1
Turn Around Time: 6

Process P3:
Response Time: 7
Completion Time: 9
Waiting Time: 5
Turn Around Time: 7


Average Response Time for 3 Processes: 3.66667
Average Completion Time for 3 Processes: 6.66667
Average Waiting Time for 3 Processes: 2
Average Turn Around Time for 3 Processes: 5.66667

*/