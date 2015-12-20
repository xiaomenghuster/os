#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}semopts;
int SEM_KEY=1234;  //信号量的key
int SHM_S_KEY=1111;  //共享内存的key
int SHM_T_KEY=2222;
int semid; //信号量集的IPC标志符
int shmid_s; //共享内存句柄
int shmid_t;
int SIZE=2; //共享内存大小
char *s;  //共享内存S绑定的局部变量
char *t;  //共享内存T绑定的局部变量
char fileA[]="./fileA.txt";
char fileB[]="./fileB.txt";
FILE *fout;
FILE *fin;

void P(int semid,int index);
void V(int semid,int index);  //PV操作


