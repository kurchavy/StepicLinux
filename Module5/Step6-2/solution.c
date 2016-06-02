#include <fcntl.h>
#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

#define MAX_BUF 8

int main()
{
    int fd1, fd2;
    char * fifo1 = "in1";
    char * fifo2 = "in2";
    int total = 0;

    fd1 = open(fifo1, O_RDONLY);
    fd2 = open(fifo2, O_RDONLY);
    
    while (1)
	{
		int sum = 2;
  		fd_set fds;
  		int maxfd;
  		int res;

  		FD_ZERO(&fds); // Clear FD set for select
  		FD_SET(fd1, &fds);
  		FD_SET(fd2, &fds);

  		maxfd = fd1 > fd2 ? fd1 : fd2;

  		select(maxfd + 1, &fds, NULL, NULL, NULL);

  		if (FD_ISSET(fd1, &fds))
  		{
     		char buf1[MAX_BUF];
     		res = read(fd1, buf1, sizeof(buf1));
     		if (res > 0)
     		{
     			total = total + atoi(buf1);
     		}
     		else
     		{
     			sum--;
     		}

  		}
		if (FD_ISSET(fd2, &fds))
		{	
			char buf2[MAX_BUF];
		    res = read(fd2, buf2, MAX_BUF);
		    if (res > 0)
		    {
		        total = total + atoi(buf2);
		    }
		    else
     		{
     			sum--;
     		}
		}
		if (sum == 0)
			break;
	}
	printf("%d\n", total);

    return 0;
}
