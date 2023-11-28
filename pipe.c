/* pipe.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 256

int main() {

	char buf[BUF_SIZE];
	int p[2], i;
	int pid;

	/* open pipe */
	if (pipe(p) == -1) {
		perror ("pipe call failed");
		exit(1);
	}

	pid = fork();

	/* child process */
	if (pid == 0) {
		close(p[0]);
		/* write to pipe */
		for (i = 0; i < 2; i++) {
			sprintf(buf, "Hello, Pipe Program #%d",i+1);
			write(p[1], buf, BUF_SIZE);
		}
	}

	else if (pid > 0) {
		close(p[1]);

		/* read from pipe */
		for (i = 0; i < 2; i++) {
			read (p[0], buf, BUF_SIZE);
			printf ("%s\n", buf);
		}
	}

	else	perror ("fork failed");
}
