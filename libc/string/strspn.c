/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include "_string.h"
#include "../klee/include/klee/klee.h"

#ifdef WANT_WIDE
# define Wstrspn wcsspn
#else
# define Wstrspn strspn
#endif

libc_hidden_proto(Wstrspn)

size_t Wstrspn(const Wchar *s1, const Wchar *s2)
{
	uint32_t ret;
	klee_make_symbolic(&ret, sizeof(ret), "strspn_return_value");
	int s1_len = strlen(s1), s2_len = strlen(s2);
	klee_strspn(s1, s2, s1_len, s2_len, ret);
	return (size_t)ret;
	// register const Wchar *s = s1;
	// register const Wchar *p = s2;

	// while (*p) {
	// 	if (*p++ == *s) {
	// 		++s;
	// 		p = s2;
	// 	}
	// }
	// return s - s1;
}
libc_hidden_def(Wstrspn)
