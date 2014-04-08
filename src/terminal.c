#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
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
		char *msg;
		char end = 0;
		while(!end){
		 	msg = malloc(30);
		 	printf("card code:\n> ");
		 	scanf("%16s",msg);
		 	scanf("%*[^\n]"); // clean stdin
			printf("->%s (r:%d,w:%d)\n",msg,readFD,writeFD);
			msg = message(msg,"Demande","0");
			if(strlen(msg) < strlen("|XXXXXXXXXXXXXXXX|Demande|0|\n")){ // 29
				end = 1;
				continue;
			}
			ecritLigne(writeFD,msg);
			free(msg);
			msg = litLigne(readFD);
			printf("=%s",msg);
			free(msg);
		}
		free(msg);
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

