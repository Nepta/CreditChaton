#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

struct option longopts[] = {
	{"bank",	required_argument, 0, 'b'},
	{"num", required_argument, 0, 'n'},
	{"unrandomize", no_argument, 0, 'u'}
};

void printHelp(char* programName);

int main(int argc, char* argv[]){
	if(argc == 5 || argc == 6){
		opterr = 0;
		int indexptr;
		int opt;
		char* bankId;
		int num;
		int unrandomize = 0;
		while((opt = getopt_long(argc, argv, "b:n:u",longopts, &indexptr)) != -1){
			switch(opt){
				case 'b':
					bankId = optarg;
					break;
				case 'n':
					num = atoi(optarg);
					break;
				case 'u':
					unrandomize = 1;
					break;
				default:
					printHelp(argv[0]);
					break;
			}
		}
		srand(time(0));
		for(int i=0; i<num; i++){
			int secondTuple = rand()%10000;
			int thirdTuple = rand()%10000;
			int lastTuple = rand()%10000;
			if(unrandomize){
				lastTuple = getpid()%10000;
			}
			printf("%4s%04d%04d%04d\n",bankId,secondTuple,thirdTuple,lastTuple);
		}
	}else{
		printHelp(argv[0]);
	}
}

void printHelp(char* programName){
	fprintf(	stderr,
				"Usage : %s [OPTION]...\n"
				"  -b,--bank\t bank id (mandatory)\n"
				"  -n,--num\t number of card id to generate (mandatory)\n"
				"  -u,--unrandomize\t set the last four digit of card to have a less random id\n",
				programName
	);
}
