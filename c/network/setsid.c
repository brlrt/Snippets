#ifdef BSD
	int fd;

	setpgrp(0, getpid());	/* change process group */

	/* open controlling terminal ... */
	if ((fd=open("/dev/tty", O_RDWR)) != -1) {
		/* ... lose it */
		ioctl(fd, TIOCNOTTY, 0);
		close(fd);
	}
#endif

#ifdef SVR4
	/* change process group and lose controlling terminal */
	setpgrp();
#endif
