#ifndef __ANNUAIRE_H__
#define __ANNUAIRE_H__

#include <string.h>

typedef struct{
	int size;
	char base[][16+13];
}DirectoryService;

int exist(DirectoryService *data, char id[16]);
int balance(DirectoryService *data, int line, char value[13+1]);
DirectoryService* load(char*);

#endif /* __ANNUAIRE_H__ */

