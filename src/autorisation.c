#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libCarteBancaire/lectureEcriture.h"
#include "../libCarteBancaire/message.h"
#include "communicationThread.h"
#include "annuaire.h"

#define STDIN 0
#define STDOUT 1

const int DEFAULT = 0644;
const int ACK = 1;
const int NACK = 0;

static DirectoryService *data;

struct option longopts[] = {
	{"bank",	required_argument, 0, 'b'}
};

void printHelp(const char* programName);
void* authenticate(void* pipe);

int main(int argc, char* argv[]){
	if(argc == 2){
		opterr = 0;
		int indexptr;
		int opt;
		char* bankId;
		while((opt = getopt_long(argc, argv, "b:",longopts, &indexptr)) != -1){
			switch(opt){
				case 'b':
					bankId = optarg;
					break;
				default:
					printHelp(argv[0]);
					break;
			}
		}
		data = load("resources/annuaire.txt");
		char pipeName[23];
		strncpy(pipeName,"localAuth",9);
		strncat(pipeName,bankId,4);
		strncat(pipeName,".fifo",5);
		mkfifo(pipeName,DEFAULT);
		int localAuth = open(pipeName,O_RDONLY);
		
		strncpy(pipeName,"localRouter",11);
		strncat(pipeName,bankId,4);
		strncat(pipeName,".fifo",5);
		mkfifo(pipeName,DEFAULT);
		int localRouter = open(pipeName,O_WRONLY);
		
		strncpy(pipeName,"remoteAuth",10);
		strncat(pipeName,bankId,4);
		strncat(pipeName,".fifo",5);
		mkfifo(pipeName,DEFAULT);
		int remoteAuth = open(pipeName,O_RDONLY);
		
		strncpy(pipeName,"remoteRouter",13);
		strncat(pipeName,bankId,4);
		strncat(pipeName,".fifo",5);
		mkfifo(pipeName,DEFAULT);
		int remoteRouter = open(pipeName,O_WRONLY);
		
		int localPipe[] = {localAuth,localRouter};
		int remotePipe[] = {remoteAuth,remoteRouter};
		pthread_t local = createThread(authenticate,localPipe);
		pthread_t remote = createThread(authenticate,remotePipe);
		
		if(pthread_join(local,NULL)){
			perror("local auth");
		}
		
		if(pthread_join(remote,NULL)){
			perror("remote auth");
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
				"  -o,--output\t file descriptor to write into (mandatory)\n"
				"  -b,--bank\t bank id (mandatory)\n",
				programName
	);
}

void* authenticate(void* pipe_){
	int *pipe = pipe_;
	char* cardNumber = malloc(16);
	char* messageType = malloc(7);
	char* value = malloc(14); // only 13 digit needed for the richest of the world
	char* string;
	char end = 0;
	while(!end){
		cardNumber[0] = '\0';
		messageType[0] = '\0';
		value[0] = '\0';
		string = litLigne(pipe[READ]);
		if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
			perror("(autorisation)message in wrong format");
			fprintf(stderr,"%s\n",string);
			end = 1;
		}
		if(exist(data,cardNumber)){
			sprintf(string,"|%s|Réponse|%d|\n",cardNumber,ACK);
		}else{
			sprintf(string,"|%s|Réponse|%d|\n",cardNumber,NACK);
		}
		ecritLigne(pipe[WRITE],string);
		free(string);
	}
	return NULL;
}

