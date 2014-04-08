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
		close(STDIN);
		close(STDOUT);
		dup2(writeFD, STDOUT);
		dup2(readFD, STDIN);
		close(writeFD);
		close(readFD);
		char* string;
		do{}while(!(string = litLigne(STDIN)));

		char* cardNumber = malloc(16); cardNumber[0] = '\0';
		char* messageType = malloc(7); messageType[0] = '\0';
		char* value = malloc(100); value[0] = '\0';
		printf("découpage de: %s",string);
		if(decoupe(string,cardNumber,messageType,value) == 0){
			perror("decoupeee");
		}
		printf("\n%s\n%s\n%s\n",cardNumber,bankId,strcmp(bankId,cardNumber)?"who are you?":"i know you!");
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
