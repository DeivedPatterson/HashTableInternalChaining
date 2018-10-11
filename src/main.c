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


static void AddClient(Hash thash)
{
	struct Client client;

	puts("Entre com o Nome");
	GetClientStackAlloc(&client);
	addObjectHashTable(thash, &client);
}

static void RemoveClient(Hash thash)
{

}
       
static void SearchClient(Hash thash)
{
}

static void Format(Object Obj)
{
	struct Client client;
	bool isNull;

	memcpy(&client, Obj, Type(struct Client));

	isNull = strlen(client.name) == 0?true:false;

	printf("Nome: %s\n" , isNull?"null":client.name);
	printf("Código: %i\n",isNull?-1:client.codeClient);

}

static void PrintTable(Hash thash)
{
	PrintHashTable(thash, Format);
}

int main(int argc, char const *argv[])
{
	Hash thash;
	struct Client client; 
	int n;
	int op;
	bool endApp = false;

	static void(*option[])(Hash) = {AddClient, PrintTable, RemoveClient, SearchClient};

	srand(time(NULL));

	puts("Entre com o tamanho da tabela");
	scanf("%i",&n);
	thash = newHashCreate(n, ModFunction, Type(struct Client));

	while(!endApp)
	{
		puts("****************************");
		puts("* 0: Adcionar Novo Cliente *");
		puts("* 1: Imprimir Tabela       *");
		puts("* 2: Excluir Cliente       *");
		puts("* 3: Exit                  *");
		puts("****************************");

		scanf("%i", &op);

		if(op < sizeof(option)/8)
		{
			if(op == 3)
			{
				endApp = true;
			}
			else
			{
				option[op](thash);
			}
		}
		else
		{
			endApp = true;
		}
	}

	return 0;
}