#include"server.hpp"

int main(void)
{
	Server server;
	server.initSocket();
	server.createSocket();
	server.listenSocket();
	for(;;) 
	{
		server.runServer();    
	}
}
    
    
  
