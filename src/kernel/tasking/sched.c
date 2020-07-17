#include <mem/kmalloc.h>
#include <tasking/sched.h>
#include <tasking/tasking.h>

static cpu_t* cpu_ptr;

int nxtrun = 0;

extern void switch_contexts(context_t** old, context_t* new);
extern void switch_to_context(context_t* new);

void init_cpus(cpu_t* cpu)
{
    cpu->kstack = kmalloc(VMM_PAGE_SIZE);
    char* sp = cpu->kstack + VMM_PAGE_SIZE;
    sp -= sizeof(*cpu->scheduler);
    cpu->scheduler = (context_t*)sp;
    memset((void*)cpu->scheduler, 0, sizeof(*cpu->scheduler));
    cpu->scheduler->eip = (uint32_t)sched;
}

void scheduler_init()
{


    nxtrun = 0;
    for (int i = 0; i < CPU_CNT; i++) {
        init_cpus(&cpus[i]);
    }
    // TODO assign here real CPU
    cpu_ptr = &cpus[0];
}

void presched()
{
    switch_contexts(&active_proc->context, cpu_ptr->scheduler);
}

int called = 0;

void presched_no_context()
{
    active_proc = 0;
    switch_to_context(cpu_ptr->scheduler);
}

void sched()
{
    proc_t* p;
    for (;;) {
        p = &proc[nxtrun];
        if (p->pid > 0) {
            kprintf("Scheduling, next %d\n", p->pid);
            switchuvm(p); // setting up proc env
            switch_contexts(&cpu_ptr->scheduler, p->context); // jumping into proc
        }
        nxtrun++;
        nxtrun %= nxt_proc;
        p = 0;
    }
}