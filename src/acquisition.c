/**
 * acquisition server, get demand and route them to rigth server
 * \param arg[1] bank id which this server belong
 * \param arg[2] max memory server must use
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int maxMemory;


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

/**
 * try to allocate memory respecting the maximum memory the server must use
 * \param size size of memory we want to allocate
 * \return a pointer to the allocated memory or NULL if no more memory is available
 */

Memory* constrainedMalloc(size_t size){
	if((int)(maxMemory - (size + sizeof (Memory))) > 0){
		maxMemory -= size + sizeof (Memory);
		Memory *memory = malloc(size + sizeof (Memory));
		memory->message.size = size;
		return memory;
	}else{
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

int main(int argc, char* argv[]){
	if(argc == 3){
		maxMemory = atoi(argv[2]);
		int bankId = atoi(argv[1]);
		pid_t serverId = getpid();
		Memory *serverHash = constrainedMalloc(10);
		serverHash->message.data[0] = '\0';
		snprintf((char*)(&serverHash->message.data),10,"%d%d", bankId, serverId);
		
		constrainedFree(serverHash);
	}else{
		printf("usage:\n%s <bankId> "
				 "<max memory usage>\n",argv[0]);
	}
 return argc == 3;
}
