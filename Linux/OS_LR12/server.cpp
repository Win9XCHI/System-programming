#include <iostream>
#include <cstring>
#include "DataStructures.h"
#include <pthread.h>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;
//g++ -Wall -o "%e" "%f"

pthread_mutex_t mutexMain = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mutexOutput = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

template <class Container>
void split(const std::string& str, Container& cont, char delim = ' ', char delim2 = ' ') {
    size_t current, previous = 0;
    previous = str.find(delim);
    current = str.find(delim2);
    while (previous != string::npos && previous < str.find('\n')) {
        cont.push_back(str.substr(previous, current - previous));
        previous = str.find(delim, current);
        current = str.find(delim2, previous);            
    }
    if (str.find('\n') != string::npos) {
        cont.push_back(str.substr(current, str.find('\n')));
    }
}

string splitTown(const string& str, string town) {
    size_t current, next = 0;
    string newStr;
    current = str.find(town + ':');

    if (current == string::npos) {
        return "\0";
    }

    next = str.find('\n', current);
    if (next == string::npos) {
        next = str.length();
    }

    newStr = str.substr(current, next);

    return newStr;
}

string settime(struct tm *u) {
	  char s[11];
	  for (int i = 0; i<11; i++) s[i] = 0;
	  strftime(s, 11, "%d.%m.%Y", u);
	  string str(s);
	  return str;
}

//get [name city] [date] = 'current' [month] = 'current' 
string GetInformation(char *str) {
	string work(str);
	vector<string> cont;
	split(work, cont);
	string stringTown;
	string buff;
	
	cout << endl << work;
	split(work, cont);

	if (cont.size() < 2) {
		throw '\0';
	}
		
	if (cont.size() == 3) {
		work = cont[2] + ".txt";
	} else {
		const time_t timer = time(NULL);
		struct tm *u;
		u = localtime(&timer);
		work = settime(u);
	}
	cout << endl << work;
		
	ifstream file(work.c_str());
	//while(file.getline(&buff, 2000)) {
	while(getline(file, buff, ",")) {
		stringTown = splitTown(buff, cont[1]);
	}
	file.close();
	
	if (stringTown.size() == 1) {
		throw '\0';
	}
		
	if (cont.size() == 4) {
		work = stringTown.substr(stringTown.find(cont[3]), stringTown.find(",", stringTown.find(cont[3])) - stringTown.find(cont[3]));
	}
		
	cout << endl << work;
	if (work.size() == 0) {
		throw '\0';
	}
	
	return work;
}

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
	if (strcmp(Object->command, "") == 0) {
		file << "Command: Init";
	} else {
		file << "Command: " << Object->command;
	}
	file.close();
}

void *ProcessData(void *arg) {	
	ForPthread *Object = (ForPthread*)arg;
	message Mes(*Object->Object);
	CSocket sock(*Object->sock);
	pthread_cond_signal(&cond);
	
	answer Ans;
	Ans.errorCode = 0;
	Ans.ControlSum = 334;
	strcpy(Ans.nameClient, "Thank you ");
	
	if (CheckClient(Mes.nameClient)) {
		strcpy(Ans.nameClient, "No ");
		Ans.errorCode = 1;
		
	} else {
		try {
			strcpy(Ans.Data, GetInformation(Mes.command).c_str());
		} catch (char c) {
			cout << endl << "Error";
			Ans.errorCode = 2;
		}
		//if (strlen(Ans.Data) == 0) {}
	}
	strcat(Ans.nameClient, Mes.nameClient);
				
	sock.SendInfo(&Ans, sizeof(Ans));
	
	pthread_mutex_lock(&mutexOutput);
	cout << endl << "Urgent news from " << Mes.nameClient << ": " << Mes.command << endl;
	pthread_mutex_unlock(&mutexOutput);
	
	LogFile(&Mes);
	
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
				
				if (strcmp(Object.command, "exit") == 0) {
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


