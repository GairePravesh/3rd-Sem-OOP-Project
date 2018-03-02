#include<SFML/Graphics.hpp>
#include"Graphics.hpp"
#include"exception.hpp"
#include<string>
#include<iostream>
using namespace sf;
int main()
{
    int flag;
    bool loop=true;
    RenderWindow home(VideoMode(500, 500), "Messenger",Style::Titlebar | Style::Close);
    RenderWindow popup(VideoMode(200, 200), "Messenger",Style::Titlebar | Style::Close);
    GUI app;
    Exception dialog;
    //app.initWindow(home,600,200,"Messenger : ");
    home.setPosition(Vector2i(600, 200));
    home.setVerticalSyncEnabled(true);
    home.clear(Color(240,240,240));
    Texture servertexture,clienttexture;
    Sprite serversprite,clientsprite;
    app.createSprite(home,servertexture,serversprite,"server",125,10);
    app.createSprite(home,clienttexture,clientsprite,"client",130,255);
    home.draw(serversprite);
    home.draw(clientsprite);
    Event event;
    while (home.isOpen() && loop)
    {
        while (home.pollEvent(event) && loop)
        {
            if (event.type == Event::Closed)
                app.closeWindow(home);
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                flag=app.isSpriteClicked(home,serversprite,clientsprite);
                if(flag==1 || flag==2)
                {
                    home.clear(Color(240,240,240));
                    loop=false;
                }
            }
       }
       home.display();
    }
    switch (flag)
    {
        case 1:
            {
                #include"server.hpp"
                Server server;
                server.serverHome(home);
                if(server.loginResult())
                {
                    // messenger

                }
                else
                {
                    //exception
                    app.closeWindow(home);
                }
                break;
            }
        case 2:
            {
                #include"client.hpp"
                Client client;
                client.clientHome(home);
                if(client.loginResult())
                {
                    //messenger
                }
                else
                {
                    //exception
                    app.closeWindow(home);
                }
                break;
            }
    }
    return 0;
}
