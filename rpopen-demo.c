/*
	Yang J. Ren
	demo program that uses rpopen
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define BSIZE 1024

FILE *rpopen(char *host, int port, char *cmd);

int main(int argc, char **argv)
{
	FILE *fp;
	char buf[BSIZE];

	if ((fp = rpopen(0, 0, "ls -1L /etc")) != 0) {
		/* read the output from the command */

		while (fgets(buf, BSIZE, fp) != 0)
			fputs(buf, stdout);
	}
	fclose(fp);
	exit(0);

}


