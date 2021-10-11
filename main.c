#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ds.h"
#include "logger.h"
#include "simulator.h"

int main(int argc, char** argv) {
    int n = 4;
    int total_resources[4] = {1, 2, 1, 2};
    int m = 10;
    int d = 1000000;
    struct resource_state* state = get_new_empty_resource_state(n, m);
    for (int i = 0; i < n; i++) {
        state->resource[i] = total_resources[i];
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
    run(state, d);
    getc(stdin);
    return 0;
}