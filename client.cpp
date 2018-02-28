/*
Pravesh Gaire
Not the way we are going to implement.
Just checking and learning things
*/

#include<iostream>
#include<cstdlib>
#include<unistd.h>
// part of unix, stands for unix standard header
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
//#include<arpa/inet.h>
#include<errno.h>
//#include<netdb.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main(int argc,char *argv[])
{
int sockfd,portno,n;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffer[256];
if(argc<3)
{
cout<<"error input of ip or port"<<endl;
exit(0);
}
portno=atoi(argv[2]);
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
cout<<"Error opening socket"<<endl;
}
server=gethostbyname(argv[1]);
if(server==NULL)
{
cout<<"no such host"<<endl;
exit(0);
}
bzero((char *)&serv_addr,sizeof(serv_addr));
serv_addr.sin_family=AF_INET;
bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
serv_addr.sin_port=htons(portno);
if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
{
cout<<"ERROR connecting"<<endl;
}
bzero(buffer,256);
cout<<"Write something to say"<<endl;
fgets(buffer,255,stdin);
n=write(sockfd,buffer,strlen(buffer));
if(n<0)
{
cout<<"Error writing to socket"<<endl;
}
bzero(buffer,256);
n=read(sockfd,buffer,255);
if(n<0)
{
cout<<"Error readingg from socket"<<endl;
}
cout<<"Server said "<<buffer<<endl;
close(sockfd);
return 0;
}
