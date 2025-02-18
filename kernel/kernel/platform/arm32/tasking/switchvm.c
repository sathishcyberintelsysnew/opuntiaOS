/*
 * Copyright (C) 2020-2022 The opuntiaOS Project Authors.
 *  + Contributed by Nikita Melekhin <nimelehin@gmail.com>
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include <mem/vmm.h>
#include <platform/arm32/interrupts.h>
#include <platform/generic/fpu/fpu.h>
#include <platform/generic/system.h>
#include <platform/generic/tasking/trapframe.h>
#include <security/defs.h>
#include <tasking/tasking.h>

/* switching the page dir and tss to the current proc */
void switchuvm(thread_t* thread)
{
    system_disable_interrupts();
#ifdef SECURITY_SPECTRE_MITIGATION
    write_iciallu(0);
#endif
    RUNNING_THREAD = thread;
    vmm_switch_address_space(thread->process->address_space);
    fpu_make_unavail();
    system_enable_interrupts();
}