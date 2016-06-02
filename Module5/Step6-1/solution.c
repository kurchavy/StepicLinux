#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 128

int main(int argc,char* argv[])
{
	char cmd[80];
	char buf[BUFSIZE];
	FILE *fd;
	int cnt = 0;

	sprintf(cmd, "./%s %s", argv[1], argv[2]);
	fd = popen(cmd, "r");

	while (fgets(buf, BUFSIZE, fd) != NULL) {
		int i;
		for (i = 0; i < BUFSIZE; i++){
			if (buf[i] == '\0')
				break;
			if (buf[i] == '0') 
				cnt++;
		}
	}
	pclose(fd);
	printf("%d\n", cnt);
	return 0;
}
