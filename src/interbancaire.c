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

static int bank[10000];
int searchBank(char bankId[5]);
int main(int argc, char* argv[]){
	mkfifo("resources/interbancaire",0644);
/*	mkfifo("resources/bank0234",0644);*/
	int interbancaire = open("resources/interbancaire",O_RDONLY);
/*	bank[1234] = open("resources/bank0234",O_WRONLY);*/
	bank[1234] = open("resources/acquisition.fifo",O_WRONLY);
	int end = 0;
	char* cardNumber = malloc(16);
	char* messageType = malloc(7);
	char* value = malloc(14); // only 13 digit needed for the richest man of the world
	while(!end){
		char* string = litLigne(interbancaire);
		if(string == NULL || decoupe(string,cardNumber,messageType,value) == 0){
			perror("(interbancaire)message is wrong format");
			end = 1;
			continue;
		}
		int destinationBank = searchBank(cardNumber);
		ecritLigne(destinationBank,string);
		free(string);
	}
 return 0;
}

int searchBank(char bankId[5]){
	bankId[4] = '\0';
	return bank[atoi(bankId)];
}
