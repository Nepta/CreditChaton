#ifndef __ANNUAIRE_H__
#define __ANNUAIRE_H__

typedef struct{
	int size;
	char* base[];
}DirectoryService;

int exist(DirectoryService *data, char id[16]);
DirectoryService* load(int fs);

#endif /* __ANNUAIRE_H__ */

