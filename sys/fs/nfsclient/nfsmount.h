/*-
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/sys/fs/nfsclient/nfsmount.h,v 1.1.2.1.2.1 2009/10/25 01:10:29 kensmith Exp $
 */

#ifndef _NFSCLIENT_NFSMOUNT_H_
#define	_NFSCLIENT_NFSMOUNT_H_

/*
 * Mount structure.
 * One allocated on every NFS mount.
 * Holds NFS specific information for mount.
 */
struct	nfsmount {
	struct mtx	nm_mtx;
	int	nm_flag;		/* Flags for soft/hard... */
	int	nm_state;		/* Internal state flags */
	struct	mount *nm_mountp;	/* Vfs structure for this filesystem */
	int	nm_numgrps;		/* Max. size of groupslist */
	u_char	nm_fh[NFSX_FHMAX];	/* File handle of root dir */
	int	nm_fhsize;		/* Size of root file handle */
	struct	nfssockreq nm_sockreq;	/* Socket Info */
	int	nm_timeo;		/* Init timer for NFSMNT_DUMBTIMR */
	int	nm_retry;		/* Max retries */
	int	nm_timeouts;		/* Request timeouts */
	int	nm_rsize;		/* Max size of read rpc */
	int	nm_wsize;		/* Max size of write rpc */
	int	nm_readdirsize;		/* Size of a readdir rpc */
	int	nm_readahead;		/* Num. of blocks to readahead */
	int	nm_wcommitsize;		/* Max size of commit for write */
	int	nm_acdirmin;		/* Directory attr cache min lifetime */
	int	nm_acdirmax;		/* Directory attr cache max lifetime */
	int	nm_acregmin;		/* Reg file attr cache min lifetime */
	int	nm_acregmax;		/* Reg file attr cache max lifetime */
	u_char	nm_verf[NFSX_VERF];	/* write verifier */
	TAILQ_HEAD(, buf) nm_bufq;	/* async io buffer queue */
	short	nm_bufqlen;		/* number of buffers in queue */
	short	nm_bufqwant;		/* process wants to add to the queue */
	int	nm_bufqiods;		/* number of iods processing queue */
	u_int64_t nm_maxfilesize;	/* maximum file size */
	int	nm_tprintf_initial_delay; /* initial delay */
	int	nm_tprintf_delay;	/* interval for messages */

	/* Newnfs additions */
	int	nm_iothreadcnt;
	struct proc *nm_iodwant[NFS_MAXRAHEAD];
	struct	nfsclclient *nm_clp;
	uid_t	nm_uid;			/* Uid for SetClientID etc. */
	u_int64_t nm_clval;		/* identifies which clientid */
	u_int64_t nm_fsid[2];		/* NFSv4 fsid */
	u_int16_t nm_krbnamelen;	/* Krb5 host principal, if any */
	u_int16_t nm_dirpathlen;	/* and mount dirpath, for V4 */
	u_int16_t nm_srvkrbnamelen;	/* and the server's target name */
	u_char	nm_name[1];	/* malloc'd actual len of krbname + dirpath */
};

#define	nm_nam		nm_sockreq.nr_nam
#define	nm_sotype	nm_sockreq.nr_sotype
#define	nm_so		nm_sockreq.nr_so
#define	nm_soflags	nm_sockreq.nr_soflags
#define	nm_soproto	nm_sockreq.nr_soproto
#define	nm_client	nm_sockreq.nr_client
#define	nm_krbname	nm_name

#define	NFSMNT_DIRPATH(m)	(&((m)->nm_name[(m)->nm_krbnamelen + 1]))
#define	NFSMNT_SRVKRBNAME(m)						\
	(&((m)->nm_name[(m)->nm_krbnamelen + (m)->nm_dirpathlen + 2]))

#if defined(_KERNEL)
/*
 * Convert mount ptr to nfsmount ptr.
 */
#define	VFSTONFS(mp)	((struct nfsmount *)((mp)->mnt_data))

#endif	/* _KERNEL */

#endif	/* _NFSCLIENT_NFSMOUNT_H_ */
