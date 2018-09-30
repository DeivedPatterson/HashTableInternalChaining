#ifndef HASH_H_
#define HASH_H_ 

#include "Typedefs.h"
#include <stdio.h>


typedef struct Register
{
	Object attached;
	union
	{
		unsigned t;
		struct
		{
			int next:31;
			unsigned free:1;
		}field;
	}bit;
}*Register;

typedef void* Hash;
typedef int (*HashFunction)(int key, int size);


Hash newHashCreate(int size, HashFunction function, FILE* file);
unsigned getHashSize(Hash thash);
unsigned getHashLimit(Hash thash);
void setHashFunction(HashFunction function);
Object getRegisterHashTable(Hash thash);
void addObjectHashTable(Hash thash, Object obj, unsigned long long size);



#endif