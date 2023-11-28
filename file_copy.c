/* file_copy.c */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define MAX_READ 10

int main(int argc, char *argv[]) {

        int src_fd;
	int dst_fd;
        char buf[MAX_READ];
        ssize_t rcnt;
	ssize_t tot_cnt = 0;
        mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	if(argc < 3) { /* 첫 번째 파일의 내용을 두 번째 파일로 복사 */
		fprintf(stderr, "Usage : file_copy source file destination_file\n");
		exit(1);
	}
	
	/* 소스 파일 열기 */
        if((src_fd = open(argv[1], O_RDONLY)) == -1) {
		perror("fopen : src");
		exit(1);
	}

	/* 대상 파일 생성 또는 열기 */
	if((dst_fd = creat(argv[2], mode)) == -1) {
		perror("fopen : dst");
		exit(1);
	}
	
	/* 파일 복사 */
	while((rcnt = read(src_fd, buf, MAX_READ) > 0)) {
		tot_cnt += write(dst_fd, buf, rcnt);
	}

	if(rcnt < 0) {
		perror("read");
		exit(1);
	}
	printf("total write count = %ld\n", tot_cnt);
	
	close(src_fd);
        close(dst_fd);
}
