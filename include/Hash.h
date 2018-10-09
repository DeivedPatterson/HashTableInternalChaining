#ifndef HASH_H_
#define HASH_H_ 

#include "Typedefs.h"
#include <stdio.h>

#define Type(Obj) sizeof(Obj)


typedef struct
{
	union
	{
		unsigned t;
		struct
		{
			int next:31;
			unsigned free:1;
		}field;
	}bit;
}Descriptor;

typedef void* Hash;
typedef int (*HashFunction)(int key, int size);
typedef unsigned long long TypeObj;

Hash newHashCreate(int size, HashFunction function, TypeObj type);
unsigned getHashSize(Hash thash);
bool HashIsEmpty(Hash thash);
unsigned getHashLimit(Hash thash);
void setHashFunction(HashFunction function);
Object getRegisterHashTable(Hash thash, int key);
void addObjectHashTable(Hash thash, Object obj);
void PrintHashTable(Hash thash, void(*format)(Object));



#endif