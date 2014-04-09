#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
		char* msg;
		char* string;
		char end = 0;
		while(!end){
		 	msg = malloc(10+16+5+1); // resources/ + card code + .fifo + '\0'
		 	printf("card code:\n> ");
		 	scanf("%16s",msg);
		 	scanf("%*[^\n]"); // clean stdin
/*			strcpy(msg,"0234567890123456");*/
			string = message(msg,"Demande","0");
			if(strlen(string) < strlen("|XXXXXXXXXXXXXXXX|Demande|0|\n")){ // 29
				end = 1;
				continue;
			}
			ecritLigne(writeFD,string);
			
			snprintf(msg,32,"resources/%.16s.fifo",string+1);
			mkfifo(msg,0644);
			readFD = open(msg,O_RDONLY);
			free(string);
			string = litLigne(readFD);
			close(readFD);
			unlink(msg);
			free(msg);
			
			int ack = (int)(string[27] - '0');
			if(ack){
				printf("transaction accepted\n");
			}else{
				printf("transaction refused\n");
			}
			free(string);
		}
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

