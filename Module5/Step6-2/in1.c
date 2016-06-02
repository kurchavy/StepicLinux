#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char* argv[]) {
	char *name = argv[1];
	
	mkfifo(name, 0666);

	int fd = open(name, O_WRONLY);

	int i;
	for (i = 10; i<20; i++) {
		char *buf;
		sprintf(buf, "%d", i);
		write(fd, buf, sizeof(buf));
		printf("Wrote %d\n", i);
	}
	close(fd);
}