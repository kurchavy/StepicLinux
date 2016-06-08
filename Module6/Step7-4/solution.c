#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_in local;

int acs(void const *a, void const* b){
	return (*(char*)b - *(char*)a);
}

int main(int argc, char* argv[])
{
	if (argc != 2)
		return -1;

	int ss = socket(AF_INET, SOCK_STREAM, 0);
	int cs;

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(atoi(argv[1]));
	local.sin_family = AF_INET;

	bind(ss, (struct sockaddr*)&local, sizeof(local));
	listen(ss,5);
	
	cs = accept(ss, NULL, NULL);
	char buf[BUFSIZ];
	int i=0;
	for (i=0;i<BUFSIZ;i++)
		buf[i] = 0;
	int nr;
	while((nr = read(cs, buf, BUFSIZ)) > 0) {
        	if(strcmp(buf, "OFF") == 0) 
        		break;
        	qsort(buf, strlen(buf), sizeof(char), acs);
			write(cs, buf, strlen(buf));
    }
	close(cs);
	close(ss);
	return 0;
}
