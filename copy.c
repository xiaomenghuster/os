#include "myhead.h"

void main(){
    semid=semget(SEM_KEY,4,IPC_CREAT|0666); //4个信号灯申请，不赋初值；
    shmid_s = shmget(SHM_S_KEY,SIZE,IPC_CREAT|0666); //申请S缓冲区，不赋初值
    s=(char*)shmat(shmid_s,NULL,SHM_R|SHM_W);   //绑定
    shmid_t = shmget(SHM_T_KEY,SIZE,IPC_CREAT|0666); //申请T缓冲区，不赋初值
    t=(char*)shmat(shmid_t,NULL,SHM_R|SHM_W);   //绑定
    while(1){
	P(semid,1);
        P(semid,2);
	if(*(s+1)=='1'){
	    t[1]=s[1];
	    V(semid,3);
	    break;
	}
	*t=*s;
	//putchar(*s);
	V(semid,0);
	V(semid,3);
    }
    V(semid,3);	
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
