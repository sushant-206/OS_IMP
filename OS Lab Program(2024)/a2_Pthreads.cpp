#include <iostream> // For input/output operations
#include <pthread.h> // For using POSIX threads
#include <vector> // For using the vector container

#define SIZE 3 // Define the size of the matrix (3x3)

// Define the matrices and result matrix as global variables with size (SIZE x SIZE)
std::vector<std::vector<int>> matrix1(SIZE, std::vector<int>(SIZE)); // Matrix 1
std::vector<std::vector<int>> matrix2(SIZE, std::vector<int>(SIZE)); // Matrix 2
std::vector<std::vector<int>> result(SIZE, std::vector<int>(SIZE)); // Resultant matrix

// Structure to hold row and column data for a thread
struct ThreadData {
    int row; // Row index
    int col; // Column index
};

// Function to perform matrix addition
void* add(void* arg) {
    ThreadData* data = (ThreadData*)arg; // Cast argument to ThreadData pointer
    // Perform addition for the specified cell
    result[data->row][data->col] = matrix1[data->row][data->col] + matrix2[data->row][data->col];
    delete data; // Free dynamically allocated memory for thread data
    return NULL; // Return null as the thread result
}

// Function to perform matrix subtraction
void* subtract(void* arg) {
    ThreadData* data = (ThreadData*)arg; // Cast argument to ThreadData pointer
    // Perform subtraction for the specified cell
    result[data->row][data->col] = matrix1[data->row][data->col] - matrix2[data->row][data->col];
    delete data; // Free dynamically allocated memory for thread data
    return NULL; // Return null as the thread result
}

// Function to perform matrix multiplication
void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg; // Cast argument to ThreadData pointer
    result[data->row][data->col] = 0; // Initialize result cell to 0
    // Calculate the multiplication for the cell
    for (int k = 0; k < SIZE; ++k) {
        result[data->row][data->col] += matrix1[data->row][k] * matrix2[k][data->col];
    }
    delete data; // Free dynamically allocated memory for thread data
    return NULL; // Return null as the thread result
}

// Function to perform matrix division
void* divide(void* arg) {
    ThreadData* data = (ThreadData*)arg; // Cast argument to ThreadData pointer
    // Perform division only if the divisor is not zero
    if (matrix2[data->row][data->col] != 0) {
        result[data->row][data->col] = matrix1[data->row][data->col] / matrix2[data->row][data->col];
    } else {
        result[data->row][data->col] = 0; // Handle division by zero by setting result to 0
    }
    delete data; // Free dynamically allocated memory for thread data
    return NULL; // Return null as the thread result
}

// Function to print a matrix
void print_matrix(const std::vector<std::vector<int>>& mat) {
    for (int i = 0; i < SIZE; ++i) { // Iterate over rows
        for (int j = 0; j < SIZE; ++j) { // Iterate over columns
            std::cout << mat[i][j] << " "; // Print each element
        }
        std::cout << std::endl; // Print a newline after each row
    }
}

int main() {
    pthread_t threads[SIZE][SIZE]; // Create an array of threads for each cell in the matrix

    // Take input for Matrix 1
    std::cout << "Enter elements for Matrix 1 (" << SIZE << "x" << SIZE << "):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cin >> matrix1[i][j]; // Read each element of Matrix 1
        }
    }

    // Take input for Matrix 2
    std::cout << "Enter elements for Matrix 2 (" << SIZE << "x" << SIZE << "):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cin >> matrix2[i][j]; // Read each element of Matrix 2
        }
    }

    // Perform addition
    std::cout << "Performing Addition:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            // Create thread data for each cell
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, add, (void*)data); // Create a thread
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL); // Wait for all threads to finish
        }
    }
    print_matrix(result); // Print the addition result

    // Perform subtraction
    std::cout << "Performing Subtraction:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, subtract, (void*)data);
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }
    print_matrix(result); // Print the subtraction result

    // Perform multiplication
    std::cout << "Performing Multiplication:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, multiply, (void*)data);
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }
    print_matrix(result); // Print the multiplication result

    // Perform division
    std::cout << "Performing Division:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, divide, (void*)data);
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }
    print_matrix(result); // Print the division result

    return 0; // Exit successfully
}
// Example input for Matrix 1 (3x3):
// 1 2 3
// 4 5 6
// 7 8 9
// This represents:
// Matrix 1 = [
//     [1, 2, 3],
//     [4, 5, 6],
//     [7, 8, 9]
// ]

// Example input for Matrix 2 (3x3):
// 9 8 7
// 6 5 4
// 3 2 1
// This represents:
// Matrix 2 = [
//     [9, 8, 7],
//     [6, 5, 4],
//     [3, 2, 1]
// ]
