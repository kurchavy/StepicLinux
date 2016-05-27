#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>

static void get_process_name(const pid_t pid, int * count) {
	char procfile[BUFSIZ];
	sprintf(procfile, "/proc/%d/stat", pid);

	FILE* fp = fopen(procfile, "r");
	if (fp) {
		size_t size = fread(procfile, sizeof (char), sizeof (procfile), fp);
		if (size > 0) {
			strtok(procfile, " "); // (1) pid  %d
			char * comm = strtok(NULL, " "); // (2) comm  %s
			//printf("%s\n", comm);
			if (strcmp("(genenv)", comm) == 0)
			{
				*count += 1;
			}
		}
		fclose(fp);
	}
}

int main()
{
	DIR* dir = opendir("/proc/");
	struct dirent *entry;
	int count = 0;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == 4)
		{
			int num = atoi(entry->d_name);
			if (num != 0)
			{
				char *name;
				get_process_name((pid_t)num, &count);
			}
		}
	}
	printf("%d\n", count);
	closedir(dir);

	return 0;
}