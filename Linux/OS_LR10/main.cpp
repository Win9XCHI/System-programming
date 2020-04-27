#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <ctime>

static struct termios stored_settings; 

void set_keypress(void) {
	struct termios new_settings;

	tcgetattr(0,&stored_settings);

	new_settings = stored_settings;

	//It is fine, really
	new_settings.c_lflag &= (~ICANON & ~ECHO & ~ECHOK & ~ISIG); //ECHOK for kill, ISIG for SUSP, but QUIT and INTR as SUSP
	//new_settings.c_oflag &= (~OPOST & ~ONLCR); //\n -> \r
	new_settings.c_cc[VTIME] = 8;
	new_settings.c_cc[VMIN] = 5;
	new_settings.c_cc[VSTOP] = 's';
	new_settings.c_cc[VSTART] = 'w';
	new_settings.c_cc[VKILL] = 'k';
	new_settings.c_cc[VQUIT] = 'q';
	new_settings.c_cc[VSUSP] = 'n';
	new_settings.c_cc[VERASE] = 'e';
	new_settings.c_cc[VINTR] = 'i';

	tcsetattr(0,TCSANOW,&new_settings);
	return;
}

void reset_keypress(void) {
	
	tcsetattr(0,TCSANOW,&stored_settings);
	return;
}

int main(void) {
	fd_set rfds;
	struct timeval tv;
	int retval;
	int start, end, t;
	
	set_keypress();
	pid_t pid = fork();

	while(1) {
		
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		
		tv.tv_sec = 0;
		tv.tv_usec = 0;	
		retval = select(2, &rfds, NULL, NULL, &tv);
		
		start = clock();
		if (retval) {
			
			printf("Data is available now. Process: %d \n", pid);
			getc(stdin);
			
		} 
		else {
			printf("No data available. Process: %d\n", pid);
		}
		end = clock();
		
		t = (end - start);
		printf("Time: %d\n", t);
		usleep(1000000);
	}
	reset_keypress();
	exit(0);
}
