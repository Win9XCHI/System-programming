#include "CSocket.h"

struct message {
	char nameClient[30];
	int TypeQuery;
	char command[30];
	char Data[400];
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
	char nameClient[22];
	char Data[400];
	unsigned int errorCode;
	unsigned int ControlSum;
};

struct ForPthread {
	message *Object;
	CSocket *sock;
};
