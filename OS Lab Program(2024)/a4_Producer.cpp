#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // for sleep

#define BUFFER_SIZE 5

// Shared buffer
int buffer[BUFFER_SIZE];
int in = 0; // Points to the next empty slot in the buffer
int out = 0; // Points to the next full slot in the buffer

// Semaphore declarations
sem_t empty_slots; // Counts the number of empty slots in the buffer
sem_t full_slots;  // Counts the number of full slots in the buffer

// Mutex declaration for critical section
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (true) {
        // Produce an item
        item = rand() % 100;
        sem_wait(&empty_slots); // Wait for an empty slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Critical section: adding item to buffer
        buffer[in] = item;
        std::cout << "Produced: " << item << " at index " << in << std::endl;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Leave critical section
        sem_post(&full_slots); // Signal that there's a full slot

        sleep(1); // Sleep to simulate time taken for production
    }
}

void* consumer(void* arg) {
    int item;
    while (true) {
        sem_wait(&full_slots); // Wait for a full slot
        pthread_mutex_lock(&mutex); // Enter critical section

        // Critical section: removing item from buffer
        item = buffer[out];
        std::cout << "Consumed: " << item << " from index " << out << std::endl;
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Leave critical section
        sem_post(&empty_slots); // Signal that there's an empty slot

        sleep(2); // Sleep to simulate time taken for consumption
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphore and mutex
    sem_init(&empty_slots, 0, BUFFER_SIZE); // Initially, all slots are empty
    sem_init(&full_slots, 0, 0); // Initially, no slots are full
    pthread_mutex_init(&mutex, nullptr);

    // Create producer and consumer threads
    pthread_create(&prod_thread, nullptr, producer, nullptr);
    pthread_create(&cons_thread, nullptr, consumer, nullptr);

    // Wait for the threads to complete (they won't in this example)
    pthread_join(prod_thread, nullptr);
    pthread_join(cons_thread, nullptr);

    // Clean up
    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
