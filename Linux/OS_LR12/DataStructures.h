#include "CSocket.h"
#define NAME_CLIENT 30
#define DATA 200
#define COMMAND 30

struct message {
	char nameClient[NAME_CLIENT];
	int TypeQuery;
	char command[COMMAND];
	char Data[DATA];
	unsigned int ControlSum;
	
	char NameStruct[10];	//?
	unsigned int sizeStruct;	//?
	
	message() {}
	~message() {}
	message(const message &Object) {
		strcpy(nameClient, Object.nameClient);
		strcpy(command, Object.command);
		strcpy(Data, Object.Data);
		strcpy(NameStruct, Object.NameStruct);
		TypeQuery = Object.TypeQuery;
		ControlSum = Object.ControlSum;
		sizeStruct = Object.sizeStruct;
	}
};

struct answer {
	char nameClient[NAME_CLIENT];
	char Data[DATA];
	unsigned int errorCode;
	unsigned int ControlSum;
};

struct ForPthread {
	message *Object;
	CSocket *sock;
};
