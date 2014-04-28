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
#include <pthread.h>
#include "../libCarteBancaire/lectureEcriture.h"
#include "../libCarteBancaire/message.h"

typedef struct{
	int authDemand;
	int input;
	int interResponse;
}RemotePipe;

const int DEFAULT = 0644;
struct option longopts[] = {
	{"bank",	required_argument, 0, 'b'}
};

static char* bankId;

void printHelp(const char* programName);
void* routeRemoteRequest(char* bankPath);
void* remoteResponse();

int main(int argc, char* argv[]){
	if(argc == 3){
		opterr = 0;
		int indexptr;
		int opt;
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
		char cardNumber[16+1];
		char messageType[7+1];
		char value[13+1]; // only 13 digit needed for the richest man of the world
		char* string;
		int end = 0;
		char bankPath[20] = {0};
		char fifoPath[64] = {0};
		sprintf(bankPath,"resources/bank%.4s",bankId);
		mkdir(bankPath,0755);

		sprintf(fifoPath,"%s/localAuth.fifo",bankPath);
		mkfifo(fifoPath,DEFAULT);
		int localAuth = open(fifoPath,O_WRONLY);

		sprintf(fifoPath,"%s/input.fifo",bankPath);
		mkfifo(fifoPath,DEFAULT);
		int bank = open(fifoPath,O_RDONLY);

		sprintf(fifoPath,"%s/interRemoteDemande.fifo",bankPath);
		mkfifo(fifoPath,DEFAULT);
		int localInter = open(fifoPath,O_WRONLY);
		pthread_t remoteThread;
		pthread_create(&remoteThread,NULL,remoteResponse,NULL);
		pthread_create(&remoteThread, NULL, (void* (*) (void*))routeRemoteRequest, (void*)&bankPath);
		
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
				char fifo[64] = {0}; // resources/ + card code + .fifo + '\0' = 32
				sprintf(fifo,"%s/%s.fifo",bankPath,cardNumber);
				int term = open(fifo,O_WRONLY);
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

void* routeRemoteRequest(char* bankPath){
	char remoteFifo[64];
	RemotePipe remote;

	sprintf(remoteFifo,"%s/remoteAuthDemande.fifo",bankPath);
	mkfifo(remoteFifo,DEFAULT);
	remote.authDemand = open(remoteFifo,O_WRONLY);

	sprintf(remoteFifo,"%s/remoteInput.fifo",bankPath);
	mkfifo(remoteFifo,DEFAULT);
	remote.input = open(remoteFifo,O_RDONLY);

	sprintf(remoteFifo,"%s/interRéponse.fifo",bankPath);
	mkfifo(remoteFifo,DEFAULT);
	remote.interResponse = open(remoteFifo,O_WRONLY);

	char cardNumber[16+1];
	char messageType[7+1];
	char value[13+1]; // only 13 digit needed for the richest man of the world
	char* string;
	int end = 0;
	while(!end){
		string = litLigne(remote.input);
		if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
			perror("(remote acquisition) message in wrong format");
			end = 1;
			continue;
		}
		if(strcmp(messageType,"Demande") == 0){
			ecritLigne(remote.authDemand,string);
		}else{
			ecritLigne(remote.interResponse,string);
		}
		free(string);
	}
 return NULL;
}

void* remoteResponse(){
	char bankPath[32] = {0};
	sprintf(bankPath,"resources/bank%.4s",bankId);
	char fifoPath[64] = {0};
	sprintf(fifoPath,"%s/remoteResponse.fifo",bankPath);
	mkfifo(fifoPath,DEFAULT);
	int remoteResponseFD = open(fifoPath,O_RDONLY);
	
	
	int end = 0;
	while(!end){
		char cardNumber[16+1];
		char messageType[7+1];
		char value[13+1]; // only 13 digit needed for the richest man of the world
		char* string = litLigne(remoteResponseFD);
		if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
			perror("(acquisition(remote response))message in wrong format");
			fprintf(stderr,"%s:%d: message: %s\n",__FILE__,__LINE__, string);
			end = 1;
			continue;
		}
	
		sprintf(fifoPath,"%s/%s.fifo",bankPath,cardNumber);
		mkfifo(fifoPath,DEFAULT);
		int term = open(fifoPath,O_WRONLY);

		if(term == -1){
			perror("miaou");
			fprintf(stderr,"%s:%d: pipe (%s)\n",__FILE__,__LINE__,string);
		}
		ecritLigne(term,string);
		close(term);
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

