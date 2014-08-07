#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
int main( void )
{
	pid_t childpid;
	int status;
	childpid = fork();
	if ( childpid < 0 )
	{
		perror( "fork()" );
		exit( EXIT_FAILURE );
	}
	else if ( childpid == 0 )
	{
		int res;
		puts( "In child process" );
		//sleep( 3 );//让子进程睡眠3秒，看看父进程的行为
		printf("\tchild pid = %d\n", getpid());
		//res = execlp("ls","ls",(char *)0);
		//res = execlp("notcmd","notcmd",(char *)0);
		//res = execlp("ls","proc_name","-?","/home/cm/whjs",(char *)0);
		res = execlp("ls","proc_name","/home/cm/whjs",(char *)0);
		//res = execlp("./wpara","./demo",(char *)0);
		//关于execlp第2个参数 这里第一个参数才是真正的文件 至于第二个可以是任意的字符 
		//第一个参数：可执行文件路径 第二个参数：在进程中显示该进程的名字，可以是任意字符串
		//比如第二个参数是 ls 则
		//ls: invalid option -- '?'
		//Try 'ls --help' for more information.
		//如果是proc_name则
		//proc_name: invalid option -- '?'
		//Try 'proc_name --help' for more information.
		//该参数是用于新进程的argv[0] 
		//如果execlp执行成功则后续的代码不再执行 如果失败则返回-1 继续执行后续代码
		printf("res=%d\n",res);
		printf("\tchild ppid = %d\n", getppid());
		//exit(EXIT_SUCCESS);//如果这里不退出 且execlp执行失败的话 那么后续的share code 也会执行
	}
	else
	{
		waitpid( childpid, &status, 0 );
		puts( "in parent" );
		printf( "\tparent pid = %d\n", getpid() );
		printf( "\tparent ppid = %d\n", getppid() );
		printf( "\tchild process exited with status %d \n", status );
	}
	printf("%d\n",getpid());//child parent share code
	exit(EXIT_SUCCESS);
}
