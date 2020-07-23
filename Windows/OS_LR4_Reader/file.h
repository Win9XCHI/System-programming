#ifndef FILE_H
#define FILE_H
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <cstring>

typedef struct CF;
typedef struct CFM;
typedef struct mVoF;

class File {
    HANDLE hFile;
    LPCWSTR pszFileName;
    HANDLE hFileMappingObject;
    PVOID MapView;

public:
    File();
    File(LPCWSTR);
    ~File();

    bool CreateF(CF);
    bool CreateFM(CFM);
    bool MVOF(mVoF);

    bool CreateF(DWORD, DWORD, PSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    bool CreateFM(PSECURITY_ATTRIBUTES, DWORD, DWORD, DWORD);
    bool MVOF(DWORD, DWORD, DWORD, SIZE_T);

    void Close();
    bool FreeRegion();
    bool Save();
    bool OpenFM(DWORD, BOOL);

    HANDLE GetFile();
    HANDLE GetFileMap();
    PVOID GetMV();
    void Write();
    void Read();
};

struct CF {
    DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
    DWORD dwShareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
    PSECURITY_ATTRIBUTES psa = nullptr;
    DWORD dwCreationDisposition = OPEN_ALWAYS;
    DWORD dwFlagsAndAttributes = 0;
    HANDLE hTemplateFile = nullptr;
};

struct CFM {
    PSECURITY_ATTRIBUTES psa = nullptr;
    DWORD fdwProtect = PAGE_READWRITE;
    DWORD dwMaximumSizeHigh = 0;
    DWORD dwMaximumSizeLow = 1024;
};

struct mVoF {
    DWORD dwDesiredAccess = FILE_MAP_READ | FILE_MAP_WRITE;
    DWORD dwFileOffsetHigh = 0;
    DWORD dwFileOffsetLow = 0;
    SIZE_T dwNumberOfBytesToMap = 0;
};


#endif // FILE_H
