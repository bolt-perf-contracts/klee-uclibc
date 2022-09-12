/*
 * Copyright (C) 2002     Manuel Novoa III
 * Copyright (C) 2000-2005 Erik Andersen <andersen@uclibc.org>
 *
 * Licensed under the LGPL v2.1, see the file COPYING.LIB in this tarball.
 */

#include "_string.h"
#include "../klee/include/klee/klee.h"

#ifdef WANT_WIDE
# define Wstrcmp wcscmp
# define Wstrcoll wcscoll
#else
# define Wstrcmp strcmp
# define Wstrcoll strcoll
#endif

libc_hidden_proto(Wstrcmp)

int Wstrcmp(register const Wchar *s1, register const Wchar *s2)
{
	int s1_len = strlen(s1);
	int s2_len = strlen(s2);
	uint32_t ret;
	klee_make_symbolic(&ret, sizeof(ret), "strcmp_return_value");
	klee_strcmp(s1, s2, s1_len, s2_len, ret);
	return (int)ret;
// #ifdef WANT_WIDE
// 	while (*((Wuchar *)s1) == *((Wuchar *)s2)) {
// 		if (!*s1++) {
// 			return 0;
// 		}
// 		++s2;
// 	}

// 	return (*((Wuchar *)s1) < *((Wuchar *)s2)) ? -1 : 1;
// #else
// 	int r;

// 	while (((r = ((int)(*((Wuchar *)s1))) - *((Wuchar *)s2++))
// 			== 0) && *s1++);
	
// 	return r;
// #endif
}
libc_hidden_def(Wstrcmp)

#ifndef __UCLIBC_HAS_LOCALE__
libc_hidden_proto(Wstrcoll)
strong_alias(Wstrcmp,Wstrcoll)
libc_hidden_def(Wstrcoll)
#endif
