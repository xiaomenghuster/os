#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
char path[]="/home/xmhuster/words/files";

void showmode(unsigned short);
/*DIR *opendir(const char *name); //打开一个目录
struct dirent* readdir(DIR*);	//读取目录中的下一个目录
int chdir(const char *path);	//改变目录
int closedir(DIR*);		//关闭目录流
*/
void printdir(char *dir,int depth){
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if(!(dp=opendir(dir))){ //如果打开dir目录不成功
		puts("the end~"); //打印出错信息
		return;		//返回
	}
	chdir(dir); //将dir设置为当前目录
	while((entry=readdir(dp))!=NULL){  //读到一个目录项
		//sleep(1);
		lstat(entry->d_name,&statbuf); //以该目录项的名字为参数，调用lstat得到该
				 //目录项的相关信息
		int abc=statbuf.st_mode & S_IFDIR;
		if(abc==S_IFDIR){  //判断是否是目录
			if((strcmp(entry->d_name,".")==0)||(strcmp(entry->d_name,"..")==0))
				continue;
			//puts("dir");
			//打印目录项的深度，目录名等信息
			printf("%s\t %d\t ",entry->d_name,depth);
			showmode(abc);
			printf("%ld\t ",statbuf.st_size);
			unsigned long t=statbuf.st_atime;
			printf("%s\n",ctime(&t));

			//递归调用printdir，打印子目录的信息，其中depth+4
			char subpath[100];
			strcpy(subpath,dir);
			strcat(subpath,"/");
			strcat(subpath,entry->d_name);
			//puts(subpath);
			printdir(subpath,depth+4);
		}
		else {
			//puts("file");//打印文件的深度，文件名等信息，文件类型，大小，时间
			//printf("%d\t",depth);
			printf("%s\t %d\t ",entry->d_name,depth);
			showmode(abc);
			printf("%ld\t ",statbuf.st_size);
			unsigned long t=statbuf.st_atime;
			printf("%s\n",ctime(&t));
		}
	}
	chdir(path);	//返回父目录
	closedir(dp);	//关闭目录项
}

int main(){
	puts("name\t depth\t mode\t size\t time");
	printdir(path,0);
	return 0;	
}

void showmode(unsigned short st_mode){
	switch(st_mode){
		case S_IFDIR: printf("dir\t "); break;
		default: 	  printf("file\t ");break;
	}
}




