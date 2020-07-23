#include "file.h"

File::File() {

}

File::File(char *filename, char WR) {
    Open(filename, WR);
}

File::~File() {
    if (foutRead.is_open()) {
        foutRead.close();
    }
    if (foutRead.is_open()) {
        foutWrite.close();
    }
}

void File::Open(char *filename, char WR) {
    if (WR == 'i') {
        foutRead.open(filename);
        cout << endl << "Read open";
    } else {
        foutWrite.open(filename, ios_base::app);
        cout << endl << "Write open";
    }
}

void File::WriteFile() {
    int num[10];
    for (int i = 0; i < 10; i++) {
        srand( time( nullptr ) + i );
        num[i] = 33 + rand() % 127;
        foutWrite << (char)num[i];
    }
}

void File::AddEndl() {
    foutWrite << endl;
}

void File::ReadFile(char *filename) {
    string buff, text = "";
    int i(0);
    while (getline(foutRead, buff)) {
        if (i == 0) {
            cout << endl << buff;
        } else {
            text += buff + "\n";
        }
        i++;
    }
    foutRead.close();
    foutWrite.open(filename, ios_base::out | ios_base::trunc);
    foutWrite << text;
    foutWrite.close();
}

void File::Close(char c) {
    if (foutRead.is_open() || c == 'i') {
        foutRead.close();
    }
    if (foutRead.is_open() || c == 'o') {
        foutWrite.close();
        cout << endl << "Write close";
    }
}
