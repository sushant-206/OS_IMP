#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Mutexes to manage synchronization
pthread_mutex_t mutex;       // To lock access to the read_count
pthread_mutex_t write_lock;  // To give exclusive access to writers
int read_count = 0;          // Track the number of active readers

// Function for reader threads
void *reader(void *arg) {
    int reader_id = *((int *)arg);  // Get the reader ID
    
    while (1) {
        // Reader Entry Section
        pthread_mutex_lock(&mutex);  // Lock mutex to safely update read_count
        read_count++;  // Increment the read count
        
        if (read_count == 1) {
            pthread_mutex_lock(&write_lock);  // First reader locks the writer
        }
        pthread_mutex_unlock(&mutex);  // Unlock mutex after updating read_count

        // Reading section (Critical Section)
        printf("Reader %d is reading\n", reader_id);
        sleep(rand() % 3);  // Simulate reading time

        // Reader Exit Section
        pthread_mutex_lock(&mutex);  // Lock mutex to safely update read_count
        read_count--;  // Decrement read count
        if (read_count == 0) {
            pthread_mutex_unlock(&write_lock);  // Last reader unlocks the writer
        }
        pthread_mutex_unlock(&mutex);  // Unlock mutex after updating read_count

        sleep(1);  // Sleep to allow other threads to execute
    }
}

// Function for writer threads
void *writer(void *arg) {
    int writer_id = *((int *)arg);  // Get the writer ID
    
    while (1) {
        // Writer Entry Section
        pthread_mutex_lock(&write_lock);  // Lock write_lock to get exclusive access

        // Writing section (Critical Section)
        printf("Writer %d is writing\n", writer_id);
        sleep(rand() % 3);  // Simulate writing time

        // Writer Exit Section
        pthread_mutex_unlock(&write_lock);  // Unlock write_lock after writing

        sleep(1);  // Sleep to allow other threads to execute
    }
}

int main() {
    pthread_t readers[5], writers[3];  // Arrays to store reader and writer thread IDs
    int reader_ids[5], writer_ids[3];  // Arrays to store reader and writer IDs
    
    // Initialize mutexes
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&write_lock, NULL);
    
    // Create 5 reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create 3 writer threads
    for (int i = 0; i < 3; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join all threads (optional in this case, as threads run indefinitely)
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy mutexes to clean up
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&write_lock);

    return 0;  // End the program
}
