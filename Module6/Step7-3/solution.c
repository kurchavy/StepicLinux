#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

struct sockaddr_in local;

int main(int argc, char* argv[])
{
	if (argc != 2)
		return -1;

	int s = socket(AF_INET, SOCK_DGRAM, 0);
	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(atoi(argv[1]));
	local.sin_family = AF_INET;

	int result = bind(s, (struct sockaddr*) &local, sizeof(local));

	while(1){
		char buf[10000];
		int i=0;
		//for (i=0; i<BUFSIZ;i++)
		//	buf[i] = 0;

		int sz = read(s, buf, 10000);
		if (buf[0] == 'O' && buf[1] == 'F' && buf[2] == 'F')
			break;
		printf("%s\n", buf);
		//if (strcmp("OFF\0", buf) == 0)
		//	break;
		//if (buf[sz] == '\n')
		//	printf("%s\n", buf);

	}
	return 0;
}
