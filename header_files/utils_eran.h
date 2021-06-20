#ifndef	__UTILS_H__
#define	__UTILS_H__

typedef enum
{
	SUCCESS,
	FAILURE
} status_ty;

typedef enum
{
	FALSE,
	TRUE
} boolean_ty;

#ifdef _DEBUG
#define DEBUG_ONLY(X) X
#else
#define DEBUG_ONLY(X)
#endif	/* _DEBUG */

#ifdef _TEST
#define TEST_ONLY(X) X
#else
#define TEST_ONLY(X)
#endif	/* _TEST */

#define DEAD_MEM(type)	((type)0xdeadbeef)

#define UNUSED(var)		((void)var)

#include <string.h>	/* memset */
#define DEB_CLEAR(ptr)	DEBUG_ONLY(memset(ptr, 0, sizeof(*ptr)))

#endif	/* __UTILS_H__ */
