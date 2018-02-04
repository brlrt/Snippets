#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* macros */
#define EVER ;;

/* globals */
const char MESSAGE[] = "Hello, world!\n";
const int BACK_LOG = 5;

/* local protos */
static int _get_hostname(char *buffer, int length);

/**
 * Main
 *
 * Usage:
 * 	server port
 */
int main(int argc, char *argv[])
{
	int server_socket = -1, on, port, status;
	int slave_socket;
	struct hostent *host_ptr;
	struct sockaddr_in server_name = { 0 };
	struct sockaddr_in client_name = { 0 };
	struct linger linger = { 0 };
	char hostname[80];
	socklen_t client_length;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(1);
	}

	port = atoi(argv[1]);

	if ((server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		perror("socket()");
		exit(1);
	}

	/* turn on reuseable address - avoids TIME_WAIT */
	on = 1;
	if ((status = setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on))) == -1) {
		perror("setsockopt(..., SO_REUSEADDR, ...) - continuing");
	}

	/* turn linger on */
	linger.l_onoff = 1;
	linger.l_linger = 30;
	if ((status = setsockopt(server_socket, SOL_SOCKET, SO_LINGER, (const char *)&linger, sizeof(linger))) == -1) {
		perror("setsockopt(..., SO_LINGER, ...) - continuing");
	}

	if ((status = _get_hostname(hostname, sizeof(hostname))) == -1) {
		perror("_get_hostname()");
		exit(1);
	}

	if ((host_ptr = gethostbyname(hostname)) == NULL) {
		perror("gethostbyname()");
		exit(1);
	}

	memset(&server_name, 0, sizeof(server_name));
	memcpy(&server_name.sin_addr, host_ptr->h_addr, host_ptr->h_length);

	server_name.sin_family = AF_INET;
	server_name.sin_port = htons(port);
	if ((status = bind(server_socket, (struct sockaddr *)&server_name, sizeof(server_name))) == -1) {
		perror("bind()");
		exit(1);
	}

	if ((status = listen(server_socket, BACK_LOG)) == -1) {
		perror("listen()");
		exit(1);
	}

	for (EVER) {
		size_t written;

		memset(&client_name, 0, sizeof(client_name));
		
		client_length = sizeof(client_name);
		if ((slave_socket = accept(server_socket, (struct sockaddr *)&client_name, &client_length)) == -1) {
			perror("accept()");
			exit(1);
		}

		switch (fork()) {
		case -1:
			perror("fork()");
			exit(1);
		case 0:
			close(server_socket);

			if (getpeername(slave_socket, (struct sockaddr *)&client_name, &client_length) == -1) {
				perror("getpeername()");
			} else  {
				printf("Connection request from %s\n", inet_ntoa(client_name.sin_addr));
			}

			written = write(slave_socket, MESSAGE, strlen(MESSAGE));
			close(slave_socket);
			exit(0);
		default:
			close(slave_socket);
			break;
		}
	}

	exit(0);
}

/**
 * Local replacement of gethostname to aid portability.
 *
 * @param buffer Where to store hostname.
 * @param length Length of buffer.
 * @returns -1 on error.
 */
static int _get_hostname(char *buffer, int length) {
	struct utsname sysname;
	int status;

	if ((status = uname(&sysname)) != -1) {
		strncpy(buffer, sysname.nodename, length);
	}

	return status;
}
