#include <iostream>
#include <vector>
#include <unistd.h>      // For fork(), sleep(), getpid()
#include <sys/wait.h>    // For wait()
#include <algorithm>     // For std::swap
#include <cstdlib>       // For exit()

// Function to perform Bubble Sort
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size(); // Get the size of the array
    // Outer loop for the passes
    for (int i = 0; i < n - 1; ++i) {
        // Inner loop for comparing and swapping adjacent elements
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) { // If elements are out of order, swap them
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Function to perform Insertion Sort
void insertionSort(std::vector<int>& arr) {
    int n = arr.size(); // Get the size of the array
    // Start from the second element
    for (int i = 1; i < n; ++i) {
        int key = arr[i]; // The element to be inserted
        int j = i - 1;    // Start from the previous element
        // Shift elements to the right to make space for the key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // Insert the key at the correct position
    }
}

int main() {
    std::vector<int> numbers; // Vector to store input numbers
    int num;

    // Prompt the user to enter integers
    std::cout << "Enter integers to sort (enter any non-integer to stop): " << std::endl;
    // Continuously read numbers until a non-integer is entered
    while (std::cin >> num) {
        numbers.push_back(num); // Add the number to the vector
    }

    pid_t pid = fork(); // Create a new process using fork()

    if (pid < 0) {
        // If fork() fails, print an error message and exit
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }
    else if (pid == 0) {
        // Code executed by the child process
        std::cout << "Child process started, PID: " << getpid() << std::endl;
        // Perform Insertion Sort in the child process
        insertionSort(numbers);
        std::cout << "Child process (sorted using Insertion Sort): ";
        for (int n : numbers) {
            std::cout << n << " "; // Print the sorted array
        }
        std::cout << std::endl;

        // Simulate a delay to keep the child process running longer
        sleep(10);
        std::cout << "Child process finished." << std::endl;
        exit(0); // Exit the child process
    }
    else {
        // Code executed by the parent process
        std::cout << "Parent process started, PID: " << getpid() << std::endl;
        // Perform Bubble Sort in the parent process
        bubbleSort(numbers);
        std::cout << "Parent process (sorted using Bubble Sort): ";
        for (int n : numbers) {
            std::cout << n << " "; // Print the sorted array
        }
        std::cout << std::endl;

        // Simulate the zombie state by sleeping before cleaning up the child process
        std::cout << "Parent process sleeping to create a zombie state." << std::endl;
        sleep(5);

        // Wait for the child process to finish and clean it up
        wait(NULL);

        std::cout << "Parent process finished, child process should be reaped now." << std::endl;

        // Simulate the parent exiting early to demonstrate the orphan state
        std::cout << "Parent process exiting, leaving child as orphan if it's still running." << std::endl;
        exit(0); // Exit the parent process
    }

    return 0; // Program ends
}
// Another valid input format (one integer per line):
// 5
// 2
// 9
// 1
// 7
// End with any alphabet