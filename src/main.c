#include <stdio.h>
#include <stdlib.h>

#include "../include/Hash.h"
#include "../include/Client.h"
#include "../include/Exception.h"

static inline __attribute__((always_inline)) int ModFunction(int key, int size)
{
	return (key % size);
}


int main(int argc, char const *argv[])
{
	Hash thash;
	FILE* file;
	

	return 0;

}