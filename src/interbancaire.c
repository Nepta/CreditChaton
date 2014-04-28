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
static pthread_mutex_t bank[10000] = {PTHREAD_MUTEX_INITIALIZER};
void* connection(int pipe[2]);
void printHelp(char* programName);

struct option longopts[] = {
	{"file", required_argument, 0, 'f'},
	{"jobs", required_argument, 0, 'j'}
};

typedef struct{
	int interResponse;
	int interDemand;
	int bankResponse;
	int bankId;
}ConnectionPipe;

typedef struct{
	ConnectionPipe *pipe;
	char* string;
}RemoteAuthData;

void* remoteAuth();
static int threadPoolPipe[2];

int main(int argc, char* argv[]){
	int poolSize = 1;
	opterr = 0;
	int indexptr;
	int opt;
	while((opt = getopt_long(argc, argv, "j:f:",longopts, &indexptr)) != -1){
		switch(opt){
			case 'j':
				poolSize = atoi(optarg);
				break;
			case 'f':
/*				bankList = open(optarg,O_RDONLY|O_NONBLOCK);*/
				break;
			default:
				printHelp(argv[0]);
				return argc;
		}
	}
	char* bankList[] = {"0000","1111"};
	int bankListSize = 2;
	pipe(threadPoolPipe);
	
	pthread_t threadId[bankListSize];
	for(int i=0; i<bankListSize; i++){
		char bankPath[20] = {0};
		sprintf(bankPath,"resources/bank%.4s",bankList[i]);
		mkdir(bankPath,0755);
		char fifoPath[64] = {0};
		int *remotePipe = malloc(2*sizeof (int));

		sprintf(fifoPath,"%s/interRemoteDemande.fifo",bankPath);
		mkfifo(fifoPath,DEFAULT);
		remotePipe[READ] = open(fifoPath,O_RDONLY);

		sprintf(fifoPath,"%s/remoteResponse.fifo",bankPath);
		mkfifo(fifoPath,DEFAULT);
		remotePipe[WRITE] = open(fifoPath,O_WRONLY);
		pthread_create(&threadId[i], NULL, (void* (*) (void*))connection, (void*)remotePipe);
	}
	
	for(int i=0; i<poolSize; i++){
		pthread_t threadId;
		pthread_create((&threadId) + (i*sizeof (pthread_t)), NULL, remoteAuth, NULL);
	}
	
	for(int i=0; i<bankListSize; i++){
		pthread_join(threadId[i],NULL);
	}
		
 return 0;
}

void* connection(int *associatedBank_){
	int associatedBank[] = {associatedBank_[0], associatedBank_[1]};
	char cardNumber[16+1];
	char messageType[7+1];
	char value[13+1]; // only 13 digit needed for the richest man of the world
	int end = 0;
	while(!end){
		errno = 0;
		char* string = litLigne(associatedBank[READ]);
		if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
			perror("(interbancaire(connection)) message is wrong format");
			end = 1;
			break;
		}
	
		ConnectionPipe *remotePipe = malloc(sizeof (ConnectionPipe));
		remotePipe->bankResponse = dup(associatedBank[WRITE]);
		
		char bankId[5];
		sprintf(bankId,"%.4s",cardNumber);
		remotePipe->bankId = atoi(bankId);
		
		char bankPath[20] = {0};
		sprintf(bankPath,"resources/bank%.4s",bankId);
		mkdir(bankPath,0755);
		char fifoPath[64] = {0};
		sprintf(fifoPath,"%s/remoteInput.fifo",bankPath);
		mkfifo(fifoPath,DEFAULT);
		remotePipe->interDemand = open(fifoPath,O_WRONLY);

		sprintf(fifoPath,"%s/interRéponse.fifo",bankPath);
		mkfifo(fifoPath,DEFAULT);
		remotePipe->interResponse = open(fifoPath,O_RDONLY);
		
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
		pthread_mutex_lock(bank+remotePipe->bankId);
		ecritLigne(remotePipe->interDemand, string);
		free(string);
		string = litLigne(remotePipe->interResponse);
		pthread_mutex_unlock(bank+remotePipe->bankId);
		ecritLigne(remotePipe->bankResponse, string);
		close(remotePipe->interDemand);
		close(remotePipe->interResponse);
		close(remotePipe->bankResponse);
		free(remotePipe);
		free(string);
		free(data);
	}
 return 0;
}

void printHelp(char* programName){
	fprintf(	stderr,
				"Usage : %s [OPTION]...\n"
				"  -f,--file\t a file containing a list of bankId\n"
				"  -j,--jobs\t number of slot available for concurrent routing\n",
				programName
	);
}

