#define IRQ_LOCK for (uint32_t _lock_primask = __get_PRIMASK (), _lock_once = (__disable_irq(), 0u); !_lock_once; _lock_once = 1u, __set_PRIMASK (_lock_primask))

