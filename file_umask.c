/* file_umask.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) { /* 파일 생성 시 기본 권한 제어 */

	int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	umask(0);

	if (creat("test1.txt", mode) < 0) {
		perror("creat : test1.txt");
		exit(1);
	}

	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

	if (creat("test2.txt", mode) < 0) {
		perror("creat : test1.txt");
		exit(1);
	}
}
