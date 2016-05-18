#ifndef __BASE_H_
#define __BASE_H_


#ifdef NDEBUG
#	define ASSERT
#	define VERIFY(expr) (expr)
#else
#	if defined(_MSC_VER)
#		include <crtdbg.h>
#		define ASSERT _ASSERTE
#	else
#		include <cassert>
#		define ASSERT assert
#	endif

#	define VERIFY(expr) ASSERT(expr)
#endif

#endif // __BASE_H_