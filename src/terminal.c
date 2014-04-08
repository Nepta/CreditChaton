#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include "../libCarteBancaire/lectureEcriture.h"
#include "../libCarteBancaire/message.h"

struct option longopts[] = {
	{"input",	required_argument, 0, 'i'},
	{"output",	required_argument, 0, 'o'}
};

void printHelp(const char* programName);

int main(int argc, char* argv[]){
	if(argc == 5){
		opterr = 0;
		int indexptr;
		int opt;
		int readFD, writeFD;
		while((opt = getopt_long(argc, argv, "i:o:",longopts, &indexptr)) != -1){
			switch(opt){
				case 'i':
					readFD = atoi(optarg);
					break;
				case 'o':
					writeFD = atoi(optarg);
					break;
				default:
					printHelp(argv[0]);
					break;
			}
		}
/*		char* cardNumber = malloc(16);*/
/*		char* messageType = malloc(7);*/
/*		char* value = malloc(100);*/
/*		char* string;*/
/*		char end = 0;*/
/*		while(!end){*/
/*			cardNumber[0] = '\0';*/
/*			messageType[0] = '\0';*/
/*			value[0] = '\0';*/
/*			string = litLigne(readFD);*/
/*			if(decoupe(string,cardNumber,messageType,value) == 0){*/
/*				perror("message in wrong format");*/
/*				end = 1;*/
/*			}*/
/*			if(strcmp(bankId,cardNumber) == 0){*/
/*				strcpy(ack,"ACK\n");*/
/*			}else{*/
/*				strcpy(ack,"NACK\n");*/
/*			}*/
			char* msg = message("0234567890123456","Réponse","9");
			ecritLigne(writeFD,msg);
			free(msg);
			msg = litLigne(readFD);
			printf("%s",msg);
			free(msg);
/*		}*/
/*		free(string);*/
/*		free(cardNumber);*/
/*		free(messageType);*/
/*		free(value);*/
	}else{
		printHelp(argv[0]);
	}
 return 0;
}

void printHelp(const char* programName){
	fprintf(	stderr,
				"Usage : %s [OPTION]...\n"
				"  -i,--input\t file descriptor to read into (mandatory)\n"
				"  -o,--output\t file descriptor to write into (mandatory)\n",
				programName
	);
}

