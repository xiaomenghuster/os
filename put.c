#include "myhead.h"

void main(){
    semid=semget(SEM_KEY,4,IPC_CREAT|0666); //信号灯申请
    shmid_t = shmget(SHM_T_KEY,SIZE,IPC_CREAT|0666); //申请T缓冲区，不赋初值
    t=(char*)shmat(shmid_t,NULL,SHM_R|SHM_W);   //绑定
	shmid_s = shmget(SHM_S_KEY,SIZE,IPC_CREAT|0666); //申请S缓冲区，不赋初值
    s=(char*)shmat(shmid_s,NULL,SHM_R|SHM_W);   //绑定
    fin=fopen(fileB,"w");
    while(1){
		P(semid,3);	
		if(t[1]=='1'){
			break;
		}
		putchar(*t);
		fputc(*t,fin);
		V(semid,2);
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
    sem.sem_flg=SEM_UNDO;   
    semop(semid,&sem,1);
    return;
}
