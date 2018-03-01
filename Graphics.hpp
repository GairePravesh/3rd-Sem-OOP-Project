#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace sf;
class GUI
{
private:
    RenderWindow &window;
    std::string String;
    std::string IP_address;
    std::string Port_no;
    std::string Username;
    std::string Password;
    std::string serverIP;
    std::string serverPort;
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
           }
           window.display();
        }
        std::cout<<String<<std::endl<<IP_address<<std::endl<<Port_no<<std::endl<<Username<<std::endl<<Password;
    }
    void createSprite(Texture &texture,Sprite &sprite,std::string image,int x,int y)
    {
        if(!texture.loadFromFile(image))
            {
                closeWindow();
            }
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setColor(Color(240,240,240));
        sprite.setPosition(Vector2f(x, y));
        window.draw(sprite);
    }
    void Home()
    {
        Texture servertexture,clienttexture;
        Sprite serversprite,clientsprite;
        createSprite(servertexture,serversprite,"server",125,10);
        createSprite(clienttexture,clientsprite,"client",130,255);
        window.draw(serversprite);
        window.draw(clientsprite);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            int flag=isSpriteClicked(serversprite,clientsprite);
            if(flag==1)
            {
                serverGUI();
            }
            if(flag==2)
            {
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
            }
            window.display();
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
            }
            window.display();
        }
    }
    void serverHome()
    {
        displayText("IP Address",50,100);
        drawBox(50,150);
        displayText("Port No",50,250);
        drawBox(50,300);
        drawBox(130,355,100,45);
        displayText("Host",145,365);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if(isAreaClicked(50,150))
            {
                displayText(serverIP,55,160);
                textEntry(55,160,serverIP);
            }
            else if(isAreaClicked(50,300))
            {
                displayText(serverPort,55,310);
                textEntry(55,310,serverPort);
            }
            else if(isAreaClicked(130,355))
            {

                closeWindow();
            }
        }
    }
    void clientHome()
    {
        Texture Logintexture,IPtexture,Porttexture,Usertexture,Codetexture;
        Sprite Loginsprtie,IPsprite,Portsprite,Usersprite,Codesprite;
        createSprite(Logintexture,Loginsprtie,"login",50,10);
        displayText("Login Credentials",150,10,30);
        createSprite(Logintexture,Loginsprtie,"IP",50,100);
        drawBox(150,100);
        createSprite(Logintexture,Loginsprtie,"Port",50,200);
        drawBox(150,200);
        createSprite(Logintexture,Loginsprtie,"User",50,300);
        drawBox(150,300);
        createSprite(Logintexture,Loginsprtie,"Password",50,400);
        drawBox(150,400);
        drawBox(350,450,100,45);
        displayText("Submit",352,460);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if(isAreaClicked(150,100))
            {
                displayText(IP_address,155,100);
                textEntry(155,100,IP_address);
            }
            else if(isAreaClicked(150,200))
            {
                 displayText(Port_no,155,200);
                 textEntry(155,200,Port_no);
            }
            else if(isAreaClicked(150,300))
            {
                displayText(Username,155,300);
                textEntry(155,300,Username);
            }
            else if(isAreaClicked(150,400))
            {
                 displayText(Password,155,400);
                 textEntry(155,400,Password);
            }
            else if(isAreaClicked(350,450))
            {
               loginResult();
            }
        }
    }
    void textEntry(int x,int y,std::string &word)
    {
        bool run=true;
        while(window.isOpen() && run)
        {
            Event event;
            while (window.pollEvent(event) && run)
            {
                if(event.type==Event::Closed)
                    closeWindow();
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if(isAreaClicked(x,y))
                    {
                        run=true;
                        displayText(word,x,y);
                    }
                    else
                        run=false;
                }
                if(Event::TextEntered)
                {
                    if (event.type == Event::TextEntered)
                    {
                       if (event.text.unicode < 128 && word.size()<16)
                        {
                            word.push_back((char)event.text.unicode);
                            displayText(word,x,y);
                        }
                    }
                }
             }
             window.display();
        }
    }
    void displayText(std::string word,int x,int y,int s=20)
    {
        Font font;
        if(!font.loadFromFile("font.ttf"))
        {
            closeWindow();
        }
        Text text;
        text.setFont(font);
        text.setColor(Color::Black);
        text.setCharacterSize(s);
        text.setString(word);
        text.setPosition(x,y);
        window.draw(text);
    }
    void drawBox(int setX,int setY,int width=300,int height=40)
    {
            RectangleShape rect;
            rect.setSize(Vector2f(width,height));
            rect.setPosition(setX,setY);
            window.draw(rect);
    }
    bool isAreaClicked(int left,int top,int width=300,int height=40)
    {
        Vector2i mousePosition = Mouse::getPosition(window);
        if(mousePosition.x > left && mousePosition.x < (left + width)
            && mousePosition.y > top && mousePosition.y < (top + height))
            return true;
        else
            return false;
    }
    void loginResult()
    {
        // check if login username and password matches to database
       // if(Username=="Pravesh Gaire" && Password=="12345")
        //{
            closeWindow();
        //}
    }
    void messageGUI()
    {
        window.clear(Color(240,240,240));

    }
};

