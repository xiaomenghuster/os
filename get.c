#include "myhead.h"

void main(){
    semid=semget(SEM_KEY,4,IPC_CREAT|0666); //申请信号灯，不赋值
    shmid_s = shmget(SHM_S_KEY,SIZE,IPC_CREAT|0666); //申请s缓冲区，不赋初值
    s=(char*)shmat(shmid_s,NULL,SHM_R|SHM_W);   //绑定
	//s[1]=0;
	*(s+1)='0';
	//打开源文件
	//puts("open fileA");
	fout=fopen(fileA,"r");
	//puts("fileA");
	while(!feof(fout)){
		P(semid,0);
		*s=fgetc(fout);
		//putchar(*s);
		V(semid,1);
	}
	//puts("end of while");
	s[1]='1';
	V(semid,1);
	fclose(fout);
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
