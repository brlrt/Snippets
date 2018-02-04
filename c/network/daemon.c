#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Main
 *
 * Example code ...
 */
int main(int argc, char *argv[])
{
	struct rlimit resource_limit = { 0 };
	int file_desc = -1, status;

	/* somewhere in the code - go daemon */
	status = fork();
	switch (status) {
	case -1:
		perror("fork() - first");
		exit(1);
	case 0:			/* child process */
		break;
	default:		/* parent process */
		exit(0);
	}

	resource_limit.rlim_max = 0;
	if ((status = getrlimit(RLIMIT_NOFILE, &resource_limit)) == -1) {
		perror("getrlimit()");
		exit(1);
	}

	if (resource_limit.rlim_max == 0) {
		fprintf(stderr, "Hmmm ... max number of open file descriptors is 0!\n");
		exit(1);
	}

	for (status = 0; status < resource_limit.rlim_max; status++) {
		close(status);
	}

	if ((status = setsid()) == -1) {
		perror("setsid()");
		exit(1);
	}

	switch (fork()) {
	case -1:
		perror("fork() - second");
		exit(1);
	case 0:			/* second child process */
		break;
	default:		/* parent process */
		exit(0);
	}

	/* we are now in a new session and process group - we have no
	   controlling terminal.  Redirect stdout, stderr and stdin.
	   Release filesystems. */
	if (chdir("/") != 0) {
		exit(1);	/* no root? */
	}

	umask(0);
	if ((file_desc=open("/dev/null", O_RDWR)) == -1) {	/* stdin */
		exit(1);	/* no /dev/null */
	}
		
	status = dup(file_desc);		/* stdout */
	status = dup(file_desc);		/* stderr */

	/* rest of code ... */

	exit(0);
}
