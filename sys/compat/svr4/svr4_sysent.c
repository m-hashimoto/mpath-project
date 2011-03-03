/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD: src/sys/compat/svr4/svr4_sysent.c,v 1.29.2.1.2.1 2009/10/25 01:10:29 kensmith Exp $
 * created from FreeBSD: head/sys/compat/svr4/syscalls.master 160798 2006-07-28 19:05:28Z jhb 
 */

#include <sys/types.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <netinet/in.h>
#include <compat/svr4/svr4.h>
#include <compat/svr4/svr4_types.h>
#include <compat/svr4/svr4_signal.h>
#include <compat/svr4/svr4_proto.h>

#define AS(name) (sizeof(struct name) / sizeof(register_t))

/* The casts are bogus but will do for now. */
struct sysent svr4_sysent[] = {
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 0 = unused */
	{ AS(sys_exit_args), (sy_call_t *)sys_exit, AUE_NULL, NULL, 0, 0, 0 },	/* 1 = exit */
	{ 0, (sy_call_t *)fork, AUE_NULL, NULL, 0, 0, 0 },		/* 2 = fork */
	{ AS(read_args), (sy_call_t *)read, AUE_NULL, NULL, 0, 0, 0 },	/* 3 = read */
	{ AS(write_args), (sy_call_t *)write, AUE_NULL, NULL, 0, 0, 0 },	/* 4 = write */
	{ AS(svr4_sys_open_args), (sy_call_t *)svr4_sys_open, AUE_NULL, NULL, 0, 0, 0 },	/* 5 = svr4_sys_open */
	{ AS(close_args), (sy_call_t *)close, AUE_NULL, NULL, 0, 0, 0 },	/* 6 = close */
	{ AS(svr4_sys_wait_args), (sy_call_t *)svr4_sys_wait, AUE_NULL, NULL, 0, 0, 0 },	/* 7 = svr4_sys_wait */
	{ AS(svr4_sys_creat_args), (sy_call_t *)svr4_sys_creat, AUE_NULL, NULL, 0, 0, 0 },	/* 8 = svr4_sys_creat */
	{ AS(link_args), (sy_call_t *)link, AUE_NULL, NULL, 0, 0, 0 },	/* 9 = link */
	{ AS(unlink_args), (sy_call_t *)unlink, AUE_NULL, NULL, 0, 0, 0 },	/* 10 = unlink */
	{ AS(svr4_sys_execv_args), (sy_call_t *)svr4_sys_execv, AUE_NULL, NULL, 0, 0, 0 },	/* 11 = svr4_sys_execv */
	{ AS(chdir_args), (sy_call_t *)chdir, AUE_NULL, NULL, 0, 0, 0 },	/* 12 = chdir */
	{ AS(svr4_sys_time_args), (sy_call_t *)svr4_sys_time, AUE_NULL, NULL, 0, 0, 0 },	/* 13 = svr4_sys_time */
	{ AS(svr4_sys_mknod_args), (sy_call_t *)svr4_sys_mknod, AUE_NULL, NULL, 0, 0, 0 },	/* 14 = svr4_sys_mknod */
	{ AS(chmod_args), (sy_call_t *)chmod, AUE_NULL, NULL, 0, 0, 0 },	/* 15 = chmod */
	{ AS(chown_args), (sy_call_t *)chown, AUE_NULL, NULL, 0, 0, 0 },	/* 16 = chown */
	{ AS(svr4_sys_break_args), (sy_call_t *)svr4_sys_break, AUE_NULL, NULL, 0, 0, 0 },	/* 17 = svr4_sys_break */
	{ AS(svr4_sys_stat_args), (sy_call_t *)svr4_sys_stat, AUE_NULL, NULL, 0, 0, 0 },	/* 18 = svr4_sys_stat */
	{ AS(lseek_args), (sy_call_t *)lseek, AUE_NULL, NULL, 0, 0, 0 },	/* 19 = lseek */
	{ 0, (sy_call_t *)getpid, AUE_NULL, NULL, 0, 0, 0 },		/* 20 = getpid */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 21 = old_mount */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 22 = sysv_umount */
	{ AS(setuid_args), (sy_call_t *)setuid, AUE_NULL, NULL, 0, 0, 0 },	/* 23 = setuid */
	{ 0, (sy_call_t *)getuid, AUE_NULL, NULL, 0, 0, 0 },		/* 24 = getuid */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 25 = stime */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 26 = ptrace */
	{ AS(svr4_sys_alarm_args), (sy_call_t *)svr4_sys_alarm, AUE_NULL, NULL, 0, 0, 0 },	/* 27 = svr4_sys_alarm */
	{ AS(svr4_sys_fstat_args), (sy_call_t *)svr4_sys_fstat, AUE_NULL, NULL, 0, 0, 0 },	/* 28 = svr4_sys_fstat */
	{ 0, (sy_call_t *)svr4_sys_pause, AUE_NULL, NULL, 0, 0, 0 },	/* 29 = svr4_sys_pause */
	{ AS(svr4_sys_utime_args), (sy_call_t *)svr4_sys_utime, AUE_NULL, NULL, 0, 0, 0 },	/* 30 = svr4_sys_utime */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 31 = stty */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 32 = gtty */
	{ AS(svr4_sys_access_args), (sy_call_t *)svr4_sys_access, AUE_NULL, NULL, 0, 0, 0 },	/* 33 = svr4_sys_access */
	{ AS(svr4_sys_nice_args), (sy_call_t *)svr4_sys_nice, AUE_NULL, NULL, 0, 0, 0 },	/* 34 = svr4_sys_nice */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 35 = statfs */
	{ 0, (sy_call_t *)sync, AUE_NULL, NULL, 0, 0, 0 },		/* 36 = sync */
	{ AS(svr4_sys_kill_args), (sy_call_t *)svr4_sys_kill, AUE_NULL, NULL, 0, 0, 0 },	/* 37 = svr4_sys_kill */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 38 = fstatfs */
	{ AS(svr4_sys_pgrpsys_args), (sy_call_t *)svr4_sys_pgrpsys, AUE_NULL, NULL, 0, 0, 0 },	/* 39 = svr4_sys_pgrpsys */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 40 = xenix */
	{ AS(dup_args), (sy_call_t *)dup, AUE_NULL, NULL, 0, 0, 0 },	/* 41 = dup */
	{ 0, (sy_call_t *)pipe, AUE_NULL, NULL, 0, 0, 0 },		/* 42 = pipe */
	{ AS(svr4_sys_times_args), (sy_call_t *)svr4_sys_times, AUE_NULL, NULL, 0, 0, 0 },	/* 43 = svr4_sys_times */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 44 = profil */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 45 = plock */
	{ AS(setgid_args), (sy_call_t *)setgid, AUE_NULL, NULL, 0, 0, 0 },	/* 46 = setgid */
	{ 0, (sy_call_t *)getgid, AUE_NULL, NULL, 0, 0, 0 },		/* 47 = getgid */
	{ AS(svr4_sys_signal_args), (sy_call_t *)svr4_sys_signal, AUE_NULL, NULL, 0, 0, 0 },	/* 48 = svr4_sys_signal */
	{ AS(svr4_sys_msgsys_args), (sy_call_t *)svr4_sys_msgsys, AUE_NULL, NULL, 0, 0, 0 },	/* 49 = svr4_sys_msgsys */
	{ AS(svr4_sys_sysarch_args), (sy_call_t *)svr4_sys_sysarch, AUE_NULL, NULL, 0, 0, 0 },	/* 50 = svr4_sys_sysarch */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 51 = acct */
	{ AS(svr4_sys_shmsys_args), (sy_call_t *)svr4_sys_shmsys, AUE_NULL, NULL, 0, 0, 0 },	/* 52 = svr4_sys_shmsys */
	{ AS(svr4_sys_semsys_args), (sy_call_t *)svr4_sys_semsys, AUE_NULL, NULL, 0, 0, 0 },	/* 53 = svr4_sys_semsys */
	{ AS(svr4_sys_ioctl_args), (sy_call_t *)svr4_sys_ioctl, AUE_NULL, NULL, 0, 0, 0 },	/* 54 = svr4_sys_ioctl */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 55 = uadmin */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 56 = exch */
	{ AS(svr4_sys_utssys_args), (sy_call_t *)svr4_sys_utssys, AUE_NULL, NULL, 0, 0, 0 },	/* 57 = svr4_sys_utssys */
	{ AS(fsync_args), (sy_call_t *)fsync, AUE_NULL, NULL, 0, 0, 0 },	/* 58 = fsync */
	{ AS(svr4_sys_execve_args), (sy_call_t *)svr4_sys_execve, AUE_NULL, NULL, 0, 0, 0 },	/* 59 = svr4_sys_execve */
	{ AS(umask_args), (sy_call_t *)umask, AUE_NULL, NULL, 0, 0, 0 },	/* 60 = umask */
	{ AS(chroot_args), (sy_call_t *)chroot, AUE_NULL, NULL, 0, 0, 0 },	/* 61 = chroot */
	{ AS(svr4_sys_fcntl_args), (sy_call_t *)svr4_sys_fcntl, AUE_NULL, NULL, 0, 0, 0 },	/* 62 = svr4_sys_fcntl */
	{ AS(svr4_sys_ulimit_args), (sy_call_t *)svr4_sys_ulimit, AUE_NULL, NULL, 0, 0, 0 },	/* 63 = svr4_sys_ulimit */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 64 = reserved */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 65 = reserved */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 66 = reserved */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 67 = reserved */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 68 = reserved */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 69 = reserved */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 70 = advfs */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 71 = unadvfs */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 72 = rmount */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 73 = rumount */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 74 = rfstart */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 75 = sigret */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 76 = rdebug */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 77 = rfstop */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 78 = rfsys */
	{ AS(rmdir_args), (sy_call_t *)rmdir, AUE_NULL, NULL, 0, 0, 0 },	/* 79 = rmdir */
	{ AS(mkdir_args), (sy_call_t *)mkdir, AUE_NULL, NULL, 0, 0, 0 },	/* 80 = mkdir */
	{ AS(svr4_sys_getdents_args), (sy_call_t *)svr4_sys_getdents, AUE_NULL, NULL, 0, 0, 0 },	/* 81 = svr4_sys_getdents */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 82 = libattach */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 83 = libdetach */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 84 = sysfs */
	{ AS(svr4_sys_getmsg_args), (sy_call_t *)svr4_sys_getmsg, AUE_NULL, NULL, 0, 0, 0 },	/* 85 = svr4_sys_getmsg */
	{ AS(svr4_sys_putmsg_args), (sy_call_t *)svr4_sys_putmsg, AUE_NULL, NULL, 0, 0, 0 },	/* 86 = svr4_sys_putmsg */
	{ AS(svr4_sys_poll_args), (sy_call_t *)svr4_sys_poll, AUE_NULL, NULL, 0, 0, 0 },	/* 87 = svr4_sys_poll */
	{ AS(svr4_sys_lstat_args), (sy_call_t *)svr4_sys_lstat, AUE_NULL, NULL, 0, 0, 0 },	/* 88 = svr4_sys_lstat */
	{ AS(symlink_args), (sy_call_t *)symlink, AUE_NULL, NULL, 0, 0, 0 },	/* 89 = symlink */
	{ AS(readlink_args), (sy_call_t *)readlink, AUE_NULL, NULL, 0, 0, 0 },	/* 90 = readlink */
	{ AS(getgroups_args), (sy_call_t *)getgroups, AUE_NULL, NULL, 0, 0, 0 },	/* 91 = getgroups */
	{ AS(setgroups_args), (sy_call_t *)setgroups, AUE_NULL, NULL, 0, 0, 0 },	/* 92 = setgroups */
	{ AS(fchmod_args), (sy_call_t *)fchmod, AUE_NULL, NULL, 0, 0, 0 },	/* 93 = fchmod */
	{ AS(fchown_args), (sy_call_t *)fchown, AUE_NULL, NULL, 0, 0, 0 },	/* 94 = fchown */
	{ AS(svr4_sys_sigprocmask_args), (sy_call_t *)svr4_sys_sigprocmask, AUE_NULL, NULL, 0, 0, 0 },	/* 95 = svr4_sys_sigprocmask */
	{ AS(svr4_sys_sigsuspend_args), (sy_call_t *)svr4_sys_sigsuspend, AUE_NULL, NULL, 0, 0, 0 },	/* 96 = svr4_sys_sigsuspend */
	{ AS(svr4_sys_sigaltstack_args), (sy_call_t *)svr4_sys_sigaltstack, AUE_NULL, NULL, 0, 0, 0 },	/* 97 = svr4_sys_sigaltstack */
	{ AS(svr4_sys_sigaction_args), (sy_call_t *)svr4_sys_sigaction, AUE_NULL, NULL, 0, 0, 0 },	/* 98 = svr4_sys_sigaction */
	{ AS(svr4_sys_sigpending_args), (sy_call_t *)svr4_sys_sigpending, AUE_NULL, NULL, 0, 0, 0 },	/* 99 = svr4_sys_sigpending */
	{ AS(svr4_sys_context_args), (sy_call_t *)svr4_sys_context, AUE_NULL, NULL, 0, 0, 0 },	/* 100 = svr4_sys_context */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 101 = evsys */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 102 = evtrapret */
	{ AS(svr4_sys_statvfs_args), (sy_call_t *)svr4_sys_statvfs, AUE_NULL, NULL, 0, 0, 0 },	/* 103 = svr4_sys_statvfs */
	{ AS(svr4_sys_fstatvfs_args), (sy_call_t *)svr4_sys_fstatvfs, AUE_NULL, NULL, 0, 0, 0 },	/* 104 = svr4_sys_fstatvfs */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 105 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 106 = nfssvc */
	{ AS(svr4_sys_waitsys_args), (sy_call_t *)svr4_sys_waitsys, AUE_NULL, NULL, 0, 0, 0 },	/* 107 = svr4_sys_waitsys */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 108 = sigsendsys */
	{ AS(svr4_sys_hrtsys_args), (sy_call_t *)svr4_sys_hrtsys, AUE_NULL, NULL, 0, 0, 0 },	/* 109 = svr4_sys_hrtsys */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 110 = acancel */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 111 = async */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 112 = priocntlsys */
	{ AS(svr4_sys_pathconf_args), (sy_call_t *)svr4_sys_pathconf, AUE_NULL, NULL, 0, 0, 0 },	/* 113 = svr4_sys_pathconf */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 114 = mincore */
	{ AS(svr4_sys_mmap_args), (sy_call_t *)svr4_sys_mmap, AUE_NULL, NULL, 0, 0, 0 },	/* 115 = svr4_sys_mmap */
	{ AS(mprotect_args), (sy_call_t *)mprotect, AUE_NULL, NULL, 0, 0, 0 },	/* 116 = mprotect */
	{ AS(munmap_args), (sy_call_t *)munmap, AUE_NULL, NULL, 0, 0, 0 },	/* 117 = munmap */
	{ AS(svr4_sys_fpathconf_args), (sy_call_t *)svr4_sys_fpathconf, AUE_NULL, NULL, 0, 0, 0 },	/* 118 = svr4_sys_fpathconf */
	{ 0, (sy_call_t *)vfork, AUE_NULL, NULL, 0, 0, 0 },		/* 119 = vfork */
	{ AS(fchdir_args), (sy_call_t *)fchdir, AUE_NULL, NULL, 0, 0, 0 },	/* 120 = fchdir */
	{ AS(readv_args), (sy_call_t *)readv, AUE_NULL, NULL, 0, 0, 0 },	/* 121 = readv */
	{ AS(writev_args), (sy_call_t *)writev, AUE_NULL, NULL, 0, 0, 0 },	/* 122 = writev */
	{ AS(svr4_sys_xstat_args), (sy_call_t *)svr4_sys_xstat, AUE_NULL, NULL, 0, 0, 0 },	/* 123 = svr4_sys_xstat */
	{ AS(svr4_sys_lxstat_args), (sy_call_t *)svr4_sys_lxstat, AUE_NULL, NULL, 0, 0, 0 },	/* 124 = svr4_sys_lxstat */
	{ AS(svr4_sys_fxstat_args), (sy_call_t *)svr4_sys_fxstat, AUE_NULL, NULL, 0, 0, 0 },	/* 125 = svr4_sys_fxstat */
	{ AS(svr4_sys_xmknod_args), (sy_call_t *)svr4_sys_xmknod, AUE_NULL, NULL, 0, 0, 0 },	/* 126 = svr4_sys_xmknod */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 127 = clocal */
	{ AS(svr4_sys_setrlimit_args), (sy_call_t *)svr4_sys_setrlimit, AUE_NULL, NULL, 0, 0, 0 },	/* 128 = svr4_sys_setrlimit */
	{ AS(svr4_sys_getrlimit_args), (sy_call_t *)svr4_sys_getrlimit, AUE_NULL, NULL, 0, 0, 0 },	/* 129 = svr4_sys_getrlimit */
	{ AS(lchown_args), (sy_call_t *)lchown, AUE_NULL, NULL, 0, 0, 0 },	/* 130 = lchown */
	{ AS(svr4_sys_memcntl_args), (sy_call_t *)svr4_sys_memcntl, AUE_NULL, NULL, 0, 0, 0 },	/* 131 = svr4_sys_memcntl */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 132 = getpmsg */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 133 = putpmsg */
	{ AS(rename_args), (sy_call_t *)rename, AUE_NULL, NULL, 0, 0, 0 },	/* 134 = rename */
	{ AS(svr4_sys_uname_args), (sy_call_t *)svr4_sys_uname, AUE_NULL, NULL, 0, 0, 0 },	/* 135 = svr4_sys_uname */
	{ AS(setegid_args), (sy_call_t *)setegid, AUE_NULL, NULL, 0, 0, 0 },	/* 136 = setegid */
	{ AS(svr4_sys_sysconfig_args), (sy_call_t *)svr4_sys_sysconfig, AUE_NULL, NULL, 0, 0, 0 },	/* 137 = svr4_sys_sysconfig */
	{ AS(adjtime_args), (sy_call_t *)adjtime, AUE_NULL, NULL, 0, 0, 0 },	/* 138 = adjtime */
	{ AS(svr4_sys_systeminfo_args), (sy_call_t *)svr4_sys_systeminfo, AUE_NULL, NULL, 0, 0, 0 },	/* 139 = svr4_sys_systeminfo */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 140 = notused */
	{ AS(seteuid_args), (sy_call_t *)seteuid, AUE_NULL, NULL, 0, 0, 0 },	/* 141 = seteuid */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 142 = vtrace */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 143 = { */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 144 = sigtimedwait */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 145 = lwp_info */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 146 = yield */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 147 = lwp_sema_wait */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 148 = lwp_sema_post */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 149 = lwp_sema_trywait */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 150 = notused */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 151 = notused */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 152 = modctl */
	{ AS(svr4_sys_fchroot_args), (sy_call_t *)svr4_sys_fchroot, AUE_NULL, NULL, 0, 0, 0 },	/* 153 = svr4_sys_fchroot */
	{ AS(svr4_sys_utimes_args), (sy_call_t *)svr4_sys_utimes, AUE_NULL, NULL, 0, 0, 0 },	/* 154 = svr4_sys_utimes */
	{ 0, (sy_call_t *)svr4_sys_vhangup, AUE_NULL, NULL, 0, 0, 0 },	/* 155 = svr4_sys_vhangup */
	{ AS(svr4_sys_gettimeofday_args), (sy_call_t *)svr4_sys_gettimeofday, AUE_NULL, NULL, 0, 0, 0 },	/* 156 = svr4_sys_gettimeofday */
	{ AS(getitimer_args), (sy_call_t *)getitimer, AUE_NULL, NULL, 0, 0, 0 },	/* 157 = getitimer */
	{ AS(setitimer_args), (sy_call_t *)setitimer, AUE_NULL, NULL, 0, 0, 0 },	/* 158 = setitimer */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 159 = lwp_create */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 160 = lwp_exit */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 161 = lwp_suspend */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 162 = lwp_continue */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 163 = lwp_kill */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 164 = lwp_self */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 165 = lwp_getprivate */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 166 = lwp_setprivate */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 167 = lwp_wait */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 168 = lwp_mutex_unlock */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 169 = lwp_mutex_lock */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 170 = lwp_cond_wait */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 171 = lwp_cond_signal */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 172 = lwp_cond_broadcast */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 173 = { */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 174 = { */
	{ AS(svr4_sys_llseek_args), (sy_call_t *)svr4_sys_llseek, AUE_NULL, NULL, 0, 0, 0 },	/* 175 = svr4_sys_llseek */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 176 = inst_sync */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 177 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 178 = kaio */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 179 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 180 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 181 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 182 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 183 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 184 = tsolsys */
	{ AS(svr4_sys_acl_args), (sy_call_t *)svr4_sys_acl, AUE_NULL, NULL, 0, 0, 0 },	/* 185 = svr4_sys_acl */
	{ AS(svr4_sys_auditsys_args), (sy_call_t *)svr4_sys_auditsys, AUE_NULL, NULL, 0, 0, 0 },	/* 186 = svr4_sys_auditsys */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 187 = processor_bind */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 188 = processor_info */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 189 = p_online */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 190 = sigqueue */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 191 = clock_gettime */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 192 = clock_settime */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 193 = clock_getres */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 194 = timer_create */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 195 = timer_delete */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 196 = timer_settime */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 197 = timer_gettime */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 198 = timer_overrun */
	{ AS(nanosleep_args), (sy_call_t *)nanosleep, AUE_NULL, NULL, 0, 0, 0 },	/* 199 = nanosleep */
	{ AS(svr4_sys_facl_args), (sy_call_t *)svr4_sys_facl, AUE_NULL, NULL, 0, 0, 0 },	/* 200 = svr4_sys_facl */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 201 = door */
	{ AS(setreuid_args), (sy_call_t *)setreuid, AUE_NULL, NULL, 0, 0, 0 },	/* 202 = setreuid */
	{ AS(setregid_args), (sy_call_t *)setregid, AUE_NULL, NULL, 0, 0, 0 },	/* 203 = setregid */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 204 = install_utrap */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 205 = signotify */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 206 = schedctl */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 207 = pset */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 208 = whoknows */
	{ AS(svr4_sys_resolvepath_args), (sy_call_t *)svr4_sys_resolvepath, AUE_NULL, NULL, 0, 0, 0 },	/* 209 = svr4_sys_resolvepath */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 210 = signotifywait */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 211 = lwp_sigredirect */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 212 = lwp_alarm */
	{ AS(svr4_sys_getdents64_args), (sy_call_t *)svr4_sys_getdents64, AUE_NULL, NULL, 0, 0, 0 },	/* 213 = svr4_sys_getdents64 */
	{ AS(svr4_sys_mmap64_args), (sy_call_t *)svr4_sys_mmap64, AUE_NULL, NULL, 0, 0, 0 },	/* 214 = svr4_sys_mmap64 */
	{ AS(svr4_sys_stat64_args), (sy_call_t *)svr4_sys_stat64, AUE_NULL, NULL, 0, 0, 0 },	/* 215 = svr4_sys_stat64 */
	{ AS(svr4_sys_lstat64_args), (sy_call_t *)svr4_sys_lstat64, AUE_NULL, NULL, 0, 0, 0 },	/* 216 = svr4_sys_lstat64 */
	{ AS(svr4_sys_fstat64_args), (sy_call_t *)svr4_sys_fstat64, AUE_NULL, NULL, 0, 0, 0 },	/* 217 = svr4_sys_fstat64 */
	{ AS(svr4_sys_statvfs64_args), (sy_call_t *)svr4_sys_statvfs64, AUE_NULL, NULL, 0, 0, 0 },	/* 218 = svr4_sys_statvfs64 */
	{ AS(svr4_sys_fstatvfs64_args), (sy_call_t *)svr4_sys_fstatvfs64, AUE_NULL, NULL, 0, 0, 0 },	/* 219 = svr4_sys_fstatvfs64 */
	{ AS(svr4_sys_setrlimit64_args), (sy_call_t *)svr4_sys_setrlimit64, AUE_NULL, NULL, 0, 0, 0 },	/* 220 = svr4_sys_setrlimit64 */
	{ AS(svr4_sys_getrlimit64_args), (sy_call_t *)svr4_sys_getrlimit64, AUE_NULL, NULL, 0, 0, 0 },	/* 221 = svr4_sys_getrlimit64 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 222 = pread64 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 223 = pwrite64 */
	{ AS(svr4_sys_creat64_args), (sy_call_t *)svr4_sys_creat64, AUE_NULL, NULL, 0, 0, 0 },	/* 224 = svr4_sys_creat64 */
	{ AS(svr4_sys_open64_args), (sy_call_t *)svr4_sys_open64, AUE_NULL, NULL, 0, 0, 0 },	/* 225 = svr4_sys_open64 */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 226 = rpcsys */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 227 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 228 = whoknows */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 229 = whoknows */
	{ AS(svr4_sys_socket_args), (sy_call_t *)svr4_sys_socket, AUE_NULL, NULL, 0, 0, 0 },	/* 230 = svr4_sys_socket */
	{ AS(socketpair_args), (sy_call_t *)socketpair, AUE_NULL, NULL, 0, 0, 0 },	/* 231 = socketpair */
	{ AS(bind_args), (sy_call_t *)bind, AUE_NULL, NULL, 0, 0, 0 },	/* 232 = bind */
	{ AS(listen_args), (sy_call_t *)listen, AUE_NULL, NULL, 0, 0, 0 },	/* 233 = listen */
	{ AS(accept_args), (sy_call_t *)accept, AUE_NULL, NULL, 0, 0, 0 },	/* 234 = accept */
	{ AS(connect_args), (sy_call_t *)connect, AUE_NULL, NULL, 0, 0, 0 },	/* 235 = connect */
	{ AS(shutdown_args), (sy_call_t *)shutdown, AUE_NULL, NULL, 0, 0, 0 },	/* 236 = shutdown */
	{ AS(svr4_sys_recv_args), (sy_call_t *)svr4_sys_recv, AUE_NULL, NULL, 0, 0, 0 },	/* 237 = svr4_sys_recv */
	{ AS(recvfrom_args), (sy_call_t *)recvfrom, AUE_NULL, NULL, 0, 0, 0 },	/* 238 = recvfrom */
	{ AS(recvmsg_args), (sy_call_t *)recvmsg, AUE_NULL, NULL, 0, 0, 0 },	/* 239 = recvmsg */
	{ AS(svr4_sys_send_args), (sy_call_t *)svr4_sys_send, AUE_NULL, NULL, 0, 0, 0 },	/* 240 = svr4_sys_send */
	{ AS(sendmsg_args), (sy_call_t *)sendmsg, AUE_NULL, NULL, 0, 0, 0 },	/* 241 = sendmsg */
	{ AS(svr4_sys_sendto_args), (sy_call_t *)svr4_sys_sendto, AUE_NULL, NULL, 0, 0, 0 },	/* 242 = svr4_sys_sendto */
	{ AS(getpeername_args), (sy_call_t *)getpeername, AUE_NULL, NULL, 0, 0, 0 },	/* 243 = getpeername */
	{ AS(getsockname_args), (sy_call_t *)getsockname, AUE_NULL, NULL, 0, 0, 0 },	/* 244 = getsockname */
	{ AS(getsockopt_args), (sy_call_t *)getsockopt, AUE_NULL, NULL, 0, 0, 0 },	/* 245 = getsockopt */
	{ AS(setsockopt_args), (sy_call_t *)setsockopt, AUE_NULL, NULL, 0, 0, 0 },	/* 246 = setsockopt */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 247 = sockconfig */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 248 = { */
	{ 0, (sy_call_t *)nosys, AUE_NULL, NULL, 0, 0, 0 },			/* 249 = { */
};
