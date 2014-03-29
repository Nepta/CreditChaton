#ifndef __communicationThread_H__
#define __communicationThread_H__

#include <pthread.h>
static const int READ = 0;
static const int WRITE = 1;

pthread_t* createThread(void* (*start_routine), int *pipe[2]);


#endif /* __communicationThread_H__ */

