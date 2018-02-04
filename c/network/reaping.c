#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

/* protos */
static void reap_child(int);

/* globals */
static struct sigaction reap_action;
/* Ignore SIGCHLD:
   static struct sigaction ignoreChildDeath={ NULL, 0, SA_CLDSTOP|SA_RESTART, NULL }; */

/**
 * Wait on child.
 *
 * @param sig_num Signal sent.
 */
static void reap_child(int sig_num) {
	int status;

	wait(&status);
}

/**
 * Main
 *
 * Reaping childs ...
 */
int main(int argc, char *argv[])
{
	/* somewhere in code */
	memset(&reap_child, 0, sizeof(struct sigaction));
	reap_action.sa_handler = reap_child;
	reap_action.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &reap_action, NULL);

	/* Ignore SIGCHLD:
	   sigaction(SIGCHLD, &ignoreChildDeath, NULL); */

	/* rest of code */
	exit(0);
}
