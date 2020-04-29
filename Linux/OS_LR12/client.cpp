#include <limits.h>
#include "DataStructures.h"
#include "Handlers.h"

using namespace std;

//g++ -Wall -o "%e" "%f"
/*
 * exit
 * root
 * get [name city] [date] = 'current' [month] = 'current' 
 */
int main(int argc, char *argv[]) {
    answer Ans;
    message Object;
    Object.ControlSum = 7534;
    CSocket sock;
    int root = 0;
    vector<string> cont;
    fd_set rfds;
	struct timeval tv;
	int retval;
    
	try {
		
		if (argc < 4) {
			throw "Few parameters";
		}
		
		sock.Connect(argv[1], argv[2], argv[3]);
				
	} catch (const char *str) {
		cout << endl << str;
		cout << endl << "Please, check parameters and restart";
		return 1;
	}
	
	char hostname[10];
	gethostname(hostname, HOST_NAME_MAX);
	
	int lenHost = strlen(hostname);
	if (lenHost > NAME_CLIENT) {
		hostname[NAME_CLIENT - 1] = '\0';
	}
	strcpy(Object.nameClient, hostname);
		
	cout << endl << "Press quit for exit" << endl;
		
	cout << endl << "Enter new command: " << endl;
	while(strcmp(Object.command, "quit") != 0) {
		
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		
		tv.tv_sec = 3;
		tv.tv_usec = 0;	
		retval = select(2, &rfds, NULL, NULL, &tv);
		
		if (retval) {
			cont.clear();
			cin.getline(Object.command, COMMAND);
			split(Object.command, cont);
			
			if (cont[0] == "get") {
				Object.TypeQuery = 2;
			
				sock.SendInfo(&Object, sizeof(message));
				sock.GetInfo(&Ans, sizeof(answer));
				
				if (Ans.ControlSum == 334 && Ans.errorCode == 0) {
					
					cout << endl << Ans.nameClient;
					cout << endl << "Return information: " << Ans.Data << endl;
					
				} else {
					cout << endl << "Error: ";
					if (Ans.errorCode == 1) {
						cout << "Access denied for your hostname";
					}
					if (Ans.errorCode == 2) {
						cout << "Information not found";
					}
					if (Ans.errorCode == 3) {
						cout << "Too few options";
					}
				}
			}
			
			if (cont[0] == "root") {
				Object.TypeQuery = 3;
			
				sock.SendInfo(&Object, sizeof(message));
				sock.GetInfo(&Ans, sizeof(answer));
				
				if (Ans.ControlSum == 334 && Ans.errorCode == 0) {
					
					cout << endl << Ans.nameClient;
					root = 1;					
				} else {
					cout << endl << "Error: ";
					if (Ans.errorCode == 4) {
						cout << "Invalid password";
					}
				}
			}
			
			if (cont[0] == "exit") {
				if (root == 1) {
					Object.TypeQuery = 4;
					Object.ControlSum = 8349;
					sock.SendInfo(&Object, sizeof(message));
					char exit[10];
					sock.GetInfo(&exit, sizeof(exit));
					cout << endl << exit;
				} else {
					cout << endl << "You have not to root right";
				}
			}
			
			
			cout << endl << "Enter new command: " << endl;
			
		} else {
			//Object.TypeQuery = 1;
			//data
		}
	}

    sock.Close();

    return 0;
}
