//client
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

void PushMsg(long type) {
	messeg One;
	One.type = type;
	
	try {
		int IDmsg = msgget(1, 0);
		if (IDmsg == -1) {
			IDmsg = msgget(1, IPC_CREAT | 0666); 
			
			if (IDmsg == -1) {
				throw "Error create msgget";
			}
		}
		
		switch (type) {
			case 1: {
				for (unsigned int i = 0; i < 5; i++) {
					cout << endl << "Enter " << i << ": ";
					cin >> One.info.mas[i];	
				}
				break;
			}
			case 2: {
				cout << endl << "Enter string: ";
				cin.getline(One.info.string, 19);
				break;
			}
			case 3: {
				break;
			}
			default: {
				throw "Type error";
			}
		}
		
		int rec = msgsnd(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0); 
		
		if (rec == -1) {
			throw "Msgsnd error";
		}
		
		cout << endl << "Information sent";
	} catch (char *str) {
		cout << endl << str;
	}
}

int main() {
	int answer;
	
	cout << endl << "Enter type query (1 - array, 2 - string, 3 - kill server)" << endl << ">>";
	cin >> answer;
	cin.clear();
	cin.ignore(10000, '\n');
	
	PushMsg(answer);

	return 0;
}
