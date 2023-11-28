/* file_check.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	int fd;
	if(argc < 2) { /* 프로그램 이름만 전달되었을 경우 */
		fprintf(stderr, "usage : file_check filename\n");
		exit(1);
	}
	
	if((fd = open(argv[1], O_RDONLY)) == -1){ /* 읽기 전용 모드 */
		perror("open");
		exit(1);
	}

	printf("File \"%s\" found... \n", argv[1]); /* 파일 열기 성공 */
	close(fd);
}
