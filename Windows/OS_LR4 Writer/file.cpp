#include "file.h"

File::File() : hFile(nullptr), hFileMappingObject(nullptr), MapView(nullptr) {
    pszFileName = L"";
}

File::File(LPCWSTR atr) : hFile(nullptr), pszFileName(atr), hFileMappingObject(nullptr), MapView(nullptr)  {}

File::~File() {
    Close();
}

bool File::CreateF(DWORD dwDesiredAccess, DWORD dwShareMode, PSECURITY_ATTRIBUTES psa, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    hFile = CreateFile(pszFileName, dwDesiredAccess, dwShareMode, psa, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    return hFile != nullptr || hFile != INVALID_HANDLE_VALUE;
}

bool File::CreateFM(PSECURITY_ATTRIBUTES psa, DWORD fdwProtect, DWORD dwMaximumSizeHigh, DWORD dwMaximumSizeLow) {
    //hFileMappingObject = CreateFileMapping(hFile, psa, fdwProtect, dwMaximumSizeHigh, dwMaximumSizeLow, pszFileName);
    hFileMappingObject = CreateFileMapping(INVALID_HANDLE_VALUE, psa, fdwProtect, dwMaximumSizeHigh, dwMaximumSizeLow, pszFileName);
    return hFileMappingObject != nullptr;
}

bool File::MVOF(DWORD dwDesiredAccess, DWORD dwFileOffsetHigh, DWORD dwFileOffsetLow, SIZE_T dwNumberOfBytesToMap) {
    MapView = MapViewOfFile(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap);
    return MapView != nullptr;
}

bool File::CreateF(CF str) {
    hFile = CreateFile(pszFileName, str.dwDesiredAccess, str.dwShareMode, str.psa, str.dwCreationDisposition, str.dwFlagsAndAttributes, str.hTemplateFile);
    return hFile != nullptr;
}

bool File::CreateFM(CFM str) {
    hFileMappingObject = CreateFileMapping(hFile, str.psa, str.fdwProtect, str.dwMaximumSizeHigh, str.dwMaximumSizeLow, pszFileName);
    return hFileMappingObject != nullptr;
}

bool File::MVOF(mVoF str) {
    MapView = MapViewOfFile(hFileMappingObject, str.dwDesiredAccess, str.dwFileOffsetHigh, str.dwFileOffsetLow, str.dwNumberOfBytesToMap);
    return MapView != nullptr;
}

void File::Close() {
    FreeRegion();
    CloseHandle(hFileMappingObject);
    CloseHandle(hFile);

    std::cout << std::endl << "Files: Close handle";
}

bool File::FreeRegion() {
    return UnmapViewOfFile(MapView);
}

bool File::Save() {
    return FlushViewOfFile(MapView, 0);
}

bool File::OpenFM(DWORD atr, BOOL atr2) {
    hFileMappingObject = OpenFileMapping(atr, atr2, pszFileName);
    return hFileMappingObject != nullptr;
}

HANDLE File::GetFile() {
    return hFile;
}

HANDLE File::GetFileMap() {
    return hFileMappingObject;
}

PVOID File::GetMV() {
    return MapView;
}

void File::Write() {
    std::cin >> (char*)MapView;
}

void File::Read() {
    std::cout << (char*)MapView;
}
