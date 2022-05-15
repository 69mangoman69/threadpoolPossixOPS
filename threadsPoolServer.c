#define ERR_MULTIPROCESS 0
#define USAGE_STRING "serverAddress"

typedef struct ClientRequest_ ClientRequest;
#define LIST_TYPE ClientRequest*
#include "katwikOpsys.h"

#define PORT 3500
#define BACKLOG 1

#define MAX_BUF 500
#define LEN 40
#define THREAD_COUNT 2

typedef struct ThreadArgs_ {
	int threadNum;
	sem_t* newRequestSem;

	// TODO: this shouldn't even be a semaphore lol
	// might make it a mutex, but might also just put it into the header lol
	sem_t* clientQueueAccessSem;

	MyList* clientQueue;
} ThreadArgs;

typedef struct ClientRequest_ {
	char clientAddr[LEN];
	char fileName[LEN];
	int sockAddr;
} ClientRequest;

volatile sig_atomic_t sigint_received = 0;
void sigint_handler(int sig) {
	UNUSED(sig);
	sigint_received = 1;
}

void* threadFunc(void* voidArgs) {
	pthread_setcanceltype_(PTHREAD_CANCEL_DEFERRED, NULL);
	ThreadArgs* args = (ThreadArgs*) voidArgs;

	while (!sigint_received) {
		sem_wait_(args->newRequestSem);
		sem_wait_(args->clientQueueAccessSem);

		ClientRequest* request = popFirstVal(args->clientQueue);
		sem_post_(args->clientQueueAccessSem);

		printf_("Thread %d recieved request: \"%s\" from: %s\n",
				args->threadNum, request->fileName, request->clientAddr);
		char buf[MAX_BUF + 1] = {0};
		int filedes = open_(request->fileName, O_RDONLY);
		read_(filedes, buf, MAX_BUF);
		send_(request->sockAddr, buf, strlen(buf), 0);

		close_(request->sockAddr);
		FREE(request); // all swell that end swell lol
	}

	return NULL;
}

int main(int argc, char** argv) {
	USAGE(argc == 2);
	sethandler(sigint_handler, SIGINT);

	// setup the address we'll bind to
	struct sockaddr_in serverAddr = make_sockaddr_in(AF_INET, htons(PORT),
			inet_addr_(argv[1])
			);

	// setup our socket
	int serverSock = socket_(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// make the server socket reusable and non-blocking
	int reuse = 1;
	setsockopt_(serverSock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

	// bind our socket to our address
	bind_(serverSock, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	// listen for up to 1 connection
	listen_(serverSock, BACKLOG);

	// Queue setup & Semaphore
	MyList* clientQueue = newMyList();
	sem_t newRequestSem = sem_make(0);
	sem_t clientQueueAccessSem = sem_make();

	pthread_t* threads = malloc_(THREAD_COUNT * sizeof(pthread_t));
	pthread_attr_t threadAttr = pthread_attr_make();
	ThreadArgs* threadArgs = malloc_(THREAD_COUNT * sizeof(ThreadArgs));

	for (int i = 0; i < THREAD_COUNT; ++i) {
		ThreadArgs args = {
			.threadNum = i + 1,
			.newRequestSem = &newRequestSem,
			.clientQueue = clientQueue,
			.clientQueueAccessSem = &clientQueueAccessSem
		};

		threadArgs[i] = args;
		pthread_create_(&threads[i], &threadAttr, &threadFunc, &threadArgs[i]);
	}

	// queue requests until we're interrupted
	while (!sigint_received) {
		struct sockaddr_in clientAddr = {0};
		socklen_t clientAddrLen = sizeof(struct sockaddr_in);
		int clientSock = accept(serverSock, (struct sockaddr*) &clientAddr, &clientAddrLen);

		if (errno == EINTR) {
			break;
		}

		printf("Accepted %s\n", inet_ntoa(clientAddr.sin_addr));

		char rcvBuf[LEN * 2];
		ClientRequest* recvRequest = (ClientRequest*) calloc(1, sizeof(ClientRequest));
		recv_(clientSock, rcvBuf, 2 * LEN, 0);
		recvRequest->sockAddr = clientSock;
		strncpy(recvRequest->clientAddr, rcvBuf, LEN - 1);
		strncpy(recvRequest->fileName, rcvBuf + LEN, LEN - 1);
		printf("Request: \"%s\"\n", recvRequest->fileName);
		sem_wait_(&clientQueueAccessSem);
		insertValLast(clientQueue, recvRequest);
		sem_post_(&clientQueueAccessSem);
		sem_post_(&newRequestSem);
	}

	// cancel threads and wait for them to finish
	for (int i = 0; i < THREAD_COUNT; ++i) {
		pthread_cancel_(threads[i]);
		pthread_join_(threads[i], NULL);
	}

	// cleanup and exit
	printf_("\n"); // slightly tidier exit

	// free any remaining requests in queue
	// fixes Issue #3 lul
	for (ClientRequest* request; myListLength(clientQueue);) {
		request = popFirstVal(clientQueue);
		FREE(request);
	}
	deleteMyList(clientQueue); 

	sem_destroy_(&newRequestSem);
	close_(serverSock);

	FREE(threadArgs);
	FREE(threads);

	return EXIT_SUCCESS;
}

