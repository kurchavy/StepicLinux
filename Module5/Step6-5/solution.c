#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUFSIZE 128

int main(int argc,char* argv[])
{
	int k1 = atoi(argv[1]);
	int k2 = atoi(argv[2]);
	key_t key1 = k1;
	key_t key2 = k2;
	key_t key3 = 512997;

	int shmid1 = shmget(key1, 1000, 0666);
	int* shm1 = shmat(shmid1, NULL, 0);
	int shmid2 = shmget(key2, 1000, 0666);
	int* shm2 = shmat(shmid2, NULL, 0);

	int shmid3 = shmget(key3, 1000, IPC_CREAT | 0666);
	int* shm3 = shmat(shmid3, NULL, 0);

	int i = 0;
	int *s = shm3;
	while(i < 100){
		//int sum = *(shm1 * sizeof(int)) + *(shm2 + i * sizeof(int));
		//*(shm3 + i * sizeof(int)) = sum;
		*s++ = *shm1++ + *shm2++;
		i++;
	}
	printf("%d\n", key3);
	i = 0;
    while(i < 100){
		printf("%d\n", *(shm3 + i * sizeof(int)));
		i++;
	}
	return 0;
}
