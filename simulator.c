#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

#include "deadlock_detector.h"
#include "ds.h"
#include "logger.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

struct run_thread_args {
    struct resource_state* state;
    int thread_index;
    int d;
};

struct deadlock_detection_thread_args {
    struct resource_state* state;
    int d;
    enum preemption_heuristic heuristic;
    long* time_diff_in_micros;
    int* number_of_deadlocks;
};

struct run_thread_args* get_run_thread_args(struct resource_state* state, int thread_index, int d) {
    struct run_thread_args* args = (struct run_thread_args*)malloc(sizeof(struct run_thread_args));
    args->state = state;
    args->thread_index = thread_index;
    args->d = d;
    return args;
}

struct deadlock_detection_thread_args* get_deadlock_detection_thread_args(struct resource_state* state, int d, enum preemption_heuristic heuristic, long* time_diff_in_micros, int* number_of_deadlocks) {
    struct deadlock_detection_thread_args* args = (struct deadlock_detection_thread_args*)malloc(sizeof(struct deadlock_detection_thread_args));
    args->state = state;
    args->d = d;
    args->heuristic = heuristic;
    args->time_diff_in_micros = time_diff_in_micros;
    args->number_of_deadlocks = number_of_deadlocks;
    return args;
}

int randint(int min, int max) {
    return min + rand() % (max - min + 1);
}

int* generate_random_requirement(int n, int* max_resources) {
    int* requirement = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        if (randint(0, 1) == 0) {
            requirement[i] = randint(0, max_resources[i]);
        } else {
            requirement[i] = 0;
        }
    }
    return requirement;
}

int number_of_required_resources(int* requirement, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (requirement[i] != 0) count++;
    }
    return count;
}

int choose_random_resource_from_required_resources(int* requirement, int n, int required_resources) {
    int resource_number_among_required_resources = randint(1, required_resources);
    for (int i = 0; i < n; i++) {
        if (requirement[i] != 0) resource_number_among_required_resources--;
        if (resource_number_among_required_resources == 0) {
            return i;
        }
    }
}

int get_random_number_of_instances(int* requirement, int resource_index) {
    int r = randint(1, (int)(1.5f * requirement[resource_index]));
    return r <= requirement[resource_index] ? r : requirement[resource_index];
}

bool claim_resources(struct resource_state* state, int thread_index, int resource_index) {
    int curr_allocation = 0;
    if (state->available[resource_index] >= state->request[thread_index][resource_index]) {
        curr_allocation = state->request[thread_index][resource_index];
    } else {
        // curr_allocation = state->available[resource_index]; // Uncomment this line to allocate partial requests
        curr_allocation = 0;
    }
    allocate_from_request(state, thread_index, resource_index, curr_allocation);
    return state->request[thread_index][resource_index] == 0;
}

bool should_terminate(struct resource_state* state, int thread_index) {
    lock_state(state);
    bool retval = state->should_terminate[thread_index];
    unlock_state(state);
    return retval;
}

void free_all_resources(struct resource_state* state, int thread_index) {
    lock_state(state);
    for (int i = 0; i < state->n; i++) {
        free_resource_from_thread(state, thread_index, i);
        cond_signal(state, i);
    }
    state->should_terminate[thread_index] = false;
    unlock_state(state);
}

