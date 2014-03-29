/**
 * acquisition server, get demand and route them to rigth server
 * \param arg[1] bank id which this server belong
 * \param arg[2] max memory server must use
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "communicationThread.h"

int maxMemory;
static pthread_mutex_t alloc_lock;

struct charMemory{
	unsigned char size;
	char* data[];
};

struct generalMemory{
	unsigned char size;
	void* data[];
};

typedef union{
	struct charMemory message;
	struct generalMemory generic;
}Memory;


typedef struct{
	int in;
	int out;
}Direction;

typedef struct{
	Direction terminal;
	Direction authorisation;
	Direction interbancaire;
}Route;

/**
 * try to allocate memory respecting the maximum memory the server must use
 * \param size size of memory we want to allocate
 * \return a pointer to the allocated memory or NULL if no more memory is available
 */

Memory* constrainedMalloc(size_t size){
	pthread_mutex_lock(&alloc_lock);
	if((int)(maxMemory - (size + sizeof (Memory))) > 0){
		maxMemory -= size + sizeof (Memory);
		Memory *memory = malloc(size + sizeof (Memory));
		memory->generic.size = size;
		pthread_mutex_unlock(&alloc_lock);
		return memory;
	}else{
		pthread_mutex_unlock(&alloc_lock);
		errno = ENOMEM;
		perror("no memory left");
		return NULL;
	}
}

/**
 * unallocated memory and tell it to others part of process
 * \param memory a Memory to unallocate
 */

void constrainedFree(Memory* memory){
	maxMemory += memory->generic.size + sizeof (Memory);
	free(memory);
}

const int DEFAULT = 0644;

void closeAll(Route route){
	close(route.terminal.in);
	close(route.terminal.out);
	close(route.authorisation.in);
	close(route.authorisation.out);
	close(route.interbancaire.in);
	close(route.interbancaire.out);
}


int main(int argc, char* argv[]){
	if(argc == 3){
		maxMemory = atoi(argv[2]);
		int bankId = atoi(argv[1]);
		pid_t serverId = getpid();
		Memory *serverHash = constrainedMalloc(10);
		Memory *fifoName = constrainedMalloc(250);
		serverHash->message.data[0] = '\0';
/*		snprintf(serverHash->message.data,10,"%d%d", bankId, serverId);*/
		snprintf(serverHash->message.data,10,"%d", bankId);
		Route route;
		// create reading file (for incoming message)
		fifoName->message.data[0] = '\0';
		mkfifo(strncat(strncat(fifoName->message.data,"resources/termIn",24),serverHash->message.data,24),DEFAULT); //Terminal -> this
		route.terminal.in = open(fifoName->message.data,O_RDONLY);
		
		fifoName->message.data[0] = '\0';
		mkfifo(strncat(strncat(fifoName->message.data,"resources/bankIn",24),serverHash->message.data,24),DEFAULT); //Interbancaire -> this
		route.interbancaire.in = open(fifoName->message.data,O_RDONLY);
		
		fifoName->message.data[0] = '\0';
		mkfifo(strncat(strncat(fifoName->message.data,"resources/authIn",24),serverHash->message.data,24),DEFAULT); //authorisation -> this
		route.authorisation.in = open(fifoName->message.data,O_RDONLY);

		// create writing file (for outgoing message)
		fifoName->message.data[0] = '\0';
		mkfifo(strncat(strncat(fifoName->message.data,"resources/termOut",24),serverHash->message.data,24),DEFAULT); //Terminal -> this
		route.terminal.out = open(fifoName->message.data,O_WRONLY);
		
		fifoName->message.data[0] = '\0';
		mkfifo(strncat(strncat(fifoName->message.data,"resources/bankOut",24),serverHash->message.data,24),DEFAULT); //Interbancaire -> this
		route.interbancaire.out = open(fifoName->message.data,O_WRONLY);
		
		fifoName->message.data[0] = '\0';
		mkfifo(strncat(strncat(fifoName->message.data,"resources/authOut",24),serverHash->message.data,24),DEFAULT); //authorisation -> this
		route.authorisation.out = open(fifoName->message.data,O_WRONLY);


		// do some computation
		char* string;
		do{}while(!(string = litLigne(route.terminal.in)));
		ecritLigne(route.terminal.out,string);
		printf("terminal: %s\n",string);
		free(string);
		
		do{}while(!(litLigne(route.interbancaire.in)));
		ecritLigne(route.interbancaire.out,string);
		printf("interbancaire: %s\n",string);
		free(string);
		
		do{}while(!(litLigne(route.authorisation.in)));
		ecritLigne(route.authorisation.out,string);
		printf("authorisation: %s\n",string);
		free(string);

		
		// delete fifo file
		fifoName->message.data[0] = '\0';
		unlink(strncat(strncat(fifoName->message.data,"resources/termIn",24),serverHash->message.data,24));
		
		fifoName->message.data[0] = '\0';
		unlink(strncat(strncat(fifoName->message.data,"resources/bankIn",24),serverHash->message.data,24));
		
		fifoName->message.data[0] = '\0';
		unlink(strncat(strncat(fifoName->message.data,"resources/authIn",24),serverHash->message.data,24));
		
		fifoName->message.data[0] = '\0';
		unlink(strncat(strncat(fifoName->message.data,"resources/termOut",24),serverHash->message.data,24));
		
		fifoName->message.data[0] = '\0';
		unlink(strncat(strncat(fifoName->message.data,"resources/bankOut",24),serverHash->message.data,24));
		
		fifoName->message.data[0] = '\0';
		unlink(strncat(strncat(fifoName->message.data,"resources/authOut",24),serverHash->message.data,24));
		
		constrainedFree(serverHash);
		constrainedFree(fifoName);
	}else{
		printf("usage:\n%s <bankId> "
				 "<max memory usage>\n",argv[0]);
	}
 return argc == 3;
}
