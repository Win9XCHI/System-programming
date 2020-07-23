#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

class File {
    ofstream foutWrite;
    ifstream foutRead;

public:
    File();
    File(char *, char);
    ~File();

    void Open(char *, char);
    void WriteFile();
    void ReadFile(char *);
    void Close(char);
    void AddEndl();
};



#endif // FILE_H
