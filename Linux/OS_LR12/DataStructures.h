struct message {
	char nameClient[10];
	char Message[200];
	unsigned int ControlSum;
	
	char NameStruct[10];
	unsigned int sizeStruct;
};
