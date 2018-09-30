#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/Exception.h"
#include "../include/Hash.h"
#include "../include/Typedefs.h"

#define CHash(Obj)	((HashTInternalChaining)(Obj))
#define CHashLimit(Obj) ((HashTInternalChaining)(Obj))->limit


typedef struct HashTInternalChaining
{
	FILE* table;
	unsigned limit;
	unsigned size;
	HashFunction function;
	FILE* file;
}*HashTInternalChaining;


Hash newHashCreate(int size, HashFunction function, FILE* file)
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
					thash->file = file;
					FileOpen(thash->table, "HashTable/HashTable.bin", "w+b");

					int temp = None;
					for(i = 0; i < size; i++)
					{
						FileWrite(&temp, sizeof(unsigned), 1, thash->table, res);
					}
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

void addObjectHashTable(Hash thash, Object obj, unsigned long long size)
{
	unsigned key;
	struct Register _register;
	unsigned index;

	key = (*((unsigned*)obj));

	_register.attached = calloc(size, sizeof(Byte));
	memcpy(_register.attached, obj, size);

	_register.bit.field.key = key;
	_register.bit.field.free = false;

	index = CHash(thash)->function(key, CHashLimit(thash));

	
}