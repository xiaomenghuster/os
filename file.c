#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

char path[]="/home/xiaomeng/os/dir";

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
		//puts("the end~"); //打印出错信息
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
			//打印目录项的深度，目录名等信息
			showmode(statbuf.st_mode);
			printf("  %ld ",statbuf.st_nlink);
			printf("%s  %d  ",entry->d_name,depth);
	
			struct passwd *wd;
			wd=getpwuid(statbuf.st_uid);
			printf("%s  ",wd->pw_name);

			struct group *group;
			group=getgrgid(statbuf.st_uid);
			printf("%s  	",group->gr_name);

			printf("%ld  ",statbuf.st_size);

			unsigned long t=statbuf.st_atime;
			printf("%s",ctime(&t));

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
			showmode(statbuf.st_mode);
			printf("  %ld ",statbuf.st_nlink);
			printf("%s  %d  ",entry->d_name,depth);
	
			struct passwd *wd;
			wd=getpwuid(statbuf.st_uid);
			printf("%s  ",wd->pw_name);

			struct group *group;
			group=getgrgid(statbuf.st_uid);
			printf("%s  	",group->gr_name);

			printf("%ld  ",statbuf.st_size);

			unsigned long t=statbuf.st_atime;
			printf("%s",ctime(&t));
		}
	}
	chdir(path);	//返回父目录
	closedir(dp);	//关闭目录项
}

int main(){
	char dir[100];
	printf("please input path:\n");
	scanf("%s",dir);
	printdir(dir,0);
	return 0;	
}

void showmode(unsigned short st_mode){
	if(st_mode&S_IRUSR)
		putchar('r');
	else
	 	putchar('-');			
	if(st_mode&S_IWUSR)
		putchar('w');
	else 
		putchar('-');
	if(st_mode&S_IXUSR)
		putchar('x');
	else 
		putchar('-');
	if(st_mode&S_IRGRP)
		putchar('r');
	else 
		putchar('-');
	if(st_mode&S_IWGRP)
		putchar('w');
	else 
		putchar('-');
	if(st_mode&S_IXGRP)
		putchar('x');
	else 
		putchar('-');
	if(st_mode&S_IROTH)
		putchar('r');
	else 
		putchar('-');
	if(st_mode&S_IWOTH)
		putchar('w');
	else 
		putchar('-');
	if(st_mode&S_IXOTH)
		putchar('x');
	else 
		putchar('-');
}




