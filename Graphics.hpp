#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace sf;
class GUI
{
private:
    RenderWindow &window;
    std::string hostType;
    int setX=600,setY=200;

public:
    GUI(RenderWindow &w):window(w){}
    void run()
    {
        window.setPosition(Vector2i(setX, setY));
        window.setVerticalSyncEnabled(true);//activate vertical synchronization
        // clear the window with black color
        window.clear(Color(240,240,240));
        // run the program as long as the window is open
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == Event::Closed)
                    closeWindow();
                Home();
                window.display();
            }
        }

    }
    void Home()
    {
        Texture servertexture,clienttexture;
        Sprite serversprite,clientsprite;
        if(!servertexture.loadFromFile("server.png"))
        {
            closeWindow();
        }
        if(!clienttexture.loadFromFile("client.png"))
        {
            closeWindow();
        }
        servertexture.setSmooth(true);
        clienttexture.setSmooth(true);
        serversprite.setTexture(servertexture);
        clientsprite.setTexture(clienttexture);
        serversprite.setColor(Color(240,240,240));
        clientsprite.setColor(Color(240,240,240));
        serversprite.setPosition(Vector2f(125, 10));
        clientsprite.setPosition(Vector2f(130, 255));
        window.draw(serversprite);
        window.draw(clientsprite);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            //std::cout<<"mouse clicked"<<std::endl;
            int flag=isSpriteClicked(serversprite,clientsprite);
            if(flag==1)
            {
                //std::cout<<"server"<<std::endl;
                hostType="Server";
                serverGUI();
            }
            if(flag==2)
            {
               // std::cout<<"client"<<std::endl;
                hostType="Client";
                clientGUI();
            }
        }

    }
    int isSpriteClicked(Sprite &spr1,Sprite &spr2)
    {
        Vector2i mousePosition = Mouse::getPosition(window);
        if(mousePosition.x > spr1.getGlobalBounds().left && mousePosition.x < (spr1.getGlobalBounds().left + spr1.getGlobalBounds().width)
            && mousePosition.y > spr1.getGlobalBounds().top && mousePosition.y < (spr1.getGlobalBounds().top + spr1.getGlobalBounds().height))
        {
            return 1;
        }
        if(mousePosition.x > spr2.getGlobalBounds().left && mousePosition.x < (spr2.getGlobalBounds().left + spr2.getGlobalBounds().width)
            && mousePosition.y > spr2.getGlobalBounds().top && mousePosition.y < (spr2.getGlobalBounds().top + spr2.getGlobalBounds().height))
        {
            return 2;
        }
        return 0;
    }
    void closeWindow()
    {

        window.close();
    }
    void serverGUI()
    {
        window.clear(Color(240,240,240));
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == Event::Closed)
                    closeWindow();
                serverHome();
                window.display();
            }
        }
    }
    void clientGUI()
    {
        window.clear(Color(240,240,240));
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == Event::Closed)
                    closeWindow();
                clientHome();
                window.display();
            }
        }
    }
    void serverHome()
    {
    }
    void clientHome()
    {
    }
};

