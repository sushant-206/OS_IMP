#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to calculate total seek operations for SSTF (Shortest Seek Time First)
int sstf(vector<int> requests, int head) {
    int totalSeekOperations = 0;  // Initialize total seek operations counter
    while (!requests.empty()) {  // Continue until all requests are served
        // Find the request closest to the current head position
        auto closest = min_element(requests.begin(), requests.end(),
            [head](int a, int b) { return abs(a - head) < abs(b - head); });
        
        // Add the distance from the current head to the closest request
        totalSeekOperations += abs(*closest - head);
        head = *closest;  // Update head to the position of the closest request
        requests.erase(closest);  // Remove the processed request from the list
    }
    return totalSeekOperations;  // Return the total seek operations calculated
}

// Function to calculate total seek operations for SCAN
int scan(vector<int> requests, int head, int diskSize) {
    int totalSeekOperations = 0;  // Initialize total seek operations counter
    requests.push_back(head);  // Add the initial head position to the requests
    sort(requests.begin(), requests.end());  // Sort all requests in ascending order
    
    // Find the iterator pointing to the position of the head in the sorted list
    auto it = find(requests.begin(), requests.end(), head);
    
    // Move the head towards the end of the disk (right direction)
    for (auto i = it; i != requests.end(); ++i) {
        totalSeekOperations += abs(head - *i);  // Add the distance to the current request
        head = *i;  // Move the head to the current request's position
    }
    
    // Check if the head has reached the end of the disk
    if (head != diskSize - 1) {
        totalSeekOperations += abs((diskSize - 1) - head);  // Move the head to the end of the disk
        head = diskSize - 1;  // Update head to the end of the disk
    }

    // Move the head back towards the beginning of the disk (left direction)
    for (auto i = it - 1; i >= requests.begin(); --i) {
        totalSeekOperations += abs(head - *i);  // Add the distance to the current request
        head = *i;  // Move the head to the current request's position
    }
    return totalSeekOperations;  // Return the total seek operations calculated
}

// Function to calculate total seek operations for C-LOOK
int c_look(vector<int> requests, int head) {
    int totalSeekOperations = 0;  // Initialize total seek operations counter
    requests.push_back(head);  // Add the initial head position to the requests
    sort(requests.begin(), requests.end());  // Sort all requests in ascending order

    // Find the iterator pointing to the position of the head in the sorted list
    auto it = find(requests.begin(), requests.end(), head);

    // Move the head towards the end of the disk (right direction)
    for (auto i = it; i != requests.end(); ++i) {
        totalSeekOperations += abs(head - *i);  // Add the distance to the current request
        head = *i;  // Move the head to the current request's position
    }

    // Move the head back to the beginning (wrap around)
    if (head != requests.front()) {
        totalSeekOperations += abs(head - requests.front());  // Move the head to the first request
        head = requests.front();  // Update head to the first request position

        // Complete the remaining requests by moving to the right
        for (auto i = requests.begin(); i != it; ++i) {
            totalSeekOperations += abs(head - *i);  // Add the distance to the current request
            head = *i;  // Move the head to the current request's position
        }
    }

    return totalSeekOperations;  // Return the total seek operations calculated
}

int main() {
    int diskSize, numRequests, head;
    
    // Input the size of the disk
    cout << "Enter the disk size: ";
    cin >> diskSize;
    
    // Input the number of disk requests
    cout << "Enter the number of disk requests: ";
    cin >> numRequests;

    vector<int> requests(numRequests);  // Vector to store the disk requests
    cout << "Enter the disk requests: ";
    for (int i = 0; i < numRequests; ++i) {
        cin >> requests[i];  // Read each disk request
    }

    // Input the initial position of the head
    cout << "Enter the initial head position: ";
    cin >> head;

    // Call each scheduling algorithm function and output the results
    cout << "\nTotal seek operations using SSTF: " << sstf(requests, head) << endl;
    cout << "Total seek operations using SCAN: " << scan(requests, head, diskSize) << endl;
    cout << "Total seek operations using C-LOOK: " << c_look(requests, head) << endl;

    return 0;  // Program execution ends successfully
}






/*
Sample input:
Enter the disk size: 200
Enter the number of disk requests: 8
Enter the disk requests: 98 183 37 122 14 124 65 67
Enter the initial head position: 53

Total seek operations using SSTF: 236
Total seek operations using SCAN: 331
Total seek operations using C-LOOK: 322
*/