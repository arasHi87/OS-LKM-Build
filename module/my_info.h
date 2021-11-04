#include <asm/page.h>
#include <generated/utsrelease.h>
#include <linux/cpufreq.h>
#include <linux/seq_file.h>
#include <linux/swap.h>

static void get_version(struct seq_file* m)
{
    seq_puts(m, "==========Version==========\n");
    seq_printf(m, "Linux version %s\n", UTS_RELEASE);
    seq_puts(m, "\n");
}

static void get_cpuinfo(struct seq_file* m)
{
    unsigned int pos = cpumask_next(-1, cpu_online_mask);
    seq_puts(m, "==========CPU==========\n");

    for (; pos < nr_cpu_ids; pos++)
    {
        struct cpuinfo_x86* c = (void*)&cpu_data(pos);
        seq_printf(m, "processor       : %d\n", c->cpu_index);
        seq_printf(m, "model name      : %s\n", c->x86_model_id[0] ? c->x86_model_id : "unknow");
        seq_printf(m, "physical id     : %d\n", c->phys_proc_id);
        seq_printf(m, "core id         : %d\n", c->cpu_core_id);
        seq_printf(m, "cpu cores       : %d\n", c->booted_cores);
        if (c->x86_cache_size)
            seq_printf(m, "cache size      : %u KB\n", c->x86_cache_size);
        seq_printf(m, "clflush size    : %u\n", c->x86_clflush_size);
        seq_printf(m, "cache_alignment : %d\n", c->x86_cache_alignment);
        seq_printf(m, "address sizes   : %u bits physical, %u bits virtual\n",
                   c->x86_phys_bits, c->x86_virt_bits);
        seq_puts(m, "\n");
    }
}

static void get_meminfo(struct seq_file* m)
{
    struct sysinfo i;
    int lru;
    unsigned long pages[NR_LRU_LISTS];

    si_meminfo(&i);
    for (lru = LRU_BASE; lru < NR_LRU_LISTS; lru++)
        pages[lru] = global_node_page_state(NR_LRU_BASE + lru);

    seq_puts(m, "==========Memory==========\n");
    seq_printf(m, "MemTotal        : %ld KB\n", i.totalram);
    seq_printf(m, "MemFree         : %ld KB\n", i.freeram);
    seq_printf(m, "Buffers         : %ld KB\n", i.bufferram);
    seq_printf(m, "Active          : %ld KB\n", pages[LRU_ACTIVE_ANON] +
               pages[LRU_ACTIVE_FILE]);
    seq_printf(m, "Inactive        : %ld KB\n", pages[LRU_INACTIVE_ANON] +
               pages[LRU_INACTIVE_FILE]);
    seq_printf(m, "Shmem           : %ld KB\n", i.sharedram);
    seq_printf(m, "Dirty           : %ld KB\n", global_node_page_state(NR_FILE_DIRTY));
    seq_printf(m, "Writeback       : %ld KB\n", global_node_page_state(NR_WRITEBACK));
    seq_printf(m, "KernelStack     : %ld KB\n", i.sharedram);
    seq_printf(m, "PageTable       : %ld KB\n",  global_node_page_state(NR_PAGETABLE));
    seq_puts(m, "\n");
}