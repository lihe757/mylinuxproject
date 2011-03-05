/*
 * client.c
 *
 *  Created on: 2011-2-12
 *      Author: lihex
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int sockfd;
	int len;
	struct sockaddr_un address;
	int result;
	char ch = 'A';

	sockfd = socket(AF_UNIX,SOCK_STREAM,0);
	address.sun_family = AF_UNIX;
	strcpy(address.sun_path,"/tmp/server_socket");
	len = sizeof(address);

	result = connect(sockfd,(struct sockaddr *)&address,len);
	if(result == -1)
	{
		perror("ops: client1");
		exit(1);
	}

	write(sockfd,&ch,1);
	read(sockfd,&ch,1);
	printf("char form server is %c \n",ch);
	close(sockfd);
	exit(0);

}
