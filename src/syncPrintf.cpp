#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>

#include "kIntLock.h"

int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
	kIntLock
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	kIntUnlock
		return res;
}
