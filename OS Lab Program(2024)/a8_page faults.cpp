#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

// Function to check if a page is present in the frames
bool isPagePresent(const vector<int>& frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end(); // Returns true if the page is in the frames
}

// Function to find the page to replace in the Optimal algorithm
int findOptimalPageToReplace(const vector<int>& frames, const vector<int>& referenceString, int currentIndex) {
    int farthest = currentIndex; // Initially, set the farthest page to the current index
    int pageToReplace = -1; // Initialize variable for the page to replace
    
    // For each page in frames, find the page whose next use is the farthest in the future
    for (int frame : frames) {
        int nextUse = INT_MAX;  // Default to an arbitrarily large value (INT_MAX)
        
        // Search for the next occurrence of this page in the reference string
        for (int j = currentIndex + 1; j < referenceString.size(); ++j) {
            if (frame == referenceString[j]) {  // Found the page in the reference string
                nextUse = j; // Update next use to the index of the next occurrence
                break;
            }
        }
        
        // If this page is used farthest in the future, it is the candidate for replacement
        if (nextUse > farthest) {
            farthest = nextUse;
            pageToReplace = frame;
        }
    }
    return pageToReplace; // Return the page that will be replaced
}

// Function for FIFO (First-In-First-Out) Page Replacement Algorithm
int fifoPageFaults(const vector<int>& referenceString, int framesCount) {
    queue<int> frames;  // Queue to store the pages in the frames
    unordered_map<int, bool> inFrame;  // Map to quickly check if a page is in the frames
    int pageFaults = 0;  // Counter for page faults
    
    // Loop through each page in the reference string
    for (int page : referenceString) {
        if (inFrame[page] == false) {  // If the page is not in the frames
            if (frames.size() == framesCount) {  // If the frames are full
                int removedPage = frames.front();  // Remove the page at the front of the queue
                frames.pop();  // Pop the front page
                inFrame[removedPage] = false;  // Mark the page as no longer in the frames
            }
            frames.push(page);  // Add the new page to the frames
            inFrame[page] = true;  // Mark the new page as present in the frames
            pageFaults++;  // Increment the page fault count
        }
    }
    return pageFaults;  // Return the total number of page faults
}

// Function for LRU (Least Recently Used) Page Replacement Algorithm
int lruPageFaults(const vector<int>& referenceString, int framesCount) {
    vector<int> frames;  // Vector to store pages in the frames
    unordered_map<int, int> lastUsed;  // Map to store the last used index of each page
    int pageFaults = 0;  // Counter for page faults
    
    // Loop through each page in the reference string
    for (int i = 0; i < referenceString.size(); ++i) {
        int page = referenceString[i];  // Get the current page
        
        // If the page is not in the frames
        if (!isPagePresent(frames, page)) {
            if (frames.size() == framesCount) {  // If the frames are full
                // Find the least recently used page
                int lruPage = frames[0];  // Assume the first page is the least recently used
                for (int frame : frames) {
                    // Compare the last used index of each page
                    if (lastUsed[frame] < lastUsed[lruPage]) {
                        lruPage = frame;
                    }
                }
                // Replace the LRU page with the current page
                replace(frames.begin(), frames.end(), lruPage, page);
            } else {
                frames.push_back(page);  // If there is space, simply add the page to frames
            }
            pageFaults++;  // Increment page fault count
        }
        lastUsed[page] = i;  // Update the last used index for the current page
    }
    return pageFaults;  // Return the total number of page faults
}

// Function for Optimal Page Replacement Algorithm
int optimalPageFaults(const vector<int>& referenceString, int framesCount) {
    vector<int> frames;  // Vector to store pages in the frames
    int pageFaults = 0;  // Counter for page faults
    
    // Loop through each page in the reference string
    for (int i = 0; i < referenceString.size(); ++i) {
        int page = referenceString[i];  // Get the current page
        
        // If the page is not already in the frames
        if (!isPagePresent(frames, page)) {
            if (frames.size() == framesCount) {  // If the frames are full
                // Find the page that should be replaced (the one used the farthest in the future)
                int pageToReplace = findOptimalPageToReplace(frames, referenceString, i);
                // Replace the farthest page with the current page
                replace(frames.begin(), frames.end(), pageToReplace, page);
            } else {
                frames.push_back(page);  // If there is space, add the page to frames
            }
            pageFaults++;  // Increment page fault count
        }
    }
    return pageFaults;  // Return the total number of page faults
}

int main() {
    int framesCount, referenceLength;  // Variables for the number of frames and length of reference string
    cout << "Enter the number of frames: ";
    cin >> framesCount;  // Input for the number of frames
    
    cout << "Enter the length of the reference string: ";
    cin >> referenceLength;  // Input for the length of the reference string
    
    vector<int> referenceString(referenceLength);  // Vector to store the reference string
    cout << "Enter the reference string: ";
    for (int i = 0; i < referenceLength; ++i) {
        cin >> referenceString[i];  // Input for the reference string
    }

    // Calculate and print the number of page faults for each page replacement algorithm
    cout << "\nPage Faults using FIFO: " << fifoPageFaults(referenceString, framesCount) << endl;
    cout << "Page Faults using LRU: " << lruPageFaults(referenceString, framesCount) << endl;
    cout << "Page Faults using Optimal: " << optimalPageFaults(referenceString, framesCount) << endl;

    return 0;  // Program execution ends successfully
}



/*
Sample inputs:
Enter the number of frames: 3
Enter the length of the reference string: 12
Enter the reference string: 7 0 1 2 0 3 0 4 2 3 0 3

Page Faults using FIFO: 10
Page Faults using LRU: 9
Page Faults using Optimal: 7
*/