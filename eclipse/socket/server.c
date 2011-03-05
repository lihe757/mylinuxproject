/*
 * server.c
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

int main(int argc, char **argv) {

	int server_sockfd,client_sockfd;
	int server_len, client_len;

	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	unlink("/tmp/server_socket");
	server_sockfd = socket(AF_UNIX,SOCK_STREAM,0);
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path,"/tmp/server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd,(struct sockaddr*)&server_address,server_len);

	listen(server_sockfd,5);
	while(1){
		char ch;

		printf("server waitting\n");

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

		read(client_sockfd,&ch,1);
		ch++;
		write(client_sockfd,&ch,1);
		close(client_sockfd);

	}
}

