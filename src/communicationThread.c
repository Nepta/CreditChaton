#include "communicationThread.h"
#include <unistd.h>
#include <stdlib.h>

pthread_t createThread(void* (*start_routine)(int*), int parentPipe[2]){
	pthread_t threadId;
	int *childPipe = malloc(2 * sizeof (int));
	pipe(parentPipe);
	pipe(childPipe);
	int writePipe = parentPipe[WRITE];
	parentPipe[WRITE] = childPipe[WRITE];
	childPipe[WRITE] = writePipe;

	pthread_create(&threadId, NULL, (void*(*)(void*))start_routine, (void*)childPipe);
	return threadId;
}
