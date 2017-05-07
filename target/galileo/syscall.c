/**
 * @file syscall.c
 * @brief Implementation of syscalls required by newlib
 * @author Ran Bao
 * @date March, 2017
 */

#include <stddef.h>

#define _close close
#define _sbrk sbrk
#define _lseek lseek
#define _read read
#define _fstat fstat
#define _isatty isatty

size_t _read(int fd, char *buffer, size_t size)
{
	return 0;
}

int _lseek(int fd, int offset, int whence)
{
	return 0;
}

int _write(int fd, char *buffer, size_t size)
{
	return 0;
}

int _open(const char *path, int flags, ...)
{
	return 0;
}

int _close(int fd)
{
	return 0;
}

int _kill(int pid, int sig)
{
	return 0;
}

void _exit(int status)
{
	while (1)
	{

	}
}

int _getpid(int pid)
{
	return 0;
}

size_t _sbrk(int incr)
{
	return 0;
}

int _fstat(int fd, void *st)
{
	return 0;
}

int _stat(const char *fname, void *st)
{
	return 0;
}

int _link(void)
{
	return 0;
}

int _unlink(const char *path)
{
	return 0;
}

void _raise(void)
{

}

int _gettimeofday(void *tp, void *tzp)
{
	return 0;
}

size_t _times(void *tp)
{
	return 0;
}

int _isatty(int fd)
{
	return 0;
}

int _system(const char *command)
{
	return 0;
}

int _rename(const char *old, const char *new)
{
	return 0;
}

