/* file_creat.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
	
	int fd; /* 파일 디스크립터 변수 선언 */
	char *buf = "This is file creation program.\n"; /* 파일에 쓸 내용 */
	ssize_t cnt;
	int flags = O_WRONLY | O_CREAT | O_TRUNC; /* (쓰기 전용, 파일이 없으면 생성, 파일이 있으면 내용 삭제) */
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; /* (소유자에 대해 읽기 및 쓰기 권한, 그룹 및 기타에 대해 읽기 권한) */

	if(argc < 2) {
		fprintf(stderr, "Usage : file_creat filename\n");
		exit(1);
	}
	/* 파일 열기 */
	if((fd = open(argv[1], flags, mode)) == -1) {
		perror("open");
		exit(1);
	}
	/* 파일에 내용 쓰기 */
	cnt = write(fd, buf, strlen(buf));
	printf("write count = %ld\n", cnt);
	close(fd);
}
