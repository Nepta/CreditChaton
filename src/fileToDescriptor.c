#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>

const int DEFAULT = 0644;

struct option longopts[] = {
	{"input",	required_argument, 0, 'i'},
	{"output",	required_argument, 0, 'o'}
};

void printHelp(const char* programName){
	printf(	"Usage : %s [OPTION]... [program to execute] -- [option of the sub program]\n"
				"Open two fifo, and pass their file descriptor to the sub-program\n"
				"  -i,--input\t reading fifo (mandatory)\n"
				"  -o,--output\t writing fifo (mandatory)\n"
			,programName);
}

int main(int argc, char* argv[]){
	opterr = 0;
	int indexptr;
	int opt;
	int writeFD = -1;
	int readFD = -1;
	while((opt = getopt_long(argc, argv, "i:o:",longopts, &indexptr)) != -1){
		switch(opt){
			case 'i':
				unlink(optarg);
				mkfifo(optarg,DEFAULT);
				readFD = open(optarg,O_RDONLY);
				break;
			case 'o':
				unlink(optarg);
				mkfifo(optarg,DEFAULT);
				writeFD = open(optarg,O_WRONLY);
				break;
			default:
				printHelp(argv[0]);
				return 1;
				break;
		}
	}
	if(writeFD != -1 && readFD != -1){
		/* construct a sane argv for the exec*/
		argv += optind;
		argc -= optind;
		char* subProgram = argv[0];
		char** argv2 = malloc((1+4+argc)* sizeof (char*));
		int i;
		for(i=0;i<argc;i++){
			argv2[i] = argv[i];
		}
		argv2[i] = "-i"; i++;
		argv2[i] = malloc(3); argv2[i][0] = '\0';
		sprintf(argv2[i],"%d",readFD); i++;
		argv2[i] = "-o"; i++;
		argv2[i] = malloc(3); argv2[i][0] = '\0';
		sprintf(argv2[i],"%d",writeFD); i++;
		argv2[i] = NULL;
		execv(subProgram, argv2);
		perror("exec");
	}
 return 0;
}
