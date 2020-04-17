//server
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/ipc.h>

using namespace std;

union U {
		int mas[5];
		char string[20];
};
	
struct messeg {
	long type;
	U info;
};

struct statistics {
	unsigned int connect;
	unsigned int connectArray;
	unsigned int connectString;
	time_t time;
};

void PrintSysInfo(msqid_ds info) {
	cout << endl << "msg_cbytes: " << info.msg_cbytes;
	cout << endl << "msg_qnum: " << info.msg_qnum;
	cout << endl << "msg_qbytes: " << info.msg_qbytes;
	cout << endl << "msg_lspid: " << info.msg_lspid;
	cout << endl << "msg_lrpid: " << info.msg_lrpid;
	cout << endl << "msg_stime: " << info.msg_stime;
	cout << endl << "msg_rtime: " << info.msg_rtime;
	cout << endl << "msg_ctime: " << info.msg_ctime;
}

int main() {
	messeg One;
	msqid_ds info;
	statistics Object = {0, 0, 0, 0};
	int rec;
	
	
	int IDmsg = msgget(1, 0); 
	PrintSysInfo(info);
	
	while (true) {
		
		rec = msgrcv(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0, 0); 
		if (rec != -1) {
			cout << endl;
			
			switch (One.type) {
				case 1: {
					cout << endl << "Array";
					for (unsigned int i = 0; i < 5; i++) {
						cout << endl << i << ": " << One.info.mas[i];
					}
					Object.connectArray++;
					break;
				}
				case 2: {
					cout << endl << "String: " << One.info.string;
					Object.connectString++;
					break;
				}
				case 3: {
					cout << endl << "Statistics ";
					cout << endl << "Amount connect: " << Object.connect + 1;
					cout << endl << "Amount array-type connect: " << Object.connectArray;
					cout << endl << "Amount string-type connect: " << Object.connectString;
					cout << endl << "Time last connect: " << Object.time;
					cout << endl << "Server is stoped!";
					return 0;
				}
				default: {
					cout << endl << "Invalid type query!";
				}
			}
			msgctl(IDmsg, IPC_STAT, &info);
			
			Object.connect++;
			Object.time = info.msg_rtime;
			
			cout << endl;
			PrintSysInfo(info);
		}
	}
	
	return 0;
}
