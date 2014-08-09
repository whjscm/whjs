#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <error.h>
#include <sys/wait.h>
#define MAXLINE 4096

static void sig_int(int);

int main(int argc,char *argv[]){
	pid_t pid;
	int status;
	char buf[MAXLINE];

	if ( signal(SIGINT,sig_int) == SIG_ERR ){
		fprintf(stderr,"signal error:%s\n",strerror(errno));
        	exit(1); 
	}

	printf("%%3 ");
	while ( fgets(buf,MAXLINE,stdin) != NULL ){
		if ( buf[strlen(buf)-1] == '\n' ){
			buf[strlen(buf)-1] = 0;
		}

		if ( (pid = fork()) < 0 ){
			fprintf(stderr,"fork error:%s\n",strerror(errno));
			exit(1);	
		}

		if ( pid == 0 ){
			execlp(buf,buf,(char *)0);
			fprintf(stdout,"exec error:%s\n",strerror(errno));
            		exit(127); 

		}

		if ( (pid = waitpid(pid,&status,0)) < 0 ){
			fprintf(stderr,"wait error:%s\n",strerror(errno));
            		exit(1); 

		}else{
			//printf("test wait success info\n");
		}

		printf("%%2 ");
	}
	exit(0);
}


void sig_int(int signo){
	printf("Interrupt\n%%1 ");
	fflush(NULL);//这里如果不加fflush 则 会不输出%1 等到回车后才输出%1且重复输出
}
