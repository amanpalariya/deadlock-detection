#include "deadlock_detector.h"

#include <stdio.h>
#include <stdlib.h>

#include "ds.h"

bool* get_all_true_bool_array(int length) {
    bool* array = (bool*)malloc(sizeof(bool) * length);
    for (int i = 0; i < length; i++) {
        array[i] = true;
    }
    return array;
}

bool can_thread_be_completed(struct minimal_resource_state* state, int thread_index) {
    for (int i = 0; i < state->n; i++) {
        if (state->request[thread_index][i] > state->available[i]) return false;
    }
    return true;
}

void deallocate_thread(struct minimal_resource_state* state, int thread_index) {
    for (int i = 0; i < state->n; i++) {
        state->request[thread_index][i] = 0;
        state->available[i] += state->allocation[thread_index][i];
        state->allocation[thread_index][i] = 0;
    }
}

bool* get_threads_involved_in_deadlock(struct minimal_resource_state* state) {
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
    bool* marked = get_all_true_bool_array(state->m);
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
    return marked;
}