void* run_thread(void* args) {
    struct run_thread_args* _args = (struct run_thread_args*)args;
    struct resource_state* state = _args->state;
    int thread_index = _args->thread_index;
    int d = _args->d;
    while (true) {
        // Decide random requirement
        log_info("[%d] Deciding requirement", thread_index);
        int* requirement = generate_random_requirement(state->n, state->resource);
        int required_resources = number_of_required_resources(requirement, state->n);
        lock_state(state);
        log_info("[%d] Printing requirement", thread_index);
        for (int i = 0; i < state->n; i++) {
            log_info("[%d] Res [%d] = %d", thread_index, i, requirement[i]);
        }
        unlock_state(state);
        while (required_resources > 0 && !should_terminate(state, thread_index)) {
            if (randint(0, 2) == 0) {
                log_info("[%d] Sleeping", thread_index);
                usleep(randint(10000, 1000000));
                continue;
            }
            // Generate random request
            int resource_index = choose_random_resource_from_required_resources(requirement, state->n, required_resources);
            int number_of_instances = get_random_number_of_instances(requirement, resource_index);
            log_info("[%d] Request of res %d x %d, currently have %d", thread_index, resource_index, number_of_instances, state->available[resource_index]);

            lock_state(state);
            state->request[thread_index][resource_index] += number_of_instances;
            while (!state->should_terminate[thread_index] && !claim_resources(state, thread_index, resource_index)) {
                cond_wait(state, resource_index);
            }
            unlock_state(state);

            requirement[resource_index] -= number_of_instances;
            required_resources = number_of_required_resources(requirement, state->n);
        }
        log_info("[%d] Freeing all resources", thread_index);
        free_all_resources(state, thread_index);
        int time = randint((int)(0.7f * d), (int)(1.5f * d));
        log_info("[%d] Sleeping for %d", thread_index, time);
        usleep(time);
    }
}

void preempt_thread(struct resource_state* state, int thread_index) {
    state->should_terminate[thread_index] = true;
    for (int i = 0; i < state->n; i++) cond_signal(state, i);
}

int total_allocation(struct resource_state* state, int thread_index) {
    int ans = 0;
    for (int i = 0; i < state->n; i++) {
        ans += state->allocation[thread_index][i];
    }
    return ans;
}

int max_allocation(struct resource_state* state, int thread_index) {
    int ans = 0;
    for (int i = 0; i < state->n; i++) {
        ans = max(ans, state->allocation[thread_index][i]);
    }
    return ans;
}

int min_allocation(struct resource_state* state, int thread_index) {
    int ans = -1;
    for (int i = 0; i < state->n; i++) {
        int alloc = state->allocation[thread_index][i];
        if (alloc != 0) {
            if (ans == -1) {
                ans = alloc;
            } else {
                ans = min(ans, state->allocation[thread_index][i]);
            }
        }
    }
    return ans;
}

int number_of_allocation(struct resource_state* state, int thread_index) {
    int ans = 0;
    for (int i = 0; i < state->n; i++) {
        ans += state->allocation[thread_index][i] != 0;
    }
    return ans;
}

int max_total_allocation(struct resource_state* state, bool* is_thread_deadlocked) {
    int ans = -1;
    int param = -1;
    for (int i = 0; i < state->m; i++) {
        if (is_thread_deadlocked[i]) {
            int param_i = total_allocation(state, i);
            if (ans == -1) {
                ans = i;
                param = param_i;
            } else if (param_i > param) {
                ans = i;
                param = param_i;
            }
        }
    }
    return ans;
}

int min_total_allocation(struct resource_state* state, bool* is_thread_deadlocked) {
    int ans = -1;
    int param = -1;
    for (int i = 0; i < state->m; i++) {
        if (is_thread_deadlocked[i]) {
            int param_i = total_allocation(state, i);
            if (ans == -1) {
                ans = i;
                param = param_i;
            } else if (param_i < param) {
                ans = i;
                param = param_i;
            }
        }
    }
    return ans;
}

int max_max_allocation(struct resource_state* state, bool* is_thread_deadlocked) {
    int ans = -1;
    int param = -1;
    for (int i = 0; i < state->m; i++) {
        if (is_thread_deadlocked[i]) {
            int param_i = max_allocation(state, i);
            if (ans == -1) {
                ans = i;
                param = param_i;
            } else if (param_i > param) {
                ans = i;
                param = param_i;
            }
        }
    }
    return ans;
}

int min_min_allocation(struct resource_state* state, bool* is_thread_deadlocked) {
    int ans = -1;
    int param = -1;
    for (int i = 0; i < state->m; i++) {
        if (is_thread_deadlocked[i]) {
            int param_i = min_allocation(state, i);
            if (ans == -1) {
                ans = i;
                param = param_i;
            } else if (param_i < param) {
                ans = i;
                param = param_i;
            }
        }
    }
    return ans;
}

