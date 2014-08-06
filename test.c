#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
	DIR *dp;
	struct dirent *dirp;

	if ((dp = opendir(".")) == NULL) {
		fprintf(stderr,"file open error");
	}
	while ((dirp = readdir(dp)) != NULL) {
		printf("%s\n", dirp->d_name);
	}
	close(dp);

	printf("Hello Eclipse C");
	return 0;
}
