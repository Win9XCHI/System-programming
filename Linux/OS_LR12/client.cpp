#include <iostream>
#include <cstring>
#include <limits.h>
#include "DataStructures.h"

using namespace std;

//g++ -Wall -o "%e" "%f"
/* help
 * Any command = message
 * get [name city] [date] = 'current' [month] = 'current' 
 */
int main(int argc, char *argv[]) {
    //char Answer[22] = "No";
    answer Ans;
    message Object;
    Object.ControlSum = 7534;
    CSocket sock;
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
    
	/*cout << endl << "Your name: ";
	cin >> Object.nameClient;*/
	
	char hostname[10];
	gethostname(hostname, HOST_NAME_MAX);
	
	int lenHost = strlen(hostname);
	if (lenHost > 30) {
		hostname[29] = '\0';
	}
	strcpy(Object.nameClient, hostname);
		
	cout << endl << "Press exit for exit" << endl;
		
	cout << endl << "Enter new command: " << endl;
	while(strcmp(Object.command, "exit") != 0) {
		
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		
		tv.tv_sec = 3;
		tv.tv_usec = 0;	
		retval = select(2, &rfds, NULL, NULL, &tv);
		
		if (retval) {
			cin.getline(Object.command, 399);
			Object.TypeQuery = 1;
			
			sock.SendInfo(&Object, sizeof(message));
			sock.GetInfo(&Ans, sizeof(Ans));
			
			if (Ans.ControlSum == 334) {
				cout << endl << Ans.nameClient;
				cout << endl << "Information: " << Ans.Data;
				
			} else {
				cout << endl << "Error: ";
				if (Ans.errorCode == 1) {
					cout << "Access denied for your hostname";
				}
				if (Ans.errorCode == 2) {
					cout << "Information not found";
				}
			}
			
			cout << endl << "Enter new command: " << endl;
			
		} else {
			//Object.TypeQuery = 2;
			//data
		}
	}

    sock.Close();

    return 0;
}
