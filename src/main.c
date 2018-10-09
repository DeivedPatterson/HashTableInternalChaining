#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "../include/Hash.h"
#include "../include/Client.h"
#include "../include/Exception.h"



static inline __attribute__((always_inline)) int ModFunction(int key, int size)
{
	return (key % size);
}


static void AddClient()
{

}

static void RemoveClient()
{

}
       
static void SearchClient()
{
}

static void Format(Object Obj)
{
	struct Client client;


	memcpy(&client, Obj, Type(struct Client));

	printf("Nome: %s\n" , strlen(client.name) == 0?"null":client.name);
	printf("Código: %i\n",client.codeClient);

}

static void PrintFile(FILE* file)
{
	struct Client client;
	int res = -1;
	bool isEnd = false;

	ReWind(file);

	while(!isEnd)
	{
		FileRead(&client, sizeof(struct Client), 1, file, res);
		if(res > 0)
		{
			printf("Nome: %s\n" , !strlen(client.name)?"null":client.name);
			printf("Código: %i\n",client.codeClient);
		}
		else
		{
			isEnd = true;
		}
	}
}

int main(int argc, char const *argv[])
{
	Hash thash;
	struct Client client; 
	int n;
	static void(*option[]) = {AddClient, RemoveClient, SearchClient};
	
	scanf("%i",&n);

	srand(time(NULL));

	thash = newHashCreate(n, ModFunction, Type(struct Client));


	GetClientStackAlloc(&client);

	addObjectHashTable(thash, &client);

	PrintHashTable(thash, Format);



	return 0;

}