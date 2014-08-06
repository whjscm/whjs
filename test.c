#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 512

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
int main(int argc, char *argv[]) {

	//printf("Hello C\n");
	//lsdir(argc,argv);
	//ioread();
	stdcopy();
	return 0;
}

