#include "CSocket.h"

struct message {
	char nameClient[10];
	char Message[200];
	unsigned int ControlSum;
	
	char NameStruct[10];
	unsigned int sizeStruct;
	
	message() {}
	~message() {}
	message(const message &Object) {
		strcpy(nameClient, Object.nameClient);
		strcpy(Message, Object.Message);
		strcpy(NameStruct, Object.NameStruct);
		ControlSum = Object.ControlSum;
		sizeStruct = Object.sizeStruct;
	}
};

struct ForPthread {
	message *Object;
	CSocket *sock;
};
