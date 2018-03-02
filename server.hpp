#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace sf;
class Server:public GUI
{
private:
    std::string serverIP;
    std::string serverPort;
    bool run=true;
public:
     void serverHome(RenderWindow &window)
    {
        window.setTitle("Messenger : Server");
        GUI::displayText(window,"IP Address",50,100);
        GUI::drawBox(window,50,150);
        GUI::displayText(window,"Port No",50,250);
        GUI::drawBox(window,50,300);
        GUI::drawBox(window,130,355,100,45);
        GUI::displayText(window,"Host",145,365);
        GUI::displayText(window,serverIP,55,160);
        GUI::displayText(window,serverPort,55,310);
        window.display();
        Event event;
        while(window.isOpen() && run)
        {
        	while(window.pollEvent(event) && run)
        	{
		    	if(event.type==Event::Closed)
		    		exit(0);//window.close();
		        if (Mouse::isButtonPressed(Mouse::Left))
		        {
		            if(GUI::isAreaClicked(window,50,150))
		            {
		                GUI::textEntry(window,55,160,serverIP);
		            }
		            else if(GUI::isAreaClicked(window,50,300))
		            {
		                GUI::textEntry(window,55,310,serverPort);
		            }
		            else if(GUI::isAreaClicked(window,130,355))
		            {
		                run=false;
		            }
		        }
		    }    
        }
        run=true;
    }
     bool loginResult()
     {
     	if (serverIP=="default")
     		return true;
     	else
     		return false;
     }

};
