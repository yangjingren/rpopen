/*
	Yang J. Ren
	rpopen: remote popen function
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <string.h>
FILE *rpopen(char *host, int port, char *cmd){
	int sockfd;
	int retVal;
	struct sockaddr_in servaddr;

	if(port == 0){
		char* envPort;
		envPort = getenv("PPORT");
		if (envPort == NULL){
			fprintf(stderr, "PPORT has not been set.\n");
			exit(1);
		}
		else{
			port = atoi(envPort);
		}
	}
	if (host == NULL || host ==""){
		char* envHost;
		envHost = getenv("PHOST");
		if (envHost == NULL){
			fprintf(stderr, "PHOST has not been set.\n");
			exit(1);
		}
		else{
			host = envHost;
		}
	}
	//inet_pton can't process localhost 
	if (strcasecmp(host,"localhost")==0){
				host = "127.0.0.1";
	}
	printf("Port: %i\n", port);
	printf("Host: %s\n", host); 

	//open socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);
	//find hostname
	if(inet_pton(AF_INET, host, &servaddr.sin_addr)<=0){
		fprintf(stderr, "Inet_pton error for %s.\n", host);
		exit(1);
	}

	//open connection to host
	if((retVal=connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)))!=0){
		fprintf(stderr,"Connect error.\n");
	}

	//write command to socket file descriptor
	write(sockfd, cmd, strlen(cmd));

	//convert socket file descriptor to file pointer
	FILE *fp;
	fp = fdopen(sockfd,"r");

	return fp;
}
