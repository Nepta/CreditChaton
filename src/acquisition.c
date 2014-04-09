/**
 * acquisition server, get demand and route them to rigth server
 * \param arg[1] bank id which this server belong
 * \param arg[2] max memory server must use
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include "communicationThread.h"
#include "../libCarteBancaire/lectureEcriture.h"
#include "../libCarteBancaire/message.h"


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

struct option longopts[] = {
	{"input",	required_argument, 0, 'i'},
	{"output",	required_argument, 0, 'o'}
};

void printHelp(const char* programName);

int main(int argc, char* argv[]){
	const char* bankId = "0234567890123456";
	if(argc == 5){
		opterr = 0;
		int indexptr;
		int opt;
		int readFD, writeFD;
		while((opt = getopt_long(argc, argv, "i:o:",longopts, &indexptr)) != -1){
			switch(opt){
				case 'i':
					readFD = atoi(optarg);
					break;
				case 'o':
					writeFD = atoi(optarg);
					break;
				default:
					printHelp(argv[0]);
					break;
			}
		}
		char* cardNumber = malloc(16);
		char* messageType = malloc(7);
		char* value = malloc(14); // only 13 digit needed for the richest of the world
		char* string;
		int end = 0;
		while(!end){
			string = litLigne(readFD);
			if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
				perror("(acquisition)message in wrong format");
				end = 1;
				continue;
			}
			if(strncmp(cardNumber,bankId,4) == 0){
				ecritLigne(writeFD,string);
			}
			free(string);
		}
	}else{
		printHelp(argv[0]);
	}
 return 0;
}

void printHelp(const char* programName){
	fprintf(	stderr,
				"Usage : %s [OPTION]...\n"
				"  -i,--input\t file descriptor to read into (mandatory)\n"
				"  -o,--output\t file descriptor to write into (mandatory)\n",
				programName
	);
}


