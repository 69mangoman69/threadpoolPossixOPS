#define ERR_MULTIPROCESS 0
#define USAGE_STRING "serverAddress clientAddress fileName"
#include "katwikOpsys.h"

#define PORT 3500

#define MAX_FILE_LEN 500
#define MAX_REQUEST_LEN 40

int main(int argc, char** argv) {
	USAGE(argc == 4);

	// setup the address we'll connect to
	struct sockaddr_in serverAddr = make_sockaddr_in( AF_INET, htons(PORT),
			inet_addr_(argv[1])
			);

	// setup the address we'll connect to
	struct sockaddr_in clientAddr = make_sockaddr_in( AF_INET, htons(PORT),
			inet_addr_(argv[2])
			);

	// setup our socket, we'll also use this to connect
	int clientSock = socket_(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// make the server socket reusable and non-blocking
	int reuse = 1;
	setsockopt_(clientSock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

	// bind our socket to our address
	bind_(clientSock, (struct sockaddr*) &clientAddr, sizeof(clientAddr));

	// connect to the server through our socket
	ERR_NEG1(connect(clientSock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)));

	// preparing to send request
	char request[MAX_REQUEST_LEN] = {0};
	snprintf_(request, MAX_REQUEST_LEN, "%s", argv[3]);
	printf_("Requesting %s\n", request);

	// send request
	send_(clientSock, &request, sizeof(request), 0);

	// receive and print file from the server
	char fileBuffer[MAX_FILE_LEN + 1] = {0};
	recv_(clientSock, fileBuffer, MAX_FILE_LEN, 0);
	printf_("Received:\n%s\n", fileBuffer);

	// cleanup and exit
	close_(clientSock);

	return EXIT_SUCCESS;
}
