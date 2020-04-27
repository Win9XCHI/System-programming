#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <iostream> //убрать позже
using namespace std;

class CSocket {
	private:
			
		struct sockaddr_in *addr;
		int domain;
		int type;
		int protocol;
		int port;
		
		int listener;
		int sock;
		
		int SelectDomain(char *str);
		int SelectType(char *str, char *strDom);
		
		void ClearAddr();
		void InitAddr();
		
	public:
		CSocket();
		CSocket(char *strDomain, char *strType, /*char *strProtocol,*/ char *strPort);
		~CSocket();
		
		int CreateConnection(char *strDomain, char *strType, char *strPort/*, char *strProtocol*/);
		int CreateConnection();
		
		int GetListener();
		
		void SendInfo(void *buf, size_t len, int flags = 0);
		int GetInfo(void *buf, size_t len, int flags = 0);
		void NewConnectSock(/*int sockfd, struct sockaddr *addr, socklen_t *addrlen*/);
		
		void Close();
};
