#include <iostream>
#include <cstring>
#include "DataStructures.h"
#include "CSocket.h"

using namespace std;
//g++ -Wall -o "%e" "%f"

//string domain, string type, string port
//AF_INET SOCK_STREAM 3425 [AF_UNIX SOCK_DGRAM 3424]
int main(int argc, char *argv[]) {
    message Object;
    char Answer[22] = "Thank you ";
    int bytes_read;
    CSocket sock;
    
	try {
		
		if (argc < 4) {
			throw "Few parameters";
		}
		
		sock.CreateConnection(argv[1], argv[2], argv[3]);
				
	} catch (string str) {
		cout << endl << str;
		cout << endl << "Please, check parameters and restart";
		return 1;
	}
    
    while(1) {
		try {
			sock.NewConnectSock();

			while(1) {
				bytes_read = sock.GetInfo(&Object, sizeof(message));
				if(bytes_read <= 0 || Object.ControlSum != 7534) break;
				
				strcat(Answer, Object.nameClient);
				
				sock.SendInfo(Answer, sizeof(Answer));
				
				cout << endl << "Urgent news from " << Object.nameClient << ": " << Object.Message << endl;
				strcpy(Answer, "Thank you ");
				
				if (strcmp(Object.Message, "exit") == 0) {
					return 0;
				}
			}
		
			sock.Close();
		} catch (const char *str) {
			cout << endl << str;
			return 1;
		}
    }
    
    return 0;
}


