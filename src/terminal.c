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
	{"bank",	required_argument, 0, 'o'}
};

static const int DEFAULT = 0644;

void printHelp(const char* programName);

int main(int argc, char* argv[]){
	if(argc == 3){
		opterr = 0;
		int indexptr;
		int opt;
		char* bankId;
		while((opt = getopt_long(argc, argv, "b:",longopts, &indexptr)) != -1){
			switch(opt){
				case 'b':
					bankId = optarg;
					break;
				default:
					printHelp(argv[0]);
					break;
			}
		}
		char* string;
		char end = 0;
		char bankFifo[64];
		char responseFifo[33];
		
		sprintf(bankFifo,"resources/bank%.4s/input.fifo",bankId);
		mkfifo(bankFifo,DEFAULT);
		int bank = open(bankFifo,O_WRONLY);
		char accountId[17];
		char money[14];
		int i = 0;
		while(!end){
			i++;
			accountId[0] = '\0';
			money[0] = '\0';
		 	printf("card code:\n> ");
		 	fflush(stdout);
		 	scanf("%16s%13s",accountId,money);
		 	scanf("%*[^\n]"); // clean stdin
			if(strlen(money) < 13){
				end = 1;
				continue;
			}
			string = message(accountId,"Demande",money);
			ecritLigne(bank,string);
			
			sprintf(responseFifo,"resources/bank%.4s/%.16s.fifo",bankId,accountId);
			mkfifo(responseFifo,DEFAULT);
			int response = open(responseFifo,O_RDONLY);
			free(string);
			string = litLigne(response);
			close(response);
			unlink(responseFifo);
			
			int ack = (int)(string[27] - '0');
			if(ack){
				printf(" transaction %d accepted\n",i);
			}else{
				printf(" transaction %d refused\n",i);
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

