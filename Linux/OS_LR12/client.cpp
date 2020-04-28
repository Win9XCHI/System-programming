#include <iostream>
#include <cstring>
#include "DataStructures.h"

using namespace std;

//g++ -Wall -o "%e" "%f"
int main(int argc, char *argv[]) {
    char Answer[22] = "No";
    message Object;
    Object.ControlSum = 7534;
    CSocket sock;
    
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
    
	cout << endl << "Your name: ";
	cin >> Object.nameClient;
		
	cout << endl << "Press exit for exit" << endl;
		
	while (strcmp(Object.Message, "exit") != 0) {
		//cin.clear();
		//cin.ignore();
		cout << endl << "Enter new message: ";
		cin.getline(Object.Message, 199);
			
		sock.SendInfo(&Object, sizeof(message));
		//int start = clock(), end = clock(), bytes = 0;
		
		/*while (bytes == 0 || end - start > 10000) {
			cout << endl << end - start;*/
			sock.GetInfo(Answer, sizeof(Answer));
			/*end = clock();
		}*/
		cout << endl << Answer << endl;
	}

    sock.Close();

    return 0;
}
