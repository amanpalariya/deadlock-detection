#ifndef CS303_DS_H
#define CS303_DS_H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

enum preemption_heuristic {
    MAX_TOTAL_ALLOCATION,
    MIN_TOTAL_ALLOCATION,
    MAX_MAX_ALLOCATION,
    MIN_MIN_ALLOCATION,
    MAX_NUMBER_OF_ALLOCATION,
    MIN_NUMBER_OF_ALLOCATION,
};

struct resource_state {
    int n;             // [READ ONLY] Number of types of resources
    int m;             // [READ ONLY] Number of threads
    int** request;     // Current pending resource requests
    int** allocation;  // Current allocated resources
    int* resource;     // [READ ONLY] Total resources
    int* available;    // Available resources
    bool* should_terminate;
    pthread_cond_t* condition;
    pthread_mutex_t mutex;
};

struct minimal_resource_state {
    int n;             // [READ ONLY] Number of types of resources
    int m;             // [READ ONLY] Number of threads
    int** request;     // Current pending resource requests
    int** allocation;  // Current allocated resources
    int* resource;     // [READ ONLY] Total resources
    int* available;    // Available resources
};

struct resource_state* get_new_empty_resource_state(int n, int m);

void update_request(struct resource_state* state, int thread_index, int resource_index, int value);

void allocate_from_request(struct resource_state* state, int thread_index, int resource_index, int allocation_value);

void free_resource_from_thread(struct resource_state* state, int thread_index, int resource_index);

void cond_wait(struct resource_state* state, int resource_index);

void cond_signal(struct resource_state* state, int resource_index);

void lock_state(struct resource_state* state);

void unlock_state(struct resource_state* state);

struct minimal_resource_state* get_copied_minimal_state(struct resource_state* state);

#endif