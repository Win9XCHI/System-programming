#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <unistd.h>
#include <dirent.h>
#include <csignal>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <cstring>

using namespace std;

struct messeg {
	long type;
	struct stat info;
};

void signalExit(int signum) { //Signal "SIGUSR1" and exit process
	cout << endl << "The end!";
	exit(0);
}

void signalStart(int signum) { //Start output information about file
	int IDmsg = msgget(1, 0);
					
	if (IDmsg == -1) {
		throw "Msg queue not open in main process or already closed";
	}
				
	cout << endl << "Start output!";
				
	Print(IDmsg);
}

void Print(int IDmsg) { //Outputting information about file
	messeg One;
	
	while (true) {
		
		signal(SIGUSR1, signalExit);
		
		int rec = msgrcv(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0, 0); 
		
		if (rec != -1) {
				cout << endl;
				printf("ID of containing device:  [%lx,%lx]\n", (long) major(One.info.st_dev), (long) minor(One.info.st_dev));

				printf("File type:                ");

				switch (One.info.st_mode & S_IFMT) {
					   case S_IFBLK:  printf("block device\n");            break;
					   case S_IFCHR:  printf("character device\n");        break;
					   case S_IFDIR:  printf("directory\n");               break;
					   case S_IFIFO:  printf("FIFO/pipe\n");               break;
					   case S_IFLNK:  printf("symlink\n");                 break;
					   case S_IFREG:  printf("regular file\n");            break;
					   case S_IFSOCK: printf("socket\n");                  break;
					   default:       printf("unknown?\n");                break;
				}

				printf("I-node number:            %ld\n", (long) One.info.st_ino);

				printf("Mode:                     %lo (octal)\n", (unsigned long) One.info.st_mode);

				printf("Link count:               %ld\n", (long) One.info.st_nlink);
				printf("Ownership:                UID=%ld   GID=%ld\n", (long) One.info.st_uid, (long) One.info.st_gid);

				printf("Preferred I/O block size: %ld bytes\n", (long) One.info.st_blksize);
				printf("File size:                %lld bytes\n", (long long) One.info.st_size);
				printf("Blocks allocated:         %lld\n", (long long) One.info.st_blocks);

				printf("Last status change:       %s", ctime(&One.info.st_ctime));
				printf("Last file access:         %s", ctime(&One.info.st_atime));
				printf("Last file modification:   %s", ctime(&One.info.st_mtime));
		}
	}	
}

string NextDir(const char *dir, const char *newDir) { //Create path for next direction
	string str;
	
	str.insert(0, dir);
	if (str.at(str.length() - 1) != '/') {
		str.push_back('/');
	}
	
	str.insert(str.length(), newDir);
	
	return str;
}

void Search(const int IDmsg, const char *dirname, const char *filename, const unsigned int size2, const unsigned int size1 = 0) {
	
	DIR *dirID = opendir(dirname);
	dirent *real = NULL;
	struct stat stBuff;
	messeg One;
	One.type = 1;
	string str;
	string FileNameAndDir = NextDir(dirname, filename);
	
	if (dirID != NULL) {			
		if (stat(FileNameAndDir.c_str(), &stBuff) == 0) {//all pathname
			
			if (static_cast<unsigned int>(stBuff.st_size) > size1 && static_cast<unsigned int>(stBuff.st_size) < size2 ) {
				
				One.info = stBuff;
				int rec = msgsnd(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0); 
		
				if (rec == -1) {
					throw "Msgsnd error";
				}	
			}
		} 
			
		while ((real = readdir(dirID)) != NULL) {
						
			if (strcmp(real->d_name, ".") != 0 && strcmp(real->d_name, "..") != 0) { //Ignore '.' and '..' files
				cout << "Give to dir: ";
				printf("%lu - %s [%d] %d\n", real->d_ino, real->d_name, real->d_type, real->d_reclen);
				str = NextDir(dirname, real->d_name);
				Search(IDmsg, str.c_str(), filename, size2, size1);
			}
		}
		closedir(dirID);
	}
}

//argv: 1 - mount point, 2 - file name, 3 - min size or max size if argv[4] not fount, 4 - min size
int main(int argc, char *argv[]) {
	
	try { 
		
		pid_t pid = fork();
		
		if (pid == -1) {	//error
		  throw "fork failed";
		}
		
		if (pid == 0) {		//second fork
			
			cout << endl << "Create second process! Wait. Pid: " << getpid() << "; PPID: " << getppid() << endl;
			
			while (true) {
				signal(SIGUSR2, signalStart);
			}
		}
		
		else {				//main fork
			msqid_ds info;
			info.msg_qnum = -1;
			int status;
			messeg One;
			One.type = 2;
			
			cout << endl << "Open main process! Pid: " << getpid() << endl;
			int IDmsg = msgget(1, IPC_CREAT | 0666); 
			
			if (IDmsg == -1) {
				throw "Error create msgget";
			}
			
			if (argc < 2 || argc > 5) {
				throw "Error: invalid set params";
			}
			if (argc == 5) {
				Search(IDmsg, argv[1], argv[2], atoi(argv[4]), atoi(argv[3]));
			}	
			if (argc == 4) {
				Search(IDmsg, argv[1], argv[2], atoi(argv[3]));
			}	
			
			int rec = msgsnd(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0);
			cout << endl << rec << endl;
			perror("");
			
			msgctl(IDmsg, IPC_STAT, &info);
			cout << endl << info.msg_qnum << endl;
			
			kill(pid, SIGUSR2);
			
			while (info.msg_qnum != 0) {
				msgctl(IDmsg, IPC_STAT, &info);
			}

			kill(pid, SIGUSR1);
			
			waitpid(pid, &status, 0);
		}	
	
	} catch (const char *str) {
		cout << endl << str;
	}
	
	return 0;
}
