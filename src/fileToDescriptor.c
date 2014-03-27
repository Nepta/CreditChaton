#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/**
 * open file to file descriptor and lunch a process passing giving descriptor as argument
 * argv[1] file to write into (stdout)
 * argv[2] file to read into (stdin)
 * argv[3] process to exec
 */

int main(int argc, char* argv[]){
	if(argc == 4){
		int writeFD = open(argv[2], O_CREAT|O_WRONLY, 0644);
		int readFD = open(argv[3], O_RDONLY);
		char writeFDString[4];
		char readFDString[4];
		snprintf(writeFDString,4,"%d",writeFD);
		snprintf(readFDString,4,"%d",readFD);
		execlp(argv[1], argv[1], writeFDString, readFDString, NULL);
	}else{
		printf("usage:\n%s <process to execute> <writing file> <reading file>\n",argv[0]);
	}
 return argc != 4;
}
