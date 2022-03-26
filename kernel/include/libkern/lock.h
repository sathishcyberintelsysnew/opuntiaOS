/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef _KERNEL_LIBKERN_LOCK_H
#define _KERNEL_LIBKERN_LOCK_H

#include <libkern/c_attrs.h>
#include <libkern/kassert.h>
#include <libkern/log.h>
#include <libkern/types.h>

// #define DEBUG_SPINLOCK

struct spinlock {
    int status;
#ifdef DEBUG_SPINLOCK

#endif // DEBUG_SPINLOCK
};
typedef struct spinlock spinlock_t;

static ALWAYS_INLINE void spinlock_init(spinlock_t* lock)
{
    __atomic_store_n(&lock->status, 0, __ATOMIC_RELAXED);
}

static ALWAYS_INLINE void spinlock_acquire(spinlock_t* lock)
{
    while (__atomic_exchange_n(&lock->status, 1, __ATOMIC_ACQUIRE) == 1) {
        // TODO: May be some cpu sleep?
    }
}

static ALWAYS_INLINE void spinlock_release(spinlock_t* lock)
{
    ASSERT(lock->status == 1);
    __atomic_store_n(&lock->status, 0, __ATOMIC_RELEASE);
}

#ifdef DEBUG_SPINLOCK
#define spinlock_acquire(x)                                    \
    extern int vmm_init_setup_finished;                        \
    if (vmm_init_setup_finished) {                             \
        log("acquire lock %s %s:%d ", #x, __FILE__, __LINE__); \
    }                                                          \
    spinlock_acquire(x);

#define spinlock_release(x)                                    \
    extern int vmm_init_setup_finished;                        \
    if (vmm_init_setup_finished) {                             \
        log("release lock %s %s:%d ", #x, __FILE__, __LINE__); \
    }                                                          \
    spinlock_release(x);
#endif

#endif // _KERNEL_LIBKERN_LOCK_H