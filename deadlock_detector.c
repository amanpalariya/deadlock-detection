#include "deadlock_detector.h"

#include <stdio.h>
#include <stdlib.h>

#include "ds.h"

bool* get_bool_array(int length) {
    return (bool*)malloc(sizeof(bool) * length);
}

bool can_thread_be_completed(struct minimal_resource_state* state, int thread_index) {
    for (int i = 0; i < state->n; i++) {
        if (state->request[thread_index][i] > state->available[i]) return false;
    }
    return true;
}

bool is_allocation_nonzero(struct minimal_resource_state* state, int thread_index) {
    for (int i = 0; i < state->n; i++) {
        if (state->allocation[thread_index][i] != 0) return true;
    }
    return false;
}

void deallocate_thread(struct minimal_resource_state* state, int thread_index) {
    for (int i = 0; i < state->n; i++) {
        state->request[thread_index][i] = 0;
        state->available[i] += state->allocation[thread_index][i];
        state->allocation[thread_index][i] = 0;
    }
}

bool* get_threads_involved_in_deadlock(struct minimal_resource_state* state, bool should_print) {
    if (should_print) {
        printf("Request");
        printf("\n");
        for (int i = 0; i < state->m; i++) {
            for (int j = 0; j < state->n; j++) {
                printf("%d ", state->request[i][j]);
            }
            printf("\n");
        }
        printf("Allocation");
        printf("\n");
        for (int i = 0; i < state->m; i++) {
            for (int j = 0; j < state->n; j++) {
                printf("%d ", state->allocation[i][j]);
            }
            printf("\n");
        }
        printf("Available");
        printf("\n");
        for (int j = 0; j < state->n; j++) {
            printf("%d ", state->available[j]);
        }
        printf("\n");
    }
    bool* marked = get_bool_array(state->m);
    for (int i = 0; i < state->m; i++) {
        marked[i] = is_allocation_nonzero(state, i);
    }
    bool progress = true;
    while (progress) {
        progress = false;
        for (int i = 0; i < state->m; i++) {
            if (!marked[i]) continue;
            if (can_thread_be_completed(state, i)) {
                deallocate_thread(state, i);
                progress = true;
                marked[i] = false;
            }
        }
    }
    free_minimal_state(state);
    return marked;
}