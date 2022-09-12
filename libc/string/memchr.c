/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include "_string.h"
#include "../klee/include/klee/klee.h"

#ifdef WANT_WIDE
# define Wmemchr wmemchr
#else
# define Wmemchr memchr
#endif

libc_hidden_proto(Wmemchr)

Wvoid *Wmemchr(const Wvoid *s, Wint c, size_t n)
{
	uint32_t ret;
	klee_make_symbolic(&ret, sizeof(ret), "memchr_return_value");
	klee_memchr(s, c, n, ret);
	if (ret == n)
		return NULL;
	else
		return (Wvoid *) (s + ret);

// 	register const Wuchar *r = (const Wuchar *) s;
// #ifdef __BCC__
// 	/* bcc can optimize the counter if it thinks it is a pointer... */
// 	register const char *np = (const char *) n;
// #else
// # define np n
// #endif

// 	while (np) {
// 		if (*r == ((Wuchar)c)) {
// 			return (Wvoid *) r;	/* silence the warning */
// 		}
// 		++r;
// 		--np;
// 	}

// 	return NULL;
	
}
// #undef np

libc_hidden_def(Wmemchr)
