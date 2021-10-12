#include "ds.h"

#include <stdbool.h>
#include <stdlib.h>

int* get_1d_int_array(int length) {
    return (int*)malloc(sizeof(int) * length);
}

int** get_2d_int_array(int rows, int columns) {
    int** array = (int**)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        array[i] = get_1d_int_array(columns);
    }
    return array;
}

struct resource_state* get_new_empty_resource_state(int n, int m) {
    struct resource_state* state = (struct resource_state*)malloc(sizeof(struct resource_state));
    state->n = n;
    state->m = m;
    state->request = get_2d_int_array(m, n);
    state->allocation = get_2d_int_array(m, n);
    state->resource = get_1d_int_array(n);
    state->available = get_1d_int_array(n);
    state->should_terminate = (bool*)malloc(sizeof(bool) * m);
    state->condition = (pthread_cond_t*)malloc(sizeof(pthread_cond_t) * n);
    pthread_mutex_init(&state->mutex, NULL);
    return state;
}

struct minimal_resource_state* get_new_empty_minimal_resource_state(int n, int m) {
    struct minimal_resource_state* state = (struct minimal_resource_state*)malloc(sizeof(struct minimal_resource_state));
    state->n = n;
    state->m = m;
    state->request = get_2d_int_array(m, n);
    state->allocation = get_2d_int_array(m, n);
    state->resource = get_1d_int_array(n);
    state->available = get_1d_int_array(n);
    return state;
}

void update_request(struct resource_state* state, int thread_index, int resource_index, int value) {
    state->request[thread_index][resource_index] = value;
}

void allocate_from_request(struct resource_state* state, int thread_index, int resource_index, int allocation_value) {
    state->request[thread_index][resource_index] -= allocation_value;
    state->allocation[thread_index][resource_index] += allocation_value;
    state->available[resource_index] -= allocation_value;
}

void free_resource_from_thread(struct resource_state* state, int thread_index, int resource_index) {
    state->request[thread_index][resource_index] = 0;
    state->available[resource_index] += state->allocation[thread_index][resource_index];
    state->allocation[thread_index][resource_index] = 0;
}

void cond_wait(struct resource_state* state, int resource_index) {
    pthread_cond_wait(&state->condition[resource_index], &state->mutex);
}

void cond_signal(struct resource_state* state, int resource_index) {
    pthread_cond_signal(&state->condition[resource_index]);
}

void lock_state(struct resource_state* state) {
    pthread_mutex_lock(&state->mutex);
}

void unlock_state(struct resource_state* state) {
    pthread_mutex_unlock(&state->mutex);
}

struct minimal_resource_state* get_copied_minimal_state(struct resource_state* state) {
    struct minimal_resource_state* copy = get_new_empty_minimal_resource_state(state->n, state->m);
    for (int i = 0; i < copy->n; i++) {
        copy->resource[i] = state->resource[i];
        copy->available[i] = state->available[i];
        for (int j = 0; j < copy->m; j++) {
            copy->request[j][i] = state->request[j][i];
            copy->allocation[j][i] = state->allocation[j][i];
        }
    }
    return copy;
}

void free_state(struct resource_state* state) {
    for (int i = 0; i < state->m; i++) {
        free(state->request[i]);
        free(state->allocation[i]);
    }
    free(state->resource);
    free(state->available);
    free(state->condition);
    free(state->should_terminate);
    free(state);
}

void free_minimal_state(struct minimal_resource_state* state) {
    for (int i = 0; i < state->m; i++) {
        free(state->request[i]);
        free(state->allocation[i]);
    }
    free(state->resource);
    free(state->available);
    free(state);
}