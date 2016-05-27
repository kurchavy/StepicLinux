#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t process_id = 0;
	pid_t sid = 0;

	// Create child process
	process_id = fork();
	
	if (process_id > 0)
	{
		printf("%d\n", process_id);
		// return success in exit status
		exit(0);
	}
	sid = setsid();
	chdir("/");
	close(stdin);
	close(stdout);
	close(stderr);
	while (1) { }
	return 0;
}
