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
		data = load("resources/annuaire.txt");
		char bankPath[20] = {0};
		char pipeName[64] = {0};
		sprintf(bankPath,"resources/bank%.4s",bankId);
		mkdir(bankPath,0755);
		
		sprintf(pipeName,"%s/localAuth.fifo",bankPath);
		mkfifo(pipeName,DEFAULT);
		int localDemand = open(pipeName,O_RDONLY);
		
		sprintf(pipeName,"%s/input.fifo",bankPath);
		mkfifo(pipeName,DEFAULT);
		int localResponse = open(pipeName,O_WRONLY);
		
		sprintf(pipeName,"%s/remoteAuthDemande.fifo",bankPath);
		mkfifo(pipeName,DEFAULT);
		int remoteDemand = open(pipeName,O_RDONLY);
		
		sprintf(pipeName,"%s/remoteAuthRéponse.fifo",bankPath);
		mkfifo(pipeName,DEFAULT);
		int remoteResponse = open(pipeName,O_WRONLY);
		
		int localPipe[] = {localDemand,localResponse};
		int remotePipe[] = {remoteDemand,remoteResponse};
		
		pthread_t local;
		pthread_create(&local, NULL, authenticate, localPipe);
		pthread_t remote;
		pthread_create(&remote, NULL, authenticate, remotePipe);
		
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
	fprintf(stderr,"Usage : %s -b <bankId>\n",programName);
}

void* authenticate(void* pipe_){
	int *pipe = pipe_;
	char* cardNumber = malloc(16+1);
	char* messageType = malloc(7+1);
	char* value = malloc(13+1); // only 13 digit needed for the richest of the world
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

