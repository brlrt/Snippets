#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

/* macros */
#define MAX_MESG_SIZE 4096
#define EVER ;;

static char mesg[MAX_MESG_SIZE] = "";

/**
 * Main
 *
 * Usage:
 *	udpserver port
 */
int main(int argc, char *argv[]) {
	int udp_socket = -1, my_port, status, size;
	struct sockaddr_in server_name = { 0 };
	struct sockaddr_in client_name = { 0 };
	socklen_t client_length;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s port\n", argv[0]);
		exit(1);
	}

	my_port = atoi(argv[1]);
	if ((udp_socket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		perror("socket()");
		exit(1);
	}

	memset(&server_name, 0, sizeof(server_name));
	memset(&client_name, 0, sizeof(client_name));

	server_name.sin_family = AF_INET;
	server_name.sin_addr.s_addr = htonl(INADDR_ANY);
	server_name.sin_port = htons(my_port);

	if ((status = bind(udp_socket, (struct sockaddr *)&server_name, sizeof(server_name))) == -1) {
		perror("bind()");
		exit(1);
	}

	for (EVER) {
		client_length = 0;
		if ((size = recvfrom(udp_socket, mesg, MAX_MESG_SIZE, 0, (struct sockaddr *)&client_name, &client_length)) == -1) {
			perror("recvfrom()");
			exit(1);
		}

		if ((status = sendto(udp_socket, mesg, size, 0, (struct sockaddr *)&client_name, client_length)) != size) {
			fprintf(stderr, "sendto(): short write\n");
			exit(1);
		}
	}

	exit(0);
}
