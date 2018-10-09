#ifndef CLIENT_H_
#define CLIENT_H_ 

#ifndef MAX_STRING_NAME
#define MAX_STRING_NAME 124UL
#endif

typedef struct Client 
{
	unsigned codeClient;
	char name[MAX_STRING_NAME];
}*Client;


void GetClientStackAlloc(Client client);



#endif