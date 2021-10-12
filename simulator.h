#ifndef CS303_SIMULATOR_H
#define CS303_SIMULATOR_H

#include "ds.h"

void run(struct resource_state* state, int d, enum preemption_heuristic heuristic, long* time_diff_in_micros, int* number_of_deadlocks);

#endif
