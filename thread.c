#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/sem.h>

void P(int semid,int index);
void V(int semid,int index);
void *subp1();
void *subp2();
int semid;  //信号量
int s;      //数值

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
}semopts;

main(){    
    s=0;
    pthread_t p1,p2;
    semid=semget(1234,2,IPC_CREAT|0666); //创建信号灯
    semopts.val=1;  //第一个信号灯的初值为1
    semctl(semid,0,SETVAL,semopts);   
    semopts.val=0;  //第二个信号灯的初值为0
    semctl(semid,1,SETVAL,semopts);
    pthread_create(&p1,NULL,(void *)subp1,NULL);
    pthread_create(&p2,NULL,(void *)subp2,NULL);    //创建两个线程subp1，subp2
    puts("init S=0");
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    //等待两个线程运行结束
    semctl(semid,0,IPC_RMID);
    semctl(semid,1,IPC_RMID);  //删除信号灯
}

void *subp1(){
    int i;
    for(i=0;i<10;i++){
	P(semid,0);
	//puts("subp1");
	s++;
	puts("s++");
	V(semid,1);
    }
    return;
}

void *subp2(){
    int j;
    for(j=0;j<10;j++){
	P(semid,1);
	//puts("subp2");
	printf("S=%d\n",s);
	V(semid,0);
    }
    return;
}

void P(int semid,int index){
    struct sembuf sem;
    sem.sem_num=index;  //要处理的信号量的下标
    sem.sem_op=-1; 	//要执行的操作
    sem.sem_flg=SEM_UNDO;//操作标志
    semop(semid,&sem,1); //参数依次为semget函数返回的信号量
			//标志符，指向结构数组的指针，操作次数
    return;
}
void V(int semid,int index){
    struct sembuf sem;
    sem.sem_num=index;
    sem.sem_op=1;
    sem.sem_flg=SEM_UNDO;   //NO_WAIT 和SEM_UNDO的区别！
    semop(semid,&sem,1);
    return;
}

