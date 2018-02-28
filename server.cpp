/*
Pravesh Gaire
Not the way we are going to implement.
Just checking and learning things
*/
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
// provides access to POSIX OS API
// size_t
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netdb.h>
#include<sys/wait.h>
#include<signal.h>
using namespace std;
void doNew(int sock)
{
int n;
char buffer[256];
bzero(buffer,256);
n=read(sock,buffer,255);
n=write(sock,"Got message",11);
cout<<"client said "<<buffer<<endl;
}
int main(int argc,char *argv[])
{
int sockfd,newsockfd,portno,pid;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr,cli_addr;
int n;
if (argc<2)
{
cout<<"No port provided"<<endl;
exit(1);
}
// create a socket
sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0)
{
cout<<"Error opening socket"<<endl;
}
//clear address strucutre
bzero((char*)&serv_addr,sizeof(serv_addr));
portno=atoi(argv[1]);
//setup host_addr structure for use in bind call
//server byte order
serv_addr.sin_family=AF_INET;
//host ip address
serv_addr.sin_addr.s_addr=INADDR_ANY;
//convert short int value for port must be
//converted into network byte order
serv_addr.sin_port=htons(portno);
if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
{
cout<<"Error on binding"<<endl;
}
//listen with max 5 in queue
listen(sockfd,5);
//accept for incomming request
clilen=sizeof(cli_addr);
while(1)
{
newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);

if(newsockfd<0)
{
cout<<"Error on accepting"<<endl;
}
pid=fork();
if(pid<0)
cout<<"Error on creating new"<<endl;
else if(pid==0)
{
close(sockfd);
doNew(newsockfd);
exit(0);
}
else 
close(newsockfd);
}
return 0;
}
