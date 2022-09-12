/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include "_string.h"
#include "../klee/include/klee/klee.h"

#ifdef __USE_GNU

libc_hidden_proto(memrchr)

void *memrchr(const void *s, int c, size_t n)
{
	uint32_t ret;
	klee_make_symbolic(&ret, sizeof(ret), "memrchr_return_value");
	klee_memrchr(s, c, n, ret);
	if (ret == n)
		return NULL;
	else
		return s + ret;


// 	register const unsigned char *r;
// #ifdef __BCC__
// 	/* bcc can optimize the counter if it thinks it is a pointer... */
// 	register const char *np = (const char *) n;
// #else
// #define np n
// #endif
	
// 	r = ((unsigned char *)s) + ((size_t) np);

// 	while (np) {
// 		if (*--r == ((unsigned char)c)) {
// 			return (void *) r;	/* silence the warning */
// 		}
// 		--np;
// 	}

// 	return NULL;
}
// #undef np

libc_hidden_def(memrchr)
#endif
