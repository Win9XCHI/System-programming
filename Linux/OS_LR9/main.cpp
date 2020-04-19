#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <cstring>

using namespace std;

void *Print(void *arg) { //Thread for outputting information about file
	struct stat sb = * (struct stat *) arg;
	cout << endl;
	printf("ID of containing device:  [%lx,%lx]\n", (long) major(sb.st_dev), (long) minor(sb.st_dev));

	printf("File type:                ");

    switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
    }

    printf("I-node number:            %ld\n", (long) sb.st_ino);

    printf("Mode:                     %lo (octal)\n", (unsigned long) sb.st_mode);

    printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n", (long) sb.st_uid, (long) sb.st_gid);

    printf("Preferred I/O block size: %ld bytes\n", (long) sb.st_blksize);
    printf("File size:                %lld bytes\n", (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n", (long long) sb.st_blocks);

    printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));	
    
    return 0;
}

string NextDir(const char *dir, const char *newDir) { //Convert to string //Create path for next direction
	string str;
	
	str.insert(0, dir);
	if (str.at(str.length() - 1) != '/') {
		str.push_back('/');
	}
	
	str.insert(str.length(), newDir);
	
	return str;
}

bool Search(const char *dirname, const char *filename, const unsigned int size2, const unsigned int size1 = 0) {

	if (dirname[strlen(dirname) - 1] == '.' || strstr(dirname,"..") != 0) { //Ignore '.' and '..' files
		return false;
	}
	
	DIR *dirID = opendir(dirname);
	dirent *real = NULL;
	struct stat stBuff;
	int result = 0;
	pthread_t thread;
	bool flag = false;
	string str;
	string FileNameAndDir = NextDir(dirname, filename);
	
	if (dirID != NULL) {			
			if (stat(FileNameAndDir.c_str(), &stBuff) == 0) {//all pathname
				
				if (static_cast<unsigned int>(stBuff.st_size) > size1 && static_cast<unsigned int>(stBuff.st_size) < size2 ) {
					
					result = pthread_create(&thread, NULL, Print, &stBuff);
					if (result != 0) {
						cout << endl << "File fount, but an error has occurred";
					}	
					pthread_join(thread, NULL);	
					flag = true;	
				}
			} 
			
		while ((real = readdir(dirID)) != NULL) {
			cout << "Give to dir: ";
			printf("%lu - %s [%d] %d\n", real->d_ino, real->d_name, real->d_type, real->d_reclen);
			str = NextDir(dirname, real->d_name);
			flag = Search(str.c_str(), filename, size2, size1);
		}
		closedir(dirID);
	}
	
	return flag;
}


int main(int argc, char *argv[]) {
	
	try {
		
		if (argc < 2 || argc > 4) {
			throw "Error: invalid set params";
		}
		if (argc == 4) {
			if (!Search("/home/yehor/Projects", argv[1], atoi(argv[3]), atoi(argv[2]))) {
				throw "File not found";
			}	
		}	
		if (argc == 3) {
			if (!Search("/home/yehor/Projects", argv[1], atoi(argv[2]))) {
				throw "File not found";
			}
		}
	
	} catch (const char *str) {
		cout << endl << str;
	}
	
	return 0;
}
