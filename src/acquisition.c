/**
 * acquisition server, get demand and route them to rigth server
 * \param arg[1] bank id which this server belong
 * \param arg[2] max memory server must use
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include "communicationThread.h"
#include "../libCarteBancaire/lectureEcriture.h"
#include "../libCarteBancaire/message.h"

typedef struct{
	int auth;
	int router;
	int inter;
}RemotePipe;

const int DEFAULT = 0644;
struct option longopts[] = {
	{"bank",	required_argument, 0, 'b'}
};

void printHelp(const char* programName);
void* routeRemoteRequest(void* pipe);

int main(int argc, char* argv[]){
	if(argc == 3){
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
		char cardNumber[16];
		char messageType[7];
		char value[14]; // only 13 digit needed for the richest man of the world
		char* string;
		int end = 0;
		char fifoPath[64] = {0};
		
		sprintf(fifoPath,"resources/%.4s.fifo",bankId);
		mkfifo(fifoPath,DEFAULT);
		int bank = open(fifoPath,O_RDONLY);
		
		sprintf(fifoPath,"resources/localAuth%.4s.fifo",bankId);
		mkfifo(fifoPath,DEFAULT);
		int localAuth = open(fifoPath,O_WRONLY);
		
		RemotePipe remotePipes;
		
		sprintf(fifoPath,"resources/remoteAuth%.4s.fifo",bankId);
		mkfifo(fifoPath,DEFAULT);
		remotePipes.auth = open(fifoPath,O_RDWR);
		
		sprintf(fifoPath,"resources/remoteRouter%.4s.fifo",bankId);
		mkfifo(fifoPath,DEFAULT);
		remotePipes.router = open(fifoPath,O_RDWR);
		
		sprintf(fifoPath,"resources/remoteInter%.4s.fifo",bankId);
		mkfifo(fifoPath,DEFAULT);
		remotePipes.inter = open(fifoPath,O_RDWR);
		
		
		sprintf(fifoPath,"resources/localInter%.4s.fifo",bankId);
		mkfifo(fifoPath,DEFAULT);
		int localInter = open(fifoPath,O_RDWR);
		
		pthread_t remoteThread;
		pthread_create(&remoteThread, NULL, routeRemoteRequest, &remotePipes);
		
		while(!end){
			string = litLigne(bank);
			if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
				perror("(acquisition)message in wrong format");
				end = 1;
				continue;
			}
			if(strcmp(messageType,"Demande") == 0){ //from terminal
				if(strncmp(cardNumber,bankId,4) == 0){ // to autorisation
					ecritLigne(localAuth,string);
				}else{ // to interbancaire
					ecritLigne(localInter,string);
				}
			}else{  //from autorisation / to terminal
				char* fifo = malloc(10+16+5+1); // resources/ + card code + .fifo + '\0' = 32
				snprintf(fifo,32,"resources/%s.fifo",cardNumber);
				int term = open(fifo,O_WRONLY);
				free(fifo);
				ecritLigne(term,string);
				close(term);
			}
			free(string);
		}
		
		if(pthread_join(remoteThread,NULL)){
			perror("local auth");
		}
	}else{
		printHelp(argv[0]);
	}
 return 0;
}

void* routeRemoteRequest(void* pipes_){
	RemotePipe *remote = pipes_;
	char cardNumber[16];
	char messageType[7];
	char value[14]; // only 13 digit needed for the richest man of the world
	char* string;
	int end = 0;
	while(!end){
		string = litLigne(remote->router);
		if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
			perror("(remote acquisition)message in wrong format");
			end = 1;
			continue;
		}
		if(strcmp(messageType,"Demande") == 0){
			ecritLigne(remote->auth,string);
		}else{
			ecritLigne(remote->inter,string);
		}
		free(string);
	}
 return NULL;
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


