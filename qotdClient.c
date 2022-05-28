 //QOTD Client code
#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 1769
#define MAX 8000
#define STAD struct sockaddr

//function for enable client to chat server
void func(int socket_desc)
{
	char buff[MAX];
	int a;
	bzero(buff,sizeof(buff));
	printf("Type 'i want'  to server to get Quote Of The Day : ");
	a = 0;
	if((buff[a++]= getchar())!= '\a')
	{
		write(socket_desc,buff,sizeof(buff));
		bzero(buff,sizeof(buff));
		read(socket_desc,buff,sizeof(buff));
		printf(" Server : %s" ,buff);
	}
}

int main(int argc,char *argv[])
{
	int socket_desc;
	struct sockaddr_in server;

	//create socket and let client know if socket is created or not
	socket_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1)
	{
		printf("\n Socket cannot be created\n");
	}
	else
		printf(" \n Successful ,socket created..\n");

	//assign server ip address and port
	server.sin_addr.s_addr=inet_addr("192.168.56.102"); //Server ip address
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);

	//connect client socket with the server socket
	if(connect(socket_desc, (struct sockaddr*)&server,sizeof(server))<0)
	{
		puts("\nConnection to server failed\n");
		return 1;
	}
	else
	puts("connection to server successsful");

	//function as for chat
	func(socket_desc);

	//close the socket
	close(socket_desc);
	
	//end the program
	return 0;
}


