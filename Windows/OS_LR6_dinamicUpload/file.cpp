#include "file.h"

using namespace std;

//Формування ім'я файлу та параметрів
//Вхідні дані: ім'я, параметри відкриття файлу, параметр
//Вихідні дані відсутні
void Expension(char *str, char *TypeChar, char *c) {
    int type(0);
    int lenght = strlen(str);
    str[lenght] = '.';
    str[lenght + 1] = 't';
    str[lenght + 2] = 'x';
    str[lenght + 3] = 't';
    str[lenght + 4] = '\0';

    while (type != 1 && type != 2) {
        cout << "Enter type file (1 - txt, 2 - binary)" << endl;
        cin >> type;
    }
    TypeChar[0] = c[0];
    TypeChar[2] = '\0';
    if (type == 1) {
        TypeChar[1] = 't';
    } else {
        TypeChar[1] = 'b';
    }
}

//Запис у файл інформації в лінію
//Вхідні дані: файлова змінна, інформація
//Вихідні дані відсутні
void WriteLine(FILE *fp, double info) {
    fprintf(fp, "%f, ", info);
}

//Запис у файл інформації у стовпець
//Вхідні дані: файлова змінна, інформація
//Вихідні дані відсутні
void WriteColumn(FILE *fp, double info) {
    fprintf(fp, "%f,\n", info);
}

//Збереження інформації у файл
//Вхідні дані: файлова змінна, вказівник на початок списку
//Вихідні дані відсутні
void Save(FILE *fp, Node *head) {

    if (head != NULL) {
        Node *work;
        work = head;
        char str[255], TypeChar[3];
		char setting[2];
        char w;
        cout << endl << "Enter name file: ";
        cin >> str;

		setting[0] = 'a';
		setting[0] = '\0';
        Expension(str, TypeChar, setting);

        cout << endl << "Line or Column? (l, c): ";
        cin >> w;

        if ((fp = fopen(str, TypeChar)) == NULL) {
               cout << endl << "File is error open";
        } else {

            while (work != NULL) {

                if (w == 'l') {
                    WriteLine(fp, work->info);
                } else {
                    WriteColumn(fp, work->info);
                }
                work = work->next;
            }
        }

        fclose(fp);
    }
}

//Зчитування інформації з файлу
//Вхідні дані: файлова змінна
//Вихідні дані: вказівник на початок списку
Node *Read(FILE *fp) {
    Node *head;
    Node *work;
    Node *last;
    head = NULL;
    last = head;
    char str[255], TypeChar[3], buffer('1'), number[10];
	char setting[2];
    int j(0);

    cout << endl << "Enter name file: ";
        cin >> str;

		setting[0] = 'a';
		setting[0] = '\0';
        Expension(str, TypeChar, setting);

        if ((fp = fopen(str, TypeChar)) == NULL) {
                cout << endl << "File is error open";
        }
        else{
            rewind(fp);
            while (buffer != EOF) {

                buffer = fgetc(fp);
                if (!isalnum(buffer) && buffer != ',') {
                    continue;
                }

                if (buffer != ',') {
                     number[j] = buffer;
                     j++;
                } else {
                    work = new Node;
                    work->next = NULL;
                    work->previous = last;

                    if (head != NULL) {
                        last->next = work;
                    } else {
                        head = work;
                    }
                    work->info = atof(number);
                    last = work;

                   for (int i = 0; i < j; i++) {
                       number[i] = '\0';
                   }
                   j = 0;
                }
            }
            fclose(fp);
        }

    return head;
}
