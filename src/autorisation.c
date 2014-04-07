#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libCarteBancaire/lectureEcriture.h"
#include <getopt.h>

struct option longopts[] = {
	{"input",	required_argument, 0, 'i'},
	{"output",	required_argument, 0, 'o'},
	{"bank",		required_argument, 0, 'b'}
};

void printHelp(const char* programName);

int main(int argc, char* argv[]){
	if(argc == 7){
		opterr = 0;
		int indexptr;
		int opt;
		int writeFD, readFD;
		while((opt = getopt_long(argc, argv, "i:o:b:",longopts, &indexptr)) != -1){
			printf("option: %c - %s\n",opt,optarg);
			switch(opt){
				case 'i':
					break;
				case 'o':
					writeFD = atoi(optarg);
					break;
				case 'b':
					readFD = atoi(optarg);
					break;
				default:
					printHelp(argv[0]);
					break;
			}
		}
		dup2(readFD, 0);
		dup2(writeFD, 1);
		close(writeFD);
		close(readFD);
/*		...	*/
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
