#include <stdlib.h>
#include <stdio.h>
#include "annuaire.h"

int exist(DirectoryService *data, char id[16]){
	for(int i=0; i<data->size; i++){
		if(strncmp(data->base[i],id,16) == 0){
			return i;
		}
	}
 return -1;
}

DirectoryService* load(char* path){
	FILE *file = fopen(path, "r");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *string = calloc(fileSize,1);
	fread(string, 1, fileSize+1, file);
	int registeredUser = (fileSize-1)/17;
	DirectoryService* data = malloc(sizeof (DirectoryService) + registeredUser * (16+13));
	data->size = registeredUser;
	for(int i=0;i<registeredUser;i++){
		strncpy(data->base[i],string+i*17,16+13);
	}
 return data;
}

int balance(DirectoryService *data, int line, char value[13+1]){
	char* accountBalance = data->base[line]+16;
	for(int i=0; i<13; i++){
		if(accountBalance[i] < value[i]){
			return 0;
		}
	}
	return 1;
}

