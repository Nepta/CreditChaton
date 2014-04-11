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

static int bank[10000];
int searchBank(char bankId[5]);
void* connection(int pipe[2]);

int main(int argc, char* argv[]){
	int interbancaire[2];
	mkfifo("resources/interbancaire.fifo",0644);
/*	mkfifo("resources/bank0234",0644);*/
	interbancaire[READ] = open("resources/interbancaire.fifo",O_RDONLY);
/*	bank[1234] = open("resources/bank0234",O_WRONLY);*/
	interbancaire[WRITE] = open("resources/acquisition.fifo",O_WRONLY);
	void* end = 0;
	while(!end){
		end = connection(interbancaire);
	}
 return 0;
}

int searchBank(char bankId[5]){
	bankId[4] = '\0';
	return bank[atoi(bankId)];
}

void* connection(int pipe[2]){
	char cardNumber[16];
	char messageType[7];
	char value[14]; // only 13 digit needed for the richest man of the world
	char* string = litLigne(pipe[READ]);
	if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
		perror("(interbancaire)message is wrong format");
		return 0;
	}
	free(string);
	string = message(cardNumber,"Réponse",value);
	ecritLigne(pipe[WRITE],string);
	free(string);
	return (void*)1;
}

