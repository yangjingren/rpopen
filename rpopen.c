/*
	rpopen: remote popen function
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <string.h>
FILE *
rpopen(char *host, int port, char *cmd)
{
	int sockfd;
struct sockaddr_in servaddr;
struct hostent *hostp;
int portt = 2000;
int hostname = "127.0.0.1";
sockfd = socket(AF_INET,SOCK_STREAM,0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(portt);
servaddr.sin_addr.s_addr =inet_addr(hostname);
//hostp= gethostbyname(hostname);
//memcpy(&serveraddr.sin_addr, hostp->h_addr,sizeof(serveraddr.sin_addr));

int ret;
if((ret=connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))!=0){
	printf("error\n");
}
char message[]="ls -1L /etc";
write(sockfd, message, strlen(message));
char line[8096];
FILE *fp;
fp = fdopen(sockfd,"r");

	return fp;
}