int max_number_of_allocation(struct resource_state* state, bool* is_thread_deadlocked) {
    int ans = -1;
    int param = -1;
    for (int i = 0; i < state->m; i++) {
        if (is_thread_deadlocked[i]) {
            int param_i = number_of_allocation(state, i);
            if (ans == -1) {
                ans = i;
                param = param_i;
            } else if (param_i > param) {
                ans = i;
                param = param_i;
            }
        }
    }
    return ans;
}

int min_number_of_allocation(struct resource_state* state, bool* is_thread_deadlocked) {
    int ans = -1;
    int param = -1;
    for (int i = 0; i < state->m; i++) {
        if (is_thread_deadlocked[i]) {
            int param_i = number_of_allocation(state, i);
            if (ans == -1) {
                ans = i;
                param = param_i;
            } else if (param_i < param) {
                ans = i;
                param = param_i;
            }
        }
    }
    return ans;
}

int get_thread_to_preempt(struct resource_state* state, bool* is_thread_deadlocked, enum preemption_heuristic heuristic) {
    switch (heuristic) {
        case MAX_TOTAL_ALLOCATION:
            return max_total_allocation(state, is_thread_deadlocked);
            break;
        case MIN_TOTAL_ALLOCATION:
            return min_total_allocation(state, is_thread_deadlocked);
            break;
        case MAX_MAX_ALLOCATION:
            return max_max_allocation(state, is_thread_deadlocked);
            break;
        case MIN_MIN_ALLOCATION:
            return min_min_allocation(state, is_thread_deadlocked);
            break;
        case MAX_NUMBER_OF_ALLOCATION:
            return max_number_of_allocation(state, is_thread_deadlocked);
            break;
        case MIN_NUMBER_OF_ALLOCATION:
            return min_number_of_allocation(state, is_thread_deadlocked);
            break;
    }
}

struct timeval get_curr_time() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return t;
}

long get_time_diff_in_millis(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
}

void* deadlock_detection_thread(void* args) {
    struct deadlock_detection_thread_args* _args = (struct deadlock_detection_thread_args*)args;
    struct resource_state* state = _args->state;
    enum preemption_heuristic heuristic = _args->heuristic;
    long* time_diff_in_micros = _args->time_diff_in_micros;
    int* number_of_deadlocks = _args->number_of_deadlocks;
    int d = _args->d;
    struct timeval start, stop;
    start = get_curr_time();
    while (true) {
        usleep(d);
        lock_state(state);
        stop = get_curr_time();
        log_info("DETECTING DEADLOCK...");
        bool* is_thread_deadlocked = get_threads_involved_in_deadlock(get_copied_minimal_state(state));
        bool is_deadlocked = false;
        for (int i = 0; i < state->m; i++) {
            if (is_thread_deadlocked[i]) {
                is_deadlocked = true;
                break;
            }
        }
        if (is_deadlocked) {
            log_info("DEADLOCK PRESENT");
            for (int i = 0; i < state->m; i++) {
                if (is_thread_deadlocked[i]) {
                    printf("%d ", i);
                }
            }
            printf("\n");
            // Find a thread to preempt using given heuristics
            int thread_index_to_preempt = get_thread_to_preempt(state, is_thread_deadlocked, heuristic);
            log_info("Preempting thread %d", thread_index_to_preempt);
            preempt_thread(state, thread_index_to_preempt);

            *time_diff_in_micros += get_time_diff_in_millis(start, stop);
            *number_of_deadlocks += 1;
            start = get_curr_time();
        } else {
            log_info("NO DEADLOCK");
        }
        unlock_state(state);
    }
}

void run(struct resource_state* state, int d, enum preemption_heuristic heuristic, long* time_diff_in_micros, int* number_of_deadlocks) {
    pthread_t thread_id[state->m];
    pthread_t deadlock_detection_thread_id;
    for (int i = 0; i < state->m; i++) {
        pthread_create(&thread_id[i], NULL, run_thread, get_run_thread_args(state, i, d));
    }
    pthread_create(&deadlock_detection_thread_id, NULL, deadlock_detection_thread, get_deadlock_detection_thread_args(state, d, heuristic, time_diff_in_micros, number_of_deadlocks));
    // pthread_join(deadlock_detection_thread_id, NULL);
}