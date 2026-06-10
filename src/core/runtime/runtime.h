#pragma once 

#include "core_config.h"

/**
 * @brief superloop function call
 * @brief processes realtime, event handlers and background
 */

bool runtime_init();

void runtime_run_once();

