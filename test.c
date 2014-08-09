#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <error.h>
#include <sys/wait.h>

#define BUFSIZE 512
#define MAXLINE 4096

void ioread(){
	int n;
	char buf[BUFSIZE];

	while ( ( n = read(STDIN_FILENO,buf,BUFSIZE)) > 0 ){
		if ( write(STDOUT_FILENO,buf,n) != n ){
			fprintf(stderr,"read error\n");
			exit(EXIT_FAILURE);
		}
	}

	if ( n < 0 ){
		fprintf(stderr,"read error\n");
		exit(EXIT_FAILURE);
	}
}

void stdcopy(){
	int c;
	while ( (c = getc(stdin)) != EOF ){
		if ( putc(c,stdout) == EOF ){
			fprintf(stderr,"write error\n");
			exit(EXIT_FAILURE);
		}
	}

	if ( ferror(stdin) ){
		fprintf(stderr,"read error\n");
		exit(EXIT_FAILURE);
	}
}

void lsdir(int argc,char *argv[]){
	DIR *dp;
	struct dirent *dirp;

	if ( argc < 2 ){
		fprintf(stderr,"./a.out /filepath");
		exit(EXIT_FAILURE);
	}
	if ((dp = opendir(argv[1])) == NULL) {
		fprintf(stderr,"file open error %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	while ((dirp = readdir(dp)) != NULL) {
		printf("%s\n", dirp->d_name);
	}
	closedir(dp);

}

void processid(){
	printf("process id %ld\n",(long)getpid());
}

void execwait(){
	char buf[MAXLINE];
	pid_t pid;
	int status;

	printf("%%");
	while ( fgets(buf,MAXLINE,stdin) != NULL){
		if ( buf[strlen(buf)-1] == '\n'){
			buf[strlen(buf)-1] = 0;
		}
		if ( ( pid = fork()) < 0 ){
			fprintf(stderr,"%s\n","fock error");
			exit(EXIT_FAILURE);
		}
		if ( pid == 0 ){
			execlp(buf,buf,(char *)0);
			fprintf(stderr,"count exec proc %s",strerror(errno));
			exit(127);
		}

		waitpid(pid,&status,0);
		printf("%%");
	}

}

void testerr(char *argv[]){
	fprintf(stderr,"%s\n",strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
}

void testuser(){
	printf("%d \t %d\n",getuid(),getpid());
}
int main(int argc, char *argv[]) {

	//printf("Hello C\n");
	//lsdir(argc,argv);
	//ioread();
	//stdcopy();
	//processid();
	//execwait();
	//testerr(argv);
	testuser();
	return 0;
}

