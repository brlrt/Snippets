#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * Usage:
 *
 *	client serverName serverPort
 */
int main(int argc, char *argv[])
{
	int client_socket = -1, remote_port, status;
	struct hostent *host_ptr;
	struct sockaddr_in server_name;
	char buffer[256];
	char *remote_host;

	if (argc != 3) {
		fprintf(stderr, "Usage: %s serverName serverPort\n", argv[0]);
		exit(1);
	}

	remote_host = argv[1];
	remote_port = atoi(argv[2]);

	if ((client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		perror("socket()");
		exit(1);
	}

	if ((host_ptr = gethostbyname(remote_host)) == NULL) {
		if ((host_ptr = gethostbyaddr(remote_host, strlen(remote_host), AF_INET)) == NULL) {
			perror("Error resolving server address");
			exit(1);
		}
	}

	server_name.sin_family = AF_INET;
	server_name.sin_port = htons(remote_port);
	memcpy(&server_name.sin_addr, host_ptr->h_addr, host_ptr->h_length);

	if ((status = connect(client_socket, (struct sockaddr *)&server_name, sizeof(server_name))) == -1) {
		perror("connect()");
		exit(1);
	}

	while ((status = read(client_socket, buffer, sizeof(buffer) - 1)) > 0) {
		buffer[status] = 0;
		printf("%i: %s", status, buffer);
	}

	if (status == -1) {
		perror("read()");
	}

	close(client_socket);
	exit(0);
}
