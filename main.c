#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include "myhead.h"

pid_t pid1,pid2,pid3;
//struct shmid_ds buf;  //缓冲区属性

void main(){
    semid=semget(SEM_KEY,4,IPC_CREAT|0666); //创建信号灯
    semopts.val=1;  //第一个信号灯的初值为1
    semctl(semid,0,SETVAL,semopts);   
    semopts.val=0;  //第二个信号灯的初值为0
    semctl(semid,1,SETVAL,semopts);
    semopts.val=1;  //第三个信号灯的初值为1
    semctl(semid,2,SETVAL,semopts);   
    semopts.val=0;  //第四个信号灯的初值为0
    semctl(semid,3,SETVAL,semopts);	

	shmid_s = shmget(SHM_S_KEY,SIZE,IPC_CREAT|0666); //申请S缓冲区，不赋初值
    s=(char*)shmat(shmid_s,NULL,SHM_R|SHM_W);   //绑定
    shmid_t = shmget(SHM_T_KEY,SIZE,IPC_CREAT|0666); //申请T缓冲区，不赋初值
    t=(char*)shmat(shmid_t,NULL,SHM_R|SHM_W);   //绑定	

	if((pid1=fork())==0){
		//puts("get");
		execv("./get",NULL);
	}
	else {	
		if((pid2=fork())==0)
			execv("./copy",NULL);
		else{ 
			if((pid3=fork())==0)
				execv("./put",NULL);		
		}
	}
	wait(NULL);
	wait(NULL);
	wait(NULL);
			
    semctl(semid,0,IPC_RMID);
    semctl(semid,1,IPC_RMID);  //删除信号灯//删除信号灯
    semctl(semid,2,IPC_RMID);
    semctl(semid,3,IPC_RMID);  
	shmctl(shmid_s,IPC_RMID,0);//删除共享内存
	shmctl(shmid_t,IPC_RMID,0);
	//printf("end");
}

