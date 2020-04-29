#include "DataStructures.h"
#include <pthread.h>
#include "Handlers.h"

using namespace std;
//g++ -Wall -o "%e" "%f"

pthread_mutex_t mutexMain = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mutexOutput = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 

bool CheckClient(const char *NameClient) {
	char Author[10];
	ifstream file("BlackList.txt");
	file.getline(Author, 10);
	if (strcmp(NameClient, Author) == 0) {
		return true;
	}
	return false;
}

void LogFile(message *Object) {
	ofstream file("Log.txt", ios_base::app);
	file << "Author: " << Object->nameClient << endl;
	file << "Command: " << Object->command << endl;
    file << "Time: " << SetTime("%d.%m.%Y %X") << endl;
	
	
	file.close();
}

void *ProcessData(void *arg) {	
	ForPthread *Object = (ForPthread*)arg;
	message Mes(*Object->Object);
	CSocket sock(*Object->sock);
	pthread_cond_signal(&cond);
	
	answer Ans;
	vector<string> cont;
	string work;
	Ans.errorCode = 0;
	Ans.ControlSum = 334;
	strcpy(Ans.nameClient, "Thank you ");
	
	if (CheckClient(Mes.nameClient)) {
		strcpy(Ans.nameClient, "No ");
		Ans.errorCode = 1;
		
	} else {
		try {
			split(Mes.command, cont); 
	 
			if (cont.size() < 2) {
				throw 1;
			}
	 
			if (cont[0] == "get" && Mes.TypeQuery == 2) {
				GetInformation(cont, work);		
				strcpy(Ans.Data, work.c_str());
			}
			
			if (cont[0] == "root" && Mes.TypeQuery == 3) {
				cout << endl << "Query on root right ";
				if (CheckPassword(cont[1])) {
					cout << "YES right";
				} else {
					cout << "NOT right";
					Ans.errorCode = 4;
				}
			}
			
		} catch (char c) {
			cout << endl << "Error process query";
			Ans.errorCode = 2;
		} catch (int) {
			cout << endl << "Error query";
			Ans.errorCode = 3;
		}
	}
	
	strcat(Ans.nameClient, Mes.nameClient);
				
	sock.SendInfo(&Ans, sizeof(answer));
	
	pthread_mutex_lock(&mutexOutput);
	cout << endl << "Command from " << Mes.nameClient << ": " << Mes.command << endl;
	LogFile(&Mes);
	pthread_mutex_unlock(&mutexOutput);	
	
	return (void *)Object;
}

//string domain, 	string type, 	string port	[...]
//AF_INET 			SOCK_STREAM 	3425 		[AF_UNIX SOCK_DGRAM 3424]
int main(int argc, char *argv[]) {
	ForPthread Arg;
    message Object;
    pthread_t id = 0; 
    char exit[10];
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
	
	cout << endl << "Server status: start" << endl;
	
    try {
		
		while(true) {
			sock.NewConnectSock();

			while(true) {
				
				int bytes_read = sock.GetInfo(&Object, sizeof(message));
				
				if(bytes_read <= 0 || (Object.ControlSum != 7534 && Object.ControlSum != 8349)) {
					break;
				}
				
				if (strcmp(Object.command, "exit") == 0) {
					LogFile(&Object);
					if (Object.ControlSum == 8349 && Object.TypeQuery == 4) {
						strcpy(exit, "Yes");
						sock.SendInfo(&exit, sizeof(exit));
						return 0;
					} else {
						strcpy(exit, "No");
						sock.SendInfo(&exit, sizeof(exit));
						break;
					}
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


