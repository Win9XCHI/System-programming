#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <cstring>

using namespace std;

struct message {
	char nameClient[10];
	char Message[200];
	unsigned int ControlSum;
};

int main() {
    int sock, listener;
    struct sockaddr_in addr;
    message Object;
    char Answer[22] = "Thank you ";
    int bytes_read;

    listener = socket(AF_INET, SOCK_STREAM, 0); //create socket for internet and connection
    if(listener < 0) {
        perror("socket");
        return 1;
    }
    
    addr.sin_family = AF_INET;	//type
    addr.sin_port = htons(3425); //port
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //address
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) { //connect socket with address
        perror("bind");
        return 2;
    }

    listen(listener, 1); //new queue query
    
    while(1) {
        sock = accept(listener, NULL, NULL); //new socket for listening
        if(sock < 0) {
            perror("accept");
            return 3;
        }

        while(1) {
            bytes_read = recv(sock, &Object, sizeof(message), 0); //get information
            if(bytes_read <= 0 || Object.ControlSum != 7534) break;
            
            strcat(Answer, Object.nameClient);
            send(sock, Answer, sizeof(Answer), 0); //send information
            cout << endl << "Urgent news from " << Object.nameClient << ": " << Object.Message << endl;
            strcpy(Answer, "Thank you ");
            
            if (strcmp(Object.Message, "exit") == 0) {
				return 0;
			}
        }
    
        close(sock);
    }
    
    return 0;
}
