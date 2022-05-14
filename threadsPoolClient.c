// testing fork and pr
#define ERR_MULTIPROCESS 0
#define USAGE_STRING "serverAddress clientAddress fileName"
#include "katwikOpsys.h"

#define SERVER_ADDRESS "127.0.4.20"
#define CLIENT_ADDRESS "127.0.0.69"

#define DESIRED_PORT 3500
#define BUFSIZE 50

#define MAX_BUF 500
#define LEN 40
typedef struct clientRequest_ {
    char clientAddr[LEN];
    char fileName[LEN];
	int sockAddr;
} clientRequest;

int main(int argc, char** argv) {
	USAGE(argc == 4);

	// setup the address we'll connect to
	struct sockaddr_in serverAddr = make_sockaddr_in( AF_INET, htons(DESIRED_PORT),
			inet_addr_(argv[1])
			);

	// setup the address we'll connect to
	struct sockaddr_in clientAddr = make_sockaddr_in( AF_INET, htons(DESIRED_PORT),
			inet_addr_(argv[2])
			);

	// setup our socket, we'll also use this to connect
	int clientSock = socket_(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// make the server socket reusable and non-blocking
	int reuse = 1;
	setsockopt_(clientSock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

	// bind our socket to our address
	bind_(clientSock, (struct sockaddr *) &clientAddr, sizeof(clientAddr));

	// conect to the server through our socket
	ERR_NEG1(connect(clientSock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)));

	// send something to the server
	// char sendBuf[BUFSIZE] = {0};
	// sprintf(sendBuf, "Hello from client!");
	// send_(clientSock, sendBuf, strlen(sendBuf), 0);

	//preparing message &send
	char request[LEN*2] = {0};
	snprintf(request, LEN - 1, "%s", argv[2]);
	snprintf(request + LEN, LEN - 1, "%s", argv[3]);
	send_(clientSock, &request, sizeof(request), 0);

	// receive something from the server
	char recvBuf[MAX_BUF+1] = {0};
	recv_(clientSock, recvBuf, MAX_BUF, 0);
	printf("Received:\n%s\n", recvBuf);

	// cleanup and exit
	close_(clientSock);
	return EXIT_SUCCESS;
}
