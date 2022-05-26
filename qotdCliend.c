#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>

int main(int argc,char *argv[]))
{	
	int sock_desc;
	struct sockaddr_in server;

	//create socket and let client know if socket is created or not
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	if(socket_desc == -1)
	{
		printf(" Socket cannot be created");
	}
	else
		printf("  Successful,Socket created");
	
	//assign server ip address and port
	server.sin_addr.s_addr=inet_addr("192.168.56.103"); //Server ip address
	server.sin_family=AF_INET;
	server.sin_port=htons(PORT);

	//connect client socket with server socket
	if(connect(socket_desc, (struct sockaddr*)&server,sizeof(server))<0)
	{
		puts("connection to server failed");
		return 1;
	}
	else
	puts("connection to server successsful");
	return 0;
}	
