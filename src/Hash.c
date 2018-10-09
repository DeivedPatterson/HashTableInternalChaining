#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <string.h>
#include "../include/Exception.h"
#include "../include/Hash.h"
#include "../include/Typedefs.h"


#define CHash(Obj)	((HashTInternalChaining)(Obj))
#define CHashLimit(Obj) ((HashTInternalChaining)(Obj))->limit
#define SetPosHash(index, Obj) (index * CHash(Obj)->type)

#ifndef DATA_SIZE
	#define DATA_SIZE 256
#endif


typedef struct HashTInternalChaining
{
	FILE* table;
	unsigned limit;
	unsigned size;
	HashFunction function;
	TypeObj type;
}*HashTInternalChaining;

typedef struct Container
{
	Byte data[DATA_SIZE];
	Descriptor des;
} *Container;


Hash newHashCreate(int size, HashFunction function, TypeObj type)
{
	HashTInternalChaining thash = NULL;
	int i;
	volatile int res = -1;

	try
	{
		if(size > 0)
		{
			try
			{
				thash = (HashTInternalChaining)malloc(sizeof(struct HashTInternalChaining));
				if(thash != NULL)
				{
					thash->limit = size;
					thash->size = 0;
					thash->function = function;
					thash->type = type;
					FileOpen(thash->table, "HashTable/HashTable.bin", "w+b");

					// int temp = None;
					// for(i = 0; i < size; i++)
					// {
					// 	FileWrite(&temp, Type(struct Container), 1, thash->table, res);
					// }
				}
				else
				{
					throw(__MemoryAllocationException__);
				}
			}
			catch(MemoryAllocationException)
			{
				PrintExceptionStdOut(MemoryAllocationException);
			}
		}
		else
		{
			throw(__InternalChainingHashTableSizeException__);
		}
	}
	catch(InternalChainingHashTableSizeException)
	{
		PrintExceptionStdOut(InternalChainingHashTableSizeException);
	}

	return thash;
}

unsigned getHashSize(Hash thash)
{
	return CHash(thash)->size;
}

bool HashIsEmpty(Hash thash)
{
	return CHash(thash)->size == 0?true:false;
}

void PrintHashTable(Hash thash, void(*format)(Object))
{
	struct Container container;
	int res = -1;
	bool isEnd = false;

	ReWind(CHash(thash)->table);

	while(!isEnd)
	{
		FileRead(&container, sizeof(struct Container), 1, CHash(thash)->table, res);
		if(res > 0)
		{
			format(container.data);
		}
		else
		{
			isEnd = true;
		}
	}
}

Object getRegisterHashTable(Hash thash, int key)
{

	// int index;
	// int pos = None;
	// int i; 
	// struct Register _register;
	// Object attached;

	// if(HashIsEmpty(thash))
	// 	return NULL;

	// attached = malloc(CHash(thash)->type);

	// index = CHash(thash)->function(key, CHash(thash)->limit);

	// FileSeek(CHash(thash)->table, index*sizeof(uint32_t), SEEK_SET);

	// for(i = 0; i < CHash(thash)->limit; i++)
	// {
	// 	//FileRead(attached, CHash(thash)->type, 1, CHash(thash)->table, res);	
	// }

}

static Object newContainer(unsigned long long size)
{
	Container container = NULL;

	try
	{
		container = malloc(sizeof(struct Container));
		if(container != NULL)
		{
			
		}
		else
		{
			throw(__MemoryAllocationException__);
		}
	}
	catch(MemoryAllocationException)
	{
		PrintExceptionStdOut(MemoryAllocationException);
	}

	return (Object)container;
}

void addObjectHashTable(Hash thash, Object obj)
{
	unsigned key;
	unsigned index;
	int pos = None;
	int res = -1;
	bool freeFound = false;
	struct Container container;
	Descriptor des;
	int i;

	key = (*((unsigned*)obj));

	memcpy(&(container.data), obj, CHash(thash)->type);
	container.des.bit.t = 0;

	index = CHash(thash)->function(key, CHash(thash)->limit);

	FileSeek(CHash(thash)->table, index*sizeof(struct Container), SEEK_SET);

	FileRead(&container, Type(struct Container), 1, CHash(thash)->table, res);

	if(container.des.bit.field.free == false)
	{

		FileSeek(CHash(thash)->table, index*sizeof(struct Container), SEEK_SET);
		FileWrite(&container, Type(struct Container), 1, CHash(thash)->table, res);
	}
	else
	{
		i = 1;

		while(!freeFound)
		{

			FileSeek(CHash(thash)->table, (i+index)*sizeof(struct Container), SEEK_SET);
			FileRead(&container, Type(struct Container), 1, CHash(thash)->table, res);

			if(container.des.bit.field.free == true)
			{
				i++;
			}

		}		
	}

}