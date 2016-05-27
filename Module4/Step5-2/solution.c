#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int p = (int)getpid();

	char fn[80];
	sprintf(fn, "/proc/%d/stat", p);

	FILE* fp = fopen(fn, "r");
	if (fp) {
		size_t size = fread(fn, sizeof (char), sizeof (fn), fp);
		if (size > 0) {
			strtok(fn, " "); // (1) pid  %d
			strtok(NULL, " "); // (2) comm  %s
			strtok(NULL, " "); // (3) state  %c
			char * s_ppid = strtok(NULL, " "); // (4) ppid  %d
			pid_t ppid = atoi(s_ppid);
			printf("%s\n", s_ppid);
		}
		fclose(fp);
	}
    	return 0;
}
