/*
	demo program that uses rpopen
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <string.h>

#define BSIZE 1024

FILE *rpopen(char *host, int port, char *cmd);

main(int argc, char **argv)
{
	FILE *fp;
	char buf[BSIZE];

	if ((fp = rpopen(0, 0, "ls -lL /etc")) != 0) {
		/* read the output from the command */

		while (fgets(buf, BSIZE, fp) != 0)
			fputs(buf, stdout);
	}
	fclose(fp);
}

#include <stdio.h> 

