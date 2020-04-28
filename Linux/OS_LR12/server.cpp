#include <iostream>
#include <cstring>
#include "DataStructures.h"
#include <pthread.h>

using namespace std;
//g++ -Wall -o "%e" "%f"

pthread_mutex_t mutexMain = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mutexOutput = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *ProcessData(void *arg) {	
	ForPthread *Object = (ForPthread*)arg;
	message Mes(*Object->Object);
	CSocket sock(*Object->sock);
	pthread_cond_signal(&cond);
	
	char Answer[22] = "Thank you ";
	strcat(Answer, Mes.nameClient);
				
	sock.SendInfo(Answer, sizeof(Answer));
	
	pthread_mutex_lock(&mutexOutput);
	cout << endl << "Urgent news from " << Mes.nameClient << ": " << Mes.Message << endl;
	pthread_mutex_unlock(&mutexOutput);
	
	return (void *)Object;
}

//string domain, 	string type, 	string port	[...]
//AF_INET 			SOCK_STREAM 	3425 		[AF_UNIX SOCK_DGRAM 3424]
int main(int argc, char *argv[]) {
	ForPthread Arg;
    message Object;
    pthread_t id = 0; 
    CSocket sock;
    Arg.sock = &sock;
    pthread_mutex_init(&mutexOutput, NULL);
    pthread_mutex_init(&mutexMain, NULL);
    
	try {
		
		if (argc < 4) {
			throw "Few parameters";
		}
		
		sock.Create(argv[1], argv[2], argv[3]);
				
	} catch (string str) {
		cout << endl << str;
		cout << endl << "Please, check parameters and restart";
		return 1;
	}
    try {
		
		while(1) {
			sock.NewConnectSock();

			while(1) {
				
				int bytes_read = sock.GetInfo(&Object, sizeof(message));
				
				if(bytes_read <= 0 || Object.ControlSum != 7534) {
					break;
				}
				
				if (strcmp(Object.Message, "exit") == 0) {
					return 0;
				}
				
				Arg.Object = &Object;

				if (pthread_create(&id, NULL, ProcessData, (void*)&Arg) == 0) {
					pthread_cond_wait(&cond, &mutexMain);
				} else {
					throw "Pthread error";
				}
			}
			
			sock.Close();
		}
	} catch (const char *str) {
		cout << endl << str;
		return 1;
	}
    
    pthread_mutex_destroy(&mutexMain);
    pthread_mutex_destroy(&mutexOutput);
    
    return 0;
}


