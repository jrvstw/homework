#include "apue.h"
//#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#define	BUFFSIZE	100

int main(void)
{
		int		n;
		char	buf[BUFFSIZE];
		int     fd = open("/dev/null", O_RDWR);

		while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
				if (write(fd, buf, n) != n)
                    err_sys("write error");

		if (n < 0)
				err_sys("read error");

		exit(0);
}

