// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2009 Arnd Bergmann <arnd@arndb.de>
 * Copyright (C) 2012 Regents of the University of California
 */

#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <asm-generic/syscalls.h>
#include <asm/syscall.h>

#undef __SYSCALL
#define __SYSCALL(nr, call)	asmlinkage long __riscv_##call(const struct pt_regs *);
#include <asm/unistd.h>

#undef __SYSCALL
#define __SYSCALL(nr, call)	[nr] = __riscv_##call,

void * const sys_call_table[__NR_syscalls] = {
	[0 ... __NR_syscalls - 1] = __riscv_sys_ni_syscall,
#include <asm/unistd.h>
};

#ifdef CONFIG_UNIKERNEL_LINUX
#undef __SYSCALL
#define __SYSCALL(nr, call)	asmlinkage long __riscv_ukl_##call(long p0, long p1, long p2, long p3, long p4, long p5, long p6);
#include <asm/unistd.h>

#undef __SYSCALL
#define __SYSCALL(nr, call)	[nr] = __riscv_ukl_##call,

void * const ukl_sys_call_table[__NR_syscalls] = {
	[0 ... __NR_syscalls - 1] = __riscv_ukl_sys_ni_syscall,
#include <asm/unistd.h>
};

#endif