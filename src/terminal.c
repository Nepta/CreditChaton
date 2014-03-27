#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libCarteBancaire/gestionFichiers.h"

int main(int argc, char* argv[]){
	if(argc == 3){
		int writeFD = atoi(argv[1]);
		int readFD = atoi(argv[2]);
		char* firstLine = litLigne(readFD);
		printf("%s\n",firstLine);
		free(firstLine);
		close(writeFD);
		close(readFD);				
	}else{
		printf("usage:\n%s <writing file descriptor> "
				 "<reading file descriptor>\n",argv[0]);
	}
 return argc != 3;
}
