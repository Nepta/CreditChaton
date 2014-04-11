#include <stdlib.h>
#include <stdio.h>
#include "annuaire.h"

int exist(DirectoryService *data, char id[16]){
	int isIdExisting = 0;
	for(int i=0; i<data->size; i++){
		if(strncmp(data->base[i],id,16) == 0){
			isIdExisting = 1;
			break;
		}
	}
 return isIdExisting;
}

// recuperé du tower defense: https://github.com/Nepta/Tower-Defense/blob/master/jsonParser.c#L37
char* fileToString(FILE *file){
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *string = calloc(fileSize,1);
	fread(string, 1, fileSize+1, file);
 return string;
}

DirectoryService* load(char* path){
	FILE *file = fopen(path, "r");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *string = calloc(fileSize,1);
	fread(string, 1, fileSize+1, file);
	int registeredUser = (fileSize-1)/17;
	DirectoryService* data = malloc(sizeof (DirectoryService) + registeredUser * 16);
	data->size = registeredUser;
	for(int i=0;i<registeredUser;i++){
		strncpy(data->base[i],string+i*17,16);
	}
 return data;
}


