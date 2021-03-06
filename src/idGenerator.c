#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>

struct option longopts[] = {
	{"bank",	required_argument, 0, 'b'},
	{"num", required_argument, 0, 'n'},
	{"unrandomize", no_argument, 0, 'u'}
};

typedef union{
	struct money{
		uint32_t moneyLSB;
		uint32_t moneyMSB;
	}split;
	unsigned long long all;
}Money;

void printHelp(char* programName);

int main(int argc, char* argv[]){
	if(argc == 3 || argc == 5 || argc == 6){
		opterr = 0;
		int indexptr;
		int opt;
		char* bankId = 0;
		int num;
		int unrandomize = 0;
		while((opt = getopt_long(argc, argv, "n:ub:",longopts, &indexptr)) != -1){
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
					return 1;
			}
		}
		srand(time(0));
		for(int i=0; i<num; i++){
			int firstTuple = rand()%10000;
			int secondTuple = rand()%10000;
			int thirdTuple = rand()%10000;
			int lastTuple = rand()%10000;
			Money money;
			money.split.moneyMSB = rand()&255;
			money.split.moneyLSB = rand();
			if(unrandomize){
				lastTuple = getpid()%10000;
			}
			if(bankId){
				printf("%.4s%04d%04d%04d%013llu\n",bankId,secondTuple,thirdTuple,lastTuple,money.all);
			}else{
				printf("%04d%04d%04d%04d%013llu\n",firstTuple,secondTuple,thirdTuple,lastTuple,money.all);
			}
		}
	}else{
		printHelp(argv[0]);
	}
 return 0;
}

void printHelp(char* programName){
	fprintf(	stderr,
				"Usage : %s [OPTION]...\n"
				"  -b,--bank\t bank id\n"
				"  -n,--num\t number of card id to generate (mandatory)\n"
				"  -u,--unrandomize\t set the last four digit of card to have a less random id\n",
				programName
	);
}
