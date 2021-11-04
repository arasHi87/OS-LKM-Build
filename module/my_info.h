#include <generated/utsrelease.h>
#include <linux/cpufreq.h>
#include <linux/seq_file.h>

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
