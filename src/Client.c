#include "../include/Client.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void GetClientStackAlloc(Client client)
{
	struct Client res;
	char buffer[64] = {0};
	int size;

	getchar();
	fgets(buffer,64, stdin);
	size = strlen(buffer);
	buffer[size-1] = 0;

	strcpy(res.name, buffer);
	res.codeClient = rand()%10000;

	*client = res;
}