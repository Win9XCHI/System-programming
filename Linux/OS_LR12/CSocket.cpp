#include "CSocket.h"

CSocket::CSocket() : domain(AF_INET), type(SOCK_STREAM), protocol(0), port(3425), listener(0), sock(0) {
	InitAddr();
}
		
CSocket::CSocket(char *strDomain, char *strType, char *strPort) : listener(0), sock(0) {
	domain = SelectDomain(strDomain);
	type = SelectType(strType, strDomain);
	protocol = 0;
	port = atoi(strPort);
	InitAddr();
}

CSocket::CSocket(CSocket &Object) {
	domain = Object.domain;
	type = Object.type;
	protocol = Object.protocol;
	port = Object.port;
	listener = Object.listener;
	sock = Object.sock;
	InitAddr();
}

CSocket::~CSocket() {
}

void CSocket::InitAddr() {
	addr.sin_family = domain;	//type
	addr.sin_port = htons(port); //port
	addr.sin_addr.s_addr = htonl(INADDR_ANY); //address
}

void CSocket::Create(char *strDomain, char *strType, char *strPort) {
	domain = SelectDomain(strDomain);
	type = SelectType(strType, strDomain);
	protocol = 0;
	port = atoi(strPort);
	InitAddr();
	
	Create();
}

void CSocket::Create() {
	listener = socket(domain, type, 0); //create socket for internet and connection
	
	if(listener < 0) {
        throw "Create socket error";
    }

    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) { //connect socket with address
        throw "Bind error";
    }

    if (listen(listener, 1) < 0) { //new queue query
		throw "Listen error";
	}
}

void CSocket::Connect(char *strDomain, char *strType, char *strPort) {
	domain = SelectDomain(strDomain);
	type = SelectType(strType, strDomain);
	protocol = 0;
	port = atoi(strPort);
	InitAddr();
	
	Connect();
}

void CSocket::Connect() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        throw "Error connection";
    }
}

int CSocket::SelectDomain(char *str) {
	if (strcmp(str, "AF_INET") == 0) {
		return AF_INET;
	}
	if (strcmp(str, "AF_UNIX") == 0 || strcmp(str, "AF_LOCAL") == 0) {
		return AF_UNIX;
	}
	if (strcmp(str, "AF_IPX") == 0) {
		return AF_IPX;
	}
	if (strcmp(str, "AF_INET6") == 0) {
		return AF_IPX;
	}
	if (strcmp(str, "AF_BLUETOOTH") == 0) {
		return AF_BLUETOOTH;
	}
	throw "Invalid first parameter";
	return 0;
}

int CSocket::SelectType(char *str, char *strDom) {
	if (strcmp(str, "SOCK_STREAM") == 0) {
		return SOCK_STREAM;
	}
	if (strcmp(str, "SOCK_DGRAM") == 0 && (strcmp(strDom, "AF_UNIX") != 0 || strcmp(strDom, "AF_LOCAL") != 0)) {
		return SOCK_DGRAM;
	}
	if (strcmp(str, "SOCK_RAW") == 0) {
		return SOCK_RAW;
	}
	throw "Invalid second parameter";
	return 0;
}

void CSocket::NewConnectSock() {
	sock = accept(listener, NULL, NULL);
	
	if(sock < 0) {
		throw "Accept error";
	}
}

int CSocket::GetInfo(void *buf, size_t len, int flags) {
	return recv(sock, buf, len, 0);
}

void CSocket::Close() {
	close(sock);
}

void CSocket::SendInfo(void *buf, size_t len, int flags) {
	send(sock, buf, len, 0);
}

CSocket CSocket::operator=(const CSocket &Object) {
	domain = Object.domain;
	type = Object.type;
	protocol = Object.protocol;
	port = Object.port;
		
	listener = Object.listener;
	sock = Object.sock;
	InitAddr();
	return *this;
}
