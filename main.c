#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds.h"
#include "logger.h"
#include "simulator.h"

long time_diff_in_micros = 0;
int number_of_deadlocks = 0;

void before_exit() {
    printf("\n\n");
    if (number_of_deadlocks == 0) {
        printf("No deadlock detected so far...\n");
    } else {
        printf("Detected deadlocks %d times\nAverage deadlock interval: %.2f ms\n", number_of_deadlocks, (time_diff_in_micros / 1000.0f) / number_of_deadlocks);
    }
}

int main(int argc, char** argv) {
    int n, m, d;
    enum preemption_heuristic heuristic;
    scanf("%d %d %d %d", &n, &m, &d, (int*)&heuristic);
    if (n <= 0 || m <= 0 || d <= 0) {
        printf("Please provide positive values for n, m, and d (got n=%d, m=%d, and d=%d)", n, m, d);
        return 0;
    }
    if (heuristic < 0 || heuristic > 5) {
        printf("Heuristic must be in range [0, 5] (got %d)", heuristic);
        return 0;
    }
    struct resource_state* state = get_new_empty_resource_state(n, m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &state->resource[i]);
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
    srand(time(NULL));
    printf("Starting simulation with following configuration\n");
    printf("Resources: %d [", state->n);
    int i = 0;
    for (; i < (state->n - 1); i++) {
        printf("%d, ", state->resource[i]);
    }
    printf("%d]\n", state->resource[i]);
    printf("Number of threads: %d\n", state->m);
    printf("Deadlock detection interval: %dms\n", d);
    printf("Preemption heuristic: ");
    switch (heuristic) {
        case MAX_TOTAL_ALLOCATION:
            printf("Max total allocation");
            break;
        case MIN_TOTAL_ALLOCATION:
            printf("Min total allocation");
            break;
        case MAX_MAX_ALLOCATION:
            printf("Max max allocation");
            break;
        case MIN_MIN_ALLOCATION:
            printf("Min min allocation");
            break;
        case MAX_NUMBER_OF_ALLOCATION:
            printf("Max number of allocation");
            break;
        case MIN_NUMBER_OF_ALLOCATION:
            printf("Min number of allocation");
            break;
    }
    printf("\n");
    printf("\n");
    atexit(before_exit);
    run(state, d * 1000, heuristic, &time_diff_in_micros, &number_of_deadlocks);
    while (getc(stdin) != EOF)
        ;
    return 0;
}