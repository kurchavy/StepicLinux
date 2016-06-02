#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
//#include <unistd.h>

int u1 = 0, u2 = 0;

void sig_handler(int signal)
{ 
	if (signal == 10)
		u1++;
	if (signal == 12)
		u2++;
	if (signal == 15){
		printf("%d %d\n", u1, u2);
		exit(1);
	}
}

int main()
{
	signal(SIGTERM, sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1){
		usleep(500000);
	}	

	return 0;
}
