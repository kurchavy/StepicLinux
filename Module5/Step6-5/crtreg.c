#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	int i;
    int shmid1;
    key_t key1;
    int *shm1, *s1;

    int shmid2;
    key_t key2;
    int *shm2, *s2;

    key1 = 7777;
    key2 = 7778;

    /*
     * Create the segment.
     */
    if ((shmid1 = shmget(key1, 1000, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    if ((shmid2 = shmget(key2, 1000, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }


    /*
     * Now we attach the segment to our data space.
     */
    if ((shm1 = shmat(shmid1, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }
    if ((shm2 = shmat(shmid2, NULL, 0)) == (int *) -1) {
        perror("shmat");
        exit(1);
    }


    for (i = 0; i < 100; i++){
        *(shm1 + i * sizeof(int))  = 5;
        *(shm2 + i * sizeof(int))  = 10;
    }
}
