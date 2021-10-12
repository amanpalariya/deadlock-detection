#ifndef CS303_DEADLOCK_DETECTOR_H
#define CS303_DEADLOCK_DETECTOR_H

#include <stdbool.h>

#include "ds.h"

bool* get_threads_involved_in_deadlock(struct minimal_resource_state* state, bool should_print);

#endif