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
int main(int argc,char *argv[])
{
int sockfd,newsockfd,portno;
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
newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
if(newsockfd<0)
{
cout<<"Error on accepting"<<endl;
}
cout<<"Connection made to "<<ntohs(cli_addr.sin_port)<<" from port "<<inet_ntoa(cli_addr.sin_addr)<<endl;
//send
send(newsockfd,"Hello world",13,0);
bzero(buffer,256);
n=read(newsockfd,buffer,255);
if(n<0)
{
cout<<"Error reading from socket"<<endl;
}
cout<<"The message is "<<buffer<<endl;
close(newsockfd);
close(sockfd);
return 0;
}
