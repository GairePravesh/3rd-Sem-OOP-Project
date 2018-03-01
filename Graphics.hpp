#include<SFML/Graphics.hpp>
#include<string>
using namespace sf;
class GUI
{
private:
    RenderWindow &window;
    std::string String;
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
                String="Server";
                serverGUI();
            }
            if(flag==2)
            {
               // std::cout<<"client"<<std::endl;
                String="Client";
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
        /*drawText("Login",30,0,0);
        drawText("IP Address",20,0,100);
        drawBox(150,100);
        drawText("Port No",20,0,200);
        drawBox(150,200);
        drawText("Username",20,0,300);
        drawBox(150,300);
        drawText("Password",20,0,400);
        drawBox(150,400);*/
        Texture IPtexture,Porttexture,Usertexture,Codetexture;
        Sprite IPsprite,Portsprite,Usersprite,Codesprite;
        if(!IPtexture.loadFromFile("IP.png") || !Porttexture.loadFromFile("Port.png") || !Usertexture.loadFromFile("User.png") || Codetexture.loadFromFile("Password.png"))
        {
            closeWindow();
        }
        IPtexture.setSmooth(true);
        Porttexture.setSmooth(true);
        Usertexture.setSmooth(true);
        Codetexture.setSmooth(true);
        IPsprite.setTexture(IPtexture);
        Portsprite.setTexture(Porttexture);
        Usersprite.setTexture(Usertexture);
        Codesprite.setTexture(Codetexture);
        IPsprite.setColor(Color(240,240,240));
        Portsprite.setColor(Color(240,240,240));
        Usersprite.setColor(Color(240,240,240));
        Codesprite.setColor(Color(240,240,240));
        IPsprite.setColor(Color(240,240,240));
        Portsprite.setColor(Color(240,240,240));
        Usersprite.setColor(Color(240,240,240));
        Codesprite.setColor(Color(240,240,240));
        window.draw(IPsprite);
        window.draw(Portsprite);
        window.draw(Usersprite);
        window.draw(Codesprite);
        /*if (Mouse::isButtonPressed(Mouse::Left))
        {
            //std::cout<<"mouse clicked"<<std::endl;
            int flag=isSpriteClicked(IPsprite,Portsprite,Usersprite,Codesprite);
            if(flag==1)
            {
                String="IPsprite";
            }
            if(flag==2)
            {
                String="Portsprite";
            }
            if(flag==3)
            {
                String="Usersprite";
            }
            if(flag==4)
            {
                String="Codesprite";
            }
        }*/

    }/*
    void drawText(std::string write,int s,int xpos,int ypos)
    {
        Font font;
        if(!font.loadFromFile("font.ttf"))
        {
            //error handler
            closeWindow();
        }
        Text text;
        text.setFont(font);
        text.setColor(Color::Black);
        text.setCharacterSize(s);
        text.move(xpos,ypos);
        text.setString(write);
        window.draw(text);
    }
    void drawBox(int setX,int setY,int width=300,int height=40)
    {
            RectangleShape rect;
            rect.setSize(Vector2f(width,height));
            rect.setPosition(setX,setY);
            window.draw(rect);
    }*/
};

