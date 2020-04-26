#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <sys/wait.h>

using namespace std;

struct message {
	char nameClient[10];
	char Message[200];
	unsigned int ControlSum;
};

int main() {
    int sock;
    char Answer[22] = "No";
    message Object;
    Object.ControlSum = 7534;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("socket");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425); 
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return 2;
    }
    
    pid_t pid = fork();
    
    if (pid > 0) {
    
		cout << endl << "Your name: ";
		cin >> Object.nameClient;
		
		cout << endl << "Press exit for exit" << endl;
		
		while (strcmp(Object.Message, "exit") != 0) {
			cin.clear();
			cin.ignore();
			cout << endl << "Enter new message: ";
			cin.getline(Object.Message, 199);
			
			send(sock, &Object, sizeof(message), 0);
			int start = clock(), end = clock(), bytes = 0;
			
			while (bytes == 0 || end - start > 10000) {
				bytes = recv(sock, Answer, sizeof(Answer), 0);
				end = clock();
			}
			printf("%s", Answer);
		}
	}
	if (pid == 0) {
		pid = fork();
		int status;
		
		if (pid > 0) {
			strcpy(Object.nameClient, "No name");
			strcpy(Object.Message, ".....................");
			waitpid(pid, &status, 0);
		}
		if (pid == 0) {
			strcpy(Object.nameClient, "Fake news");
			strcpy(Object.Message, "Noise and missinformation");
		}
		send(sock, &Object, sizeof(message), 0);
		recv(sock, Answer, sizeof(Answer), 0);
		return 0;
	}

    close(sock);

    return 0;
}
