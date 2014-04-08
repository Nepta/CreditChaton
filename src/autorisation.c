#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "../libCarteBancaire/lectureEcriture.h"
#include "../libCarteBancaire/message.h"

#define STDIN 0
#define STDOUT 1

struct option longopts[] = {
	{"input",	required_argument, 0, 'i'},
	{"output",	required_argument, 0, 'o'},
	{"bank",		required_argument, 0, 'b'}
};

void printHelp(const char* programName);

int main(int argc, char* argv[]){
	for(int i=0; i<argc; i++){
		printf("%s ",argv[i]);
	}
	printf("\n");
	if(argc == 7){
		opterr = 0;
		int indexptr;
		int opt;
		int readFD, writeFD;
		char* bankId;
		while((opt = getopt_long(argc, argv, "i:o:b:",longopts, &indexptr)) != -1){
			switch(opt){
				case 'i':
					readFD = atoi(optarg);
					break;
				case 'o':
					writeFD = atoi(optarg);
					break;
				case 'b':
					bankId = optarg;
					break;
				default:
					printHelp(argv[0]);
					break;
			}
		}
		char* cardNumber = malloc(16);
		char* messageType = malloc(7);
		char* value = malloc(100);
		char* string;
		char ack[6];
		char end = 0;
		while(!end){
			cardNumber[0] = '\0';
			messageType[0] = '\0';
			value[0] = '\0';
			string = litLigne(readFD);
			if(decoupe(string,cardNumber,messageType,value) == 0){
				perror("message in wrong format");
				end = 1;
			}
			if(strcmp(bankId,cardNumber) == 0){
				strcpy(ack,"ACK\n");
			}else{
				strcpy(ack,"NACK\n");
			}
			ecritLigne(writeFD,ack);
		}
		free(string);
		free(cardNumber);
		free(messageType);
		free(value);
	}else{
		printHelp(argv[0]);
	}
 return argc != 7;
}

void printHelp(const char* programName){
	printf(	"Usage : %s [OPTION]...\n"
				"  -i,--input\t file descriptor to read into (mandatory)\n"
				"  -o,--output\t file descriptor to write into (mandatory)\n"
				"  -b,--bank\t bank id (mandatory)\n"
			,programName);
}
