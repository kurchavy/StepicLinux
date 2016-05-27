#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>

void find_parent(int p, int parent, int *count)
{
	pid_t ppid;
	char fn[80];
	sprintf(fn, "/proc/%d/stat", p);
	
	FILE* fp = fopen(fn, "r");
	if (fp) {
		//printf("%s opened\n", fn);
		size_t size = fread(fn, sizeof (char), sizeof (fn), fp);
		if (size > 0) {
			strtok(fn, " "); // (1) pid  %d
			strtok(NULL, " "); // (2) comm  %s
			strtok(NULL, " "); // (3) state  %c
			char * s_ppid = strtok(NULL, " "); // (4) ppid  %d
			ppid = atoi(s_ppid);
			//printf("%s\n", s_ppid);
		}
		fclose(fp);
	}
	
	if (ppid == parent)
	{
		
		*count += 1;
		return;
	}
	if (ppid <= 1) return;
	find_parent(ppid, parent, count);

}


int main(int argc, char **argv)
{
	int p = atoi(argv[1]);
	DIR* dir = opendir("/proc/");
	struct dirent *entry;
	int count = 1;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == 4)
		{
			int num = atoi(entry->d_name);	
			if (num != 0)
			{
				find_parent(num, p, &count);
			}	 
		}	
	}
	printf("%d\n", count);
	closedir(dir);
	return 0;
}
