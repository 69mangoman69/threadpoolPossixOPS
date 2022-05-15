#define ERR_MULTIPROCESS 0
#define USAGE_STRING "serverAddress"

typedef struct ClientRequest_ ClientRequest;
#define LIST_TYPE ClientRequest*
#include "katwikOpsys.h"

#define PORT 3500
#define BACKLOG 1

#define MAX_FILE_LEN 500
#define MAX_REQUEST_LEN 40
#define THREAD_COUNT 2

typedef struct ThreadArgs_ {
	int threadNum;
	MyList* clientQueue;
	sem_t* newRequestSem;
	pthread_mutex_t* clientQueueMutex;
} ThreadArgs;

struct ClientRequest_ {
	struct sockaddr_in* clientAddr;
	char fileName[MAX_REQUEST_LEN + 1];
	int clientSocket;
};

volatile sig_atomic_t sigint_received = 0;
void sigint_handler(int sig) {
	UNUSED(sig);
	sigint_received = 1;
}

#define BAD_FILE_RESPONSE "BRUHH THAT AIN'T NO FIIILE"
void* threadFunc(void* voidArgs) {
	pthread_setcanceltype_(PTHREAD_CANCEL_DEFERRED, NULL);
	ThreadArgs* args = (ThreadArgs*) voidArgs;

	while (!sigint_received) {
		// wait until we're signaled for a new request
		sem_wait_(args->newRequestSem);

		// get the request
		pthread_mutex_lock_(args->clientQueueMutex);
		ClientRequest* clientRequest = popFirstVal(args->clientQueue);
		pthread_mutex_unlock_(args->clientQueueMutex);

		// print request details
		printf_("Thread %d handling request: \"%s\" from %s\n",
				args->threadNum,
				clientRequest->fileName,
				inet_ntoa((clientRequest->clientAddr)->sin_addr));

		// open the requested file,
		// retry it if it gets interrupted,
		// ignore ENOENT so that we can handle it ourselves
		int filedes = CHECK_RETRY_( open(clientRequest->fileName, O_RDONLY) , ENOENT );
		if (ENOENT == errno) {
			send_(clientRequest->clientSocket,
					BAD_FILE_RESPONSE, strlen(BAD_FILE_RESPONSE), 0);
			close_(clientRequest->clientSocket);

			FREE(clientRequest->clientAddr);
			FREE(clientRequest);
			continue;
		}

		// read the file and send it
		char buf[MAX_FILE_LEN + 1] = {0};
		read_(filedes, buf, MAX_FILE_LEN);
		send_(clientRequest->clientSocket, buf, strlen(buf), 0);

		// cleanup
		close_(clientRequest->clientSocket);
		FREE(clientRequest->clientAddr);
		FREE(clientRequest);
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
	int serverSocket = socket_(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// make the server socket reusable and non-blocking
	int reuse = 1;
	setsockopt_(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

	// bind our socket to our address
	bind_(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

	// listen for up to 1 connection
	listen_(serverSocket, BACKLOG);

	// queue setup
	MyList* clientQueue = newMyList();
	sem_t newRequestSem = sem_make(0);
	pthread_mutex_t clientQueueMutex = pthread_mutex_make();

	// thread setup
	pthread_t* threads = malloc_(THREAD_COUNT * sizeof(pthread_t));
	pthread_attr_t threadAttr = pthread_attr_make();
	ThreadArgs* threadArgs = malloc_(THREAD_COUNT * sizeof(ThreadArgs));
	for (int i = 0; i < THREAD_COUNT; ++i) {
		ThreadArgs args = {
			.threadNum = i + 1,
			.newRequestSem = &newRequestSem,
			.clientQueue = clientQueue,
			.clientQueueMutex = &clientQueueMutex
		};

		threadArgs[i] = args;
		pthread_create_(&threads[i], &threadAttr, &threadFunc, &threadArgs[i]);
	}

	// queue requests until we're interrupted
	while (!sigint_received) {
		// accept new client,
		socklen_t clientAddrLen = sizeof(struct sockaddr_in);
		struct sockaddr_in* clientAddr = malloc(clientAddrLen);
		int clientSocket = ERR_NEG1_(
				accept(serverSocket, (struct sockaddr*) clientAddr, &clientAddrLen),
				EINTR);

		// if we get interrupted we assume it's by SIGINT and we stop the loop
		if (EINTR == errno) {
			// we need some extra cleanup now,
			// since we're doing the first part slightly different
			FREE(clientAddr);
			break;
		}

		// struct for new client's request
		ClientRequest* newClientRequest = (ClientRequest*) calloc(1, sizeof(ClientRequest));
		newClientRequest->clientSocket = clientSocket;
		newClientRequest->clientAddr = clientAddr;

		// receive client's request and put it in the struct
		recv_(clientSocket, newClientRequest->fileName, MAX_REQUEST_LEN, 0);

		// print request details
		printf_("Main thread accepted request: \"%s\" from %s\n",
				newClientRequest->fileName, inet_ntoa(clientAddr->sin_addr));

		// insert the request and signal the threads
		pthread_mutex_lock_(&clientQueueMutex);
		insertValLast(clientQueue, newClientRequest);
		pthread_mutex_unlock_(&clientQueueMutex);

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
	for (ClientRequest* clientRequest; myListLength(clientQueue);) {
		clientRequest = popFirstVal(clientQueue);
		FREE(clientRequest);
	}
	deleteMyList(clientQueue); 

	sem_destroy_(&newRequestSem);
	pthread_mutex_destroy_(&clientQueueMutex);
	close_(serverSocket);

	FREE(threadArgs);
	FREE(threads);

	return EXIT_SUCCESS;
}
