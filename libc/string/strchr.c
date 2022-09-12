/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include "_string.h"
#include "../klee/include/klee/klee.h"

#ifdef WANT_WIDE
# define Wstrchr wcschr
#else
# define Wstrchr strchr
#endif

libc_hidden_proto(Wstrchr)

Wchar *Wstrchr(register const Wchar *s, Wint c)
{
	uint32_t ret;
	klee_make_symbolic(&ret, sizeof(ret), "strchr_return_value");
	int n = strlen(s);
	klee_strchr(s, c, n, ret);
	if (ret == n)
		return NULL;
	else
		return (Wchar *)(s + ret);
	// do {
	// 	if (*s == ((Wchar)c)) {
	// 		return (Wchar *) s;	/* silence the warning */
	// 	}
	// } while (*s++);

	// return NULL;
}
libc_hidden_def(Wstrchr)

#if !defined WANT_WIDE && defined __UCLIBC_SUSV3_LEGACY__
strong_alias(strchr,index)
#endif
