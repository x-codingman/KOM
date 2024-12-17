#include "klee/klee.h"
#include "stdio.h"

#define Z_OOPS(expr) \
	do { \
		if (expr) { \
			scanf("error"); \
			klee_assert(0); \
		} \
	} while (false)



