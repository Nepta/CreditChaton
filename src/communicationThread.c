#include "communicationThread.h"

pthread_t* createThread(void* (*start_routine)(void*), int *parentPipe[2]){
	pthread_t *threadId;
	int *childPipe[2];
	pipe(childPipe);
	
	int writePipe = *parentPipe[WRITE];
	*parentPipe[WRITE] = *childPipe[WRITE];
	*childPipe[WRITE] = fd;
		
	pthread_create(threadId, start_routine,childPipe);
	return threadId;
}
