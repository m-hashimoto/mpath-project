/*-
 * Copyright (c) 1992-2011 The FreeBSD Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#define SCCSSTR "@(#)FreeBSD 8.0-RELEASE #0: Thu Jan 27 01:25:05 JST 2011"
#define VERSTR "FreeBSD 8.0-RELEASE #0: Thu Jan 27 01:25:05 JST 2011\n    root@m-hashimoto.jaist.ac.jp:/usr/src/sys/i386/compile/GENERIC\n"
#define RELSTR "8.0-RELEASE"

char sccs[sizeof(SCCSSTR) > 128 ? sizeof(SCCSSTR) : 128] = SCCSSTR;
char version[sizeof(VERSTR) > 256 ? sizeof(VERSTR) : 256] = VERSTR;
char ostype[] = "FreeBSD";
char osrelease[sizeof(RELSTR) > 32 ? sizeof(RELSTR) : 32] = RELSTR;
int osreldate = 800107;
char kern_ident[] = "GENERIC";
