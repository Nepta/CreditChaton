#ifndef __ANNUAIRE_H__
#define __ANNUAIRE_H__

#include <string.h>

typedef struct{
	int size;
	char base[][16];
}DirectoryService;

int exist(DirectoryService *data, char id[16]);
DirectoryService* load(char*);

#endif /* __ANNUAIRE_H__ */

