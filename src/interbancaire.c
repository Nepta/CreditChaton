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
#include "annuaire.h"

static const int DEFAULT = 0644;
static int bank[10000];
int searchBank(char bankId[5]);
void* connection(int pipe[2]);

typedef struct{
	int interResponse;
	int interDemand;
	int bankResponse;
}ConnectionPipe;

typedef struct{
	ConnectionPipe *pipe;
	char* string;
}RemoteAuthData;

void* remoteAuth();
static int threadPoolPipe[2];

int main(int argc, char* argv[]){
	int bankList[] = {0000,0001};
	int bankListSize = 2;
	int poolSize = 9;
	pipe(threadPoolPipe);
	
	pthread_t threadId[bankListSize];
	
	for(int i=0; i<bankListSize; i++){
		char fifoPath[64] = {0};
		int *remotePipe = malloc(2*sizeof (int));
		sprintf(fifoPath,"resources/interRemoteDemande%.4d.fifo",bankList[i]);
		mkfifo(fifoPath,DEFAULT);
		remotePipe[READ] = open(fifoPath,O_RDONLY);
	
		sprintf(fifoPath,"resources/réponse%.4d.fifo",bankList[i]);
		mkfifo(fifoPath,DEFAULT);
		remotePipe[WRITE] = open(fifoPath,O_WRONLY);
		threadId[i] = createThread(connection,remotePipe);
	}
	
	for(int i=0; i<poolSize; i++){
		pthread_t threadId;
		pthread_create(&threadId, NULL, remoteAuth, NULL);
	}
	
	for(int i=0; i<bankListSize; i++){
		pthread_join(threadId[i],NULL);
	}
		
 return 0;
}

int searchBank(char bankId[5]){
	bankId[4] = '\0';
	return bank[atoi(bankId)];
}

void* connection(int associatedBank[2]){
	char cardNumber[16];
	char messageType[7];
	char value[14]; // only 13 digit needed for the richest man of the world
	int end = 0;
	while(!end){
		char* string = litLigne(associatedBank[READ]);
		if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
			perror("(interbancaire(connection))message is wrong format");
			end = 1;
			break;
		}
	
		ConnectionPipe *remotePipe = malloc(sizeof (ConnectionPipe));
		remotePipe->bankResponse = associatedBank[WRITE];
	
		char fifoPath[64] = {0};
		sprintf(fifoPath,"resources/interDemande%.4s.fifo",cardNumber+1);
		mkfifo(fifoPath,DEFAULT);
		remotePipe->interDemand = open(fifoPath,O_WRONLY);
	
		sprintf(fifoPath,"resources/interRéponse%.4s.fifo",cardNumber+1);
		mkfifo(fifoPath,DEFAULT);
		remotePipe->interResponse = open(fifoPath,O_WRONLY);
		RemoteAuthData *data = malloc(sizeof (RemoteAuthData));
		data->pipe = remotePipe;
		data->string = string;
		write(threadPoolPipe[WRITE], &data, sizeof (void*));
	}
	return (void*)1;
}

void* remoteAuth(){
	RemoteAuthData *data;
	while(read(threadPoolPipe[READ], &data, sizeof (void*)) != -1){
		ConnectionPipe *remotePipe = data->pipe;
		char* string = data->string;
		ecritLigne(remotePipe->interDemand, string);
		free(string);
		string = litLigne(remotePipe->interResponse);
		ecritLigne(remotePipe->bankResponse, string);
		free(remotePipe);
		free(string);
		free(data);
	}
 return 0;
}

