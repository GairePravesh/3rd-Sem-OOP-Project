#include"Graphics.hpp"
//#include"exception.hpp"
int main()
{
    int flag;
    bool loop=true;
    RenderWindow home(VideoMode(500, 500), "Messenger",Style::Titlebar | Style::Close);
    GUI app(home);
    home.setPosition(Vector2i(600, 200));
    home.setVerticalSyncEnabled(true);
    home.clear(Color(240,240,240));
    Texture servertexture,clienttexture;
    Sprite serversprite,clientsprite;
    app.createSprite(servertexture,serversprite,"server",125,10);
    app.createSprite(clienttexture,clientsprite,"client",130,255);
    home.draw(serversprite);
    home.draw(clientsprite);
    Event event;
    while (home.isOpen() && loop)
    {
        while (home.pollEvent(event) && loop)
        {
            if (event.type == Event::Closed)
                app.closeWindow();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                flag=app.isSpriteClicked(serversprite,clientsprite);
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
            app.serverHome();
            if(app.loginResult())
            {
                // messenger
            }
            break;
        case 2:
            app.clientHome();
            if(app.loginResult())
            {
                //messenger
            }
            break;
    }
    return 0;
}
