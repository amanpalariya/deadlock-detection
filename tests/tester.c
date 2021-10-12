#include <stdbool.h>
#include <stdio.h>

#include "../deadlock_detector.h"
#include "../ds.h"

int total_tests = 0;
int passed_tests = 0;
int failed_tests = 0;

void test_log(char* test_name, bool success) {
    total_tests++;
    if (success) {
        printf("\033[0;32m[✓]: %s\033[0m\n", test_name);
        passed_tests++;
    } else {
        printf("\033[0;31m[ ]: %s\033[0m\n", test_name);
        failed_tests++;
    }
}

void print_test_section(char* section) {
    printf("\n\033[0;1m%s\033[0m\n\n", section);
}

void test_ds() {
    int n = 2, m = 2;
    struct resource_state* state = get_new_empty_resource_state(n, m);
    for (int i = 0; i < n; i++) {
        state->resource[i] = i + 1;
        state->available[i] = state->resource[i];
    }
    for (int i = 0; i < m; i++) {
        state->should_terminate[i] = false;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            state->request[j][i] = 0;
            state->allocation[j][i] = 0;
        }
    }
    test_log("Initialize state (resource)", state->resource[0] == 1 && state->resource[1] == 2);
    test_log("Initialize state (available)", state->resource[0] == state->available[0] && state->resource[1] == state->resource[1]);
    test_log("Initialize state (should_terminate)", state->should_terminate[0] == false && state->should_terminate[1] == false);
    test_log("Initialize state (request)", state->request[0][0] == 0 && state->request[0][1] == 0 && state->request[1][0] == 0 && state->request[1][1] == 0);
    test_log("Initialize state (allocation)", state->allocation[0][0] == 0 && state->allocation[0][1] == 0 && state->allocation[1][0] == 0 && state->allocation[1][1] == 0);

    update_request(state, 0, 0, 10);
    test_log("(1/3) Update request", state->request[0][0] == 10 && state->request[0][1] == 0 && state->request[1][0] == 0 && state->request[1][1] == 0);
    update_request(state, 0, 1, 3);
    test_log("(2/3) Update request", state->request[0][0] == 10 && state->request[0][1] == 3 && state->request[1][0] == 0 && state->request[1][1] == 0);
    update_request(state, 0, 1, 7);
    test_log("(3/3) Update request", state->request[0][0] == 10 && state->request[0][1] == 7 && state->request[1][0] == 0 && state->request[1][1] == 0);

    allocate_from_request(state, 0, 0, 5);
    test_log("(1/2) Allocate from request", state->request[0][0] == 5 && state->allocation[0][0] == 5 && state->available[0] == -4);
    allocate_from_request(state, 0, 1, 1);
    test_log("(2/2) Allocate from request", state->request[0][1] == 6 && state->allocation[0][1] == 1 && state->available[1] == 1);

    free_resource_from_thread(state, 0, 0);
    test_log("(1/2) Free resources from thread", state->request[0][0] == 0 && state->allocation[0][0] == 0 && state->available[0] == 1);
    free_resource_from_thread(state, 0, 1);
    test_log("(1/2) Free resources from thread", state->request[0][1] == 0 && state->allocation[0][1] == 0 && state->available[1] == 2);
}

void test_deadlock_detector() {
    int n = 2, m = 2;
    struct resource_state* state = get_new_empty_resource_state(n, m);
    for (int i = 0; i < n; i++) {
        state->resource[i] = 2;
        state->available[i] = state->resource[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            state->request[j][i] = 0;
            state->allocation[j][i] = 0;
        }
    }

    bool* deadlock;
    deadlock = get_threads_involved_in_deadlock(get_copied_minimal_state(state), false);
    test_log("No deadlock", deadlock[0] == false && deadlock[1] == false);

    state->allocation[0][0] = 2;
    state->allocation[1][1] = 2;
    state->request[0][1] = 1;
    state->request[1][0] = 1;
    state->available[0] = 0;
    state->available[1] = 0;
    deadlock = get_threads_involved_in_deadlock(get_copied_minimal_state(state), false);
    test_log("Deadlock detected", deadlock[0] == true && deadlock[1] == true);
}

int main(int argc, char** argv) {
    print_test_section("Testing data structures");
    test_ds();

    print_test_section("Testing deadlock detection logic");
    test_deadlock_detector();

    printf("\n%d/%d tests passed\n", passed_tests, total_tests);
    return 0;
}