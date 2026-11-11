// SPDX-License-Identifier: GPL-2.0
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#include "debug.h"
#include "klog.h" // IWYU pragma: keep
#include "manager/manager_identity.h"
#include "runtime/ksud.h"
#include "runtime/ksud_boot.h"

unsigned long ksu_debug_execveat_calls;
unsigned long ksu_debug_zygote_hits;
unsigned long ksu_debug_setresuid_calls;
unsigned long ksu_debug_fd_installs;
int ksu_debug_post_fs_data;
int ksu_debug_observer_init = -1;
int ksu_debug_observer_adb = -1;

static int ksu_debug_show(struct seq_file *m, void *v)
{
	seq_printf(m, "boot_completed: %d\n", READ_ONCE(ksu_boot_completed));
	seq_printf(m, "post_fs_data: %d\n", READ_ONCE(ksu_debug_post_fs_data));
	seq_printf(m, "observer_init: %d\n", READ_ONCE(ksu_debug_observer_init));
	seq_printf(m, "observer_adb: %d\n", READ_ONCE(ksu_debug_observer_adb));
	seq_printf(m, "manager_appid: %d\n", (int)ksu_get_manager_appid());
	seq_printf(m, "manager_appid_valid: %d\n",
		   ksu_is_manager_appid_valid() ? 1 : 0);
	seq_printf(m, "ksud_present: %d\n", READ_ONCE(ksu_ksud_present));
	seq_printf(m, "execveat_hook: %d\n", READ_ONCE(ksu_execveat_hook));
	seq_printf(m, "execveat_calls: %lu\n",
		   READ_ONCE(ksu_debug_execveat_calls));
	seq_printf(m, "zygote_hits: %lu\n", READ_ONCE(ksu_debug_zygote_hits));
	seq_printf(m, "setresuid_calls: %lu\n",
		   READ_ONCE(ksu_debug_setresuid_calls));
	seq_printf(m, "fd_installs: %lu\n", READ_ONCE(ksu_debug_fd_installs));
	seq_printf(m, "ksu_version: %d\n", KSU_VERSION);
	return 0;
}

static int ksu_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, ksu_debug_show, NULL);
}

static const struct file_operations ksu_debug_fops = {
	.open = ksu_debug_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

void __init ksu_debug_init(void)
{
	proc_create("ksu_debug", 0444, NULL, &ksu_debug_fops);
}

void __exit ksu_debug_exit(void)
{
	remove_proc_entry("ksu_debug", NULL);
}
