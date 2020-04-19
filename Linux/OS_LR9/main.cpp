#include <sys/types.h>	//structure UNIX
#include <sys/stat.h>	//stat
#include <sys/wait.h>	//waitpid
#include <sys/msg.h>	//msg queue
#include <unistd.h>		//fork, I/O file
#include <dirent.h>		//operation with direction
#include <csignal>		//signal
#include <stdlib.h> 	//atoi
#include <time.h>		//c_time
#include <stdio.h> 		//I/O C
#include <cstring> 		//std::string
#include <fcntl.h> 		//file
#include <iostream> 	//I/O C++

using namespace std;

struct messeg {
	long type;
	struct stat info;
};

void Print(messeg One) {
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

void OutputFile(const char *file) {	//read file
	messeg One;
	int descriptorFile = open(file, O_RDONLY);	//open file for read
	
	if (descriptorFile != -1) {
		
		while (read(descriptorFile, &One, sizeof(One)) != 0) { //while not EOF read from file
			Print(One);
		}		
		close(descriptorFile);
	}
}

void signalExit(int signum) { //Signal "SIGUSR1" and exit process
	cout << endl << "The end!";
	exit(0);
}

void OutputQueue(int IDmsg) { //Outputting information about file
	messeg One;
	
	while (true) {
		
		signal(SIGUSR1, signalExit);	//wait exit signal
		
		int rec = msgrcv(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0, 0); //read from queue
		
		if (rec != -1) {
				
			Print(One);
			int descriptorFile = open("MyFile.txt", O_WRONLY | O_APPEND);	//open file for write and app
				
			if (descriptorFile != -1) {
				write(descriptorFile, &One, sizeof(One));				//write in file	
				close(descriptorFile);
			}
		}
	}	
}

void signalStart(int signum) { //Signal "SIGUSR2" and start output information about file
	int IDmsg = msgget(1, 0);		//open queue
					
	if (IDmsg == -1) {
		throw "Msg queue not open in main process or already closed";
	}
	
	int descriptorFile = creat("MyFile.txt", 0666);		//create new file
	if (descriptorFile == -1) {
		cout << endl << "Error file. Data will not write in file";
		perror("");
		cout << endl;
	}
	close(descriptorFile);
				
	cout << endl << "Start output!";
				
	OutputQueue(IDmsg);
}

string NextDir(const char *dir, const char *newDir) { //Create path for next direction
	string str;
	
	str.insert(0, dir); //old dir
	if (str.at(str.length() - 1) != '/') {
		str.push_back('/');
	}
	
	str.insert(str.length(), newDir); //old dir + new folder
	
	return str;
}

void Search(const int IDmsg, const char *dirname, const char *filename, const unsigned int size2, const unsigned int size1 = 0) {
	
	DIR *dirID = opendir(dirname);
	dirent *real = NULL;
	struct stat stBuff;
	messeg One;
	One.type = 1;
	string str;
	string FileNameAndDir = NextDir(dirname, filename); //create all path for filename
	
	if (dirID != NULL) {			
		if (stat(FileNameAndDir.c_str(), &stBuff) == 0) {//search filename in here direction
			
			if (static_cast<unsigned int>(stBuff.st_size) > size1 && static_cast<unsigned int>(stBuff.st_size) < size2 ) { //Range size
				
				One.info = stBuff;
				int rec = msgsnd(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0); //Add file in queue
		
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

//First set argv: 1 - mount point, 2 - file name, 3 - min size, 4 - man size
//Second set argv: 1 - mount point, 2 - file name, 3 - max size
//Third set argv: 1 - file name
int main(int argc, char *argv[]) {
	
	try { 
		
		if (argc == 2) { 		//Third set - read file with data
			OutputFile(argv[1]);
			throw "Reading complete!";
		}
		
		pid_t pid = fork();
		
		if (pid == -1) {		//error
		  throw "fork failed";
		}
		
		if (pid == 0) {			//second fork
			
			cout << endl << "Create second process! Wait. Pid: " << getpid() << "; PPID: " << getppid() << endl;
			
			while (true) {
				signal(SIGUSR2, signalStart);
			}
		} else {					//main fork
			msqid_ds info;
			info.msg_qnum = -1;
			int status;
			messeg One;
			One.type = 2;
			
			cout << endl << "Open main process! Pid: " << getpid() << endl;
			int IDmsg = msgget(1, IPC_CREAT | 0666);  //init queue
			
			if (IDmsg == -1) {
				throw "Error create msgget";
			}
			
			if (argc < 2 || argc > 5) {
				throw "Error: invalid set params";
			}
			
			if (argc == 5) { //First set - min and max
				Search(IDmsg, argv[1], argv[2], atoi(argv[4]), atoi(argv[3]));
			}	
			if (argc == 4) { //Second set - only max
				Search(IDmsg, argv[1], argv[2], atoi(argv[3]));
			}	
			
			msgsnd(IDmsg, (struct messeg *) (&One), sizeof(One.info), 0);
			
			kill(pid, SIGUSR2); //Search termination signal
			
			while (info.msg_qnum != 0) {	//while in queue there items
				msgctl(IDmsg, IPC_STAT, &info);
			}

			kill(pid, SIGUSR1); //Signal output end results
			
			waitpid(pid, &status, 0);
		}	
	
	} catch (const char *str) {
		cout << endl << str;
	}
	
	return 0;
}
