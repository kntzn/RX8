#pragma once
#include <stm32f303xc.h>

#define IRQ_LOCK for (uint32_t _lock_primask = __get_PRIMASK (), _lock_once = (__disable_irq(), 0u); !_lock_once; _lock_once = 1u, __set_PRIMASK (_lock_primask))

#define STATIC_ASSERT_CONCAT(a, b) a##b
#define STATIC_ASSERT_NAME(line) STATIC_ASSERT_CONCAT(static_assert_global_, line)
#define STATIC_ASSERT(condition) \
    typedef char STATIC_ASSERT_NAME(__LINE__)[(condition) ? 1 : -1]

#define IS_POWER_OF_2(x) ((x) > 0 && !((x) & ((x) - 1)))

