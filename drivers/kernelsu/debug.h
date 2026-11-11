#ifndef __KSU_H_DEBUG
#define __KSU_H_DEBUG

#include <linux/types.h>

extern unsigned long ksu_debug_execveat_calls;
extern unsigned long ksu_debug_zygote_hits;
extern unsigned long ksu_debug_setresuid_calls;
extern unsigned long ksu_debug_fd_installs;
extern int ksu_debug_post_fs_data;
extern int ksu_debug_observer_init;
extern int ksu_debug_observer_adb;

void ksu_debug_init(void);
void ksu_debug_exit(void);

#endif
