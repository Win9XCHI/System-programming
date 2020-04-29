#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

template <class Container>
static void split(const string& str, Container& cont, char delim = ' ') {
     size_t current, previous = 0;
     current = str.find(delim);
     while (current != string::npos) {
           cont.push_back(str.substr(previous, current - previous));
           previous = current + 1;
           current = str.find(delim, previous);
     }
     cont.push_back(str.substr(previous, current - previous));
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
 
string SetTime(const char *format) {
	const time_t timer = time(NULL);
    struct tm *u;
    u = localtime(&timer);
      
    char s[100];
    for (unsigned int i = 0; i < 100; i++) s[i] = 0;
    strftime(s, 100, format, u);
    string str(s);
    
    return str;
}
 
//get [name city] [date] = 'current' [month] = 'current'
void GetInformation(vector<string> &cont, string &work) {
    work = "Library/";
    string stringTown;
    char buff[255];
 
    if (cont.size() > 2) {
        work += cont[2];
    } else {
        work += SetTime("%d.%m.%Y");
    }
    work += ".txt";
    
    ifstream file(work.c_str());
    while(file.getline(buff, 255)) {
        stringTown = buff;
        stringTown = splitTown(stringTown, cont[1]);
 
        if (stringTown.size() != 0) {
            break;
        }
    }
    file.close();
 
    if (stringTown.size() == 0) {
        throw '\0';
    }
 
	work = stringTown;
    if (cont.size() == 4) {
        work = stringTown.substr(stringTown.find(cont[3]), stringTown.find(",", stringTown.find(cont[3])) - stringTown.find(cont[3]));
    }

    if (work.size() == 0) {
        throw '\0';
    }
}

bool CheckPassword(string &password) {
	bool flag = false;
	char buff[255];
	
	ifstream file("Password.txt");
    while(file.getline(buff, 255)) {
        if (strcmp(buff, password.c_str()) == 0) {
			flag = true;
		}
    }
    file.close();
    
    return flag;
}
