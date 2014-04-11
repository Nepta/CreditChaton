#include <stdlib.h>
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

DirectoryService* load(int fd){
	int registeredUser = 10;
	DirectoryService* data = malloc(sizeof (DirectoryService) + registeredUser * 16);
	data->size = registeredUser;
	strncpy(data->base[0],"0000000000000000",16);
	strncpy(data->base[1],"0000000000000001",16);
	strncpy(data->base[2],"0000000000000002",16);
	strncpy(data->base[3],"0000000000000003",16);
	strncpy(data->base[4],"0000000000000004",16);
	strncpy(data->base[5],"0000000000000005",16);
	strncpy(data->base[6],"0000000000000006",16);
	strncpy(data->base[7],"0000000000000007",16);
	strncpy(data->base[8],"0000000000000008",16);
	strncpy(data->base[9],"0000000000000009",16);
 return data;
}

