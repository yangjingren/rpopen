/*
	rpserver: remote popen server
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <string.h>



void str_echo(int sockfd);

int main(int argc, char **argv)
{
	static char usage[] = "Usage: %s [-p port]\n";
	//Initialize port to 0 i.e. PPORT
	int port = 0;
	//Check for correct usage format
	if (argc == 3){
		if (strcmp(argv[1],"-p")==0){
			int intCheck;
			if (atoi(argv[2])!=0){
				port = atoi(argv[2]);
				printf("Port: %i\n",port);
			}
			else{
				fprintf(stderr, usage, argv[0]);
				exit(1);
			}

		}
		else{
			fprintf(stderr, usage, argv[0]);
			exit(1);
		}
	}
	else if (argc == 1)
		;
	else{
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

	int listenfd, connfd, ret;
	pid_t pid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	// Allows for socket reuse
	int on = 1;
	ret = setsockopt (listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

	//Set up connections on the given port from all interfaces
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl (INADDR_ANY);
	servaddr.sin_port = htons (port);

	//bind to the port
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	//listen for incoming connections
	int maxConn = 8;
	listen(listenfd, maxConn);

	while (1){
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

		if ((pid = fork())==0){
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}

void str_echo(int sockfd){
	ssize_t n;
	char line[8096];
	for (;;){
		if ((n=read(sockfd, line, 8096))==0)
			return;
		write(sockfd, line, n);
	}
}