#include <iostream>
#include <vector>
using namespace std;

// Function to check if a system is in a safe state
bool isSafeState(vector<vector<int>>& allocation, vector<vector<int>>& max, vector<int>& available, int n, int m) {
    // Step 1: Initialize work and finish arrays
    vector<int> work = available;  // Initialize work with available resources
    vector<bool> finish(n, false);  // Finish array to mark whether a process has finished
    vector<int> safeSequence;  // This will hold the safe sequence of processes
    bool found;  // Flag to track if a process is found in each iteration

    // Step 2: Try to find a safe sequence
    for (int k = 0; k < n; k++) {  // Try for all processes
        found = false;
        
        // Step 3: Try to find a process that can finish
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {  // If process i hasn't finished yet
                bool possible = true;  // Flag to check if process i can finish

                // Step 4: Check if process i's remaining needs can be satisfied with the available resources
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {  // If process i's needs > available resources
                        possible = false;  // Process i cannot be satisfied
                        break;
                    }
                }

                // Step 5: If process i can finish, update work and finish arrays
                if (possible) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];  // Add allocated resources back to work
                    }
                    finish[i] = true;  // Mark process i as finished
                    found = true;  // We found a process that can finish
                    safeSequence.push_back(i);  // Add this process to the safe sequence
                }
            }
        }

        // Step 6: If no process can be found that can finish, the system is not in a safe state
        if (!found) {
            return false;  // System is not in a safe state
        }
    }

    // Step 7: If we find a safe sequence, print it and return true
    cout << "System is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < safeSequence.size(); i++) {
        cout << safeSequence[i] << " ";  // Print the safe sequence
    }
    cout << endl;

    return true;  // System is in a safe state
}

int main() {
    int n, m; // Number of processes (n) and resource types (m)

    cout << "Enter the number of processes: ";
    cin >> n;  // Input the number of processes
    cout << "Enter the number of resource types: ";
    cin >> m;  // Input the number of resource types

    // Step 1: Declare and input the allocation matrix (allocation[i][j] stores the allocation of resource j for process i)
    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));  // Maximum demand matrix
    vector<int> available(m);  // Available resources array

    // Input the allocation matrix (row-wise)
    cout << "Enter the allocation matrix (row-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];  // Read allocation values
        }
    }

    // Input the maximum demand matrix (row-wise)
    cout << "Enter the maximum demand matrix (row-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];  // Read max demand values
        }
    }

    // Input the available resources
    cout << "Enter the available resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> available[i];  // Read available resources
    }

    // Step 2: Check if the system is in a safe state
    if (!isSafeState(allocation, max, available, n, m)) {
        cout << "System is not in a safe state.\n";  // If not in a safe state, print a message
    }

    return 0;  // End of program
}





/*
sample input
Enter the number of processes: 5
Enter the number of resources: 3
Enter the available resources: 3 3 2
Enter the maximum demand matrix :
7 5 3 
3 2 2
9 0 2
2 2 2
4 3 3
Enter the allocation matrix :
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2



Output: System is in safe state!
safe sequence: 1 3 4 0 2
*/