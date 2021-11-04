#include "my_info.h"
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

static struct proc_dir_entry* entry;

static int proc_show(struct seq_file* m, void* v)
{
    get_version(m);
    get_cpuinfo(m);
    get_meminfo(m);
    return 0;
}

static int proc_open(struct inode* inode, struct file* file)
{
    return single_open(file, &proc_show, NULL);
}

static struct file_operations fops =
{
    .owner = THIS_MODULE,
    .open = proc_open,
    .release = single_release,
    .read = seq_read,
    .llseek = seq_lseek,
};

static int __init init(void)
{
    entry = proc_create("my_info", 0644, NULL, &fops);
    printk(KERN_ALERT "Init my_info ...\n");
    return 0;
}

static void __exit cleanup(void)
{
    proc_remove(entry);
    printk(KERN_ALERT "Removed my_info ...\n");
}

module_init(init);
module_exit(cleanup);
