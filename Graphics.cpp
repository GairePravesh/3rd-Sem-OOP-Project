#include"Graphics.hpp"
void GUI::textEntry(int x,int y,std::string &word)
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
                    //displayText(word,x,y);
                }
                else
                    run=false;
            }
            if(Event::TextEntered)
            {
                if (event.type == Event::TextEntered)
                {
                   if(event.text.unicode== 8 && word.size()>0)
                   {
                        word.pop_back();
                        drawBox(x-5,y);
                   }
                   if (event.text.unicode > 32 && event.text.unicode < 125 && word.size()<15)
                    {
                        word.push_back((char)event.text.unicode);
                    }
                   displayText(word,x,y);
                }
            }
         }
         window.display();
    }
}
void GUI::drawBox(int setX,int setY,int width,int height)
{
    RectangleShape rect;
    rect.setSize(Vector2f(width,height));
    rect.setPosition(setX,setY);
    window.draw(rect);
}
void GUI::displayText(std::string word,int x,int y,int s)
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
void GUI::createSprite(Texture &texture,Sprite &sprite,std::string image,int x,int y)
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
int GUI::isSpriteClicked(Sprite &spr1,Sprite &spr2)
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
void GUI::serverHome()
{
    window.setTitle("Messenger : Server");
    displayText("IP Address",50,100);
    drawBox(50,150);
    displayText("Port No",50,250);
    drawBox(50,300);
    drawBox(130,355,100,45);
    displayText("Host",145,365);
    displayText(serverIP,55,160);
    displayText(serverPort,55,310);
    window.display();
    while(true)
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if(isAreaClicked(50,150))
            {
                textEntry(55,160,serverIP);
            }
            else if(isAreaClicked(50,300))
            {
                textEntry(55,310,serverPort);
            }
            else if(isAreaClicked(130,355))
            {
                break;
            }
        }
    }
}
void GUI::clientHome()
{
    window.setTitle("Messenger : Client");
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
    displayText(IP_address,155,100);
    displayText(Port_no,155,200);
    displayText(Username,155,300);
    displayText(Password,155,400);
    window.display();
    while(true)
    {
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if(isAreaClicked(150,100))
            {
                textEntry(155,100,IP_address);
            }
            else if(isAreaClicked(150,200))
            {
                 textEntry(155,200,Port_no);
            }
            else if(isAreaClicked(150,300))
            {
                textEntry(155,300,Username);
            }
            else if(isAreaClicked(150,400))
            {
                 textEntry(155,400,Password);
            }
            else if(isAreaClicked(350,450))
            {
               break;
            }
        }
    }
}
bool GUI::isAreaClicked(int left,int top,int width,int height)
{
    Vector2i mousePosition = Mouse::getPosition(window);
    if(mousePosition.x > left && mousePosition.x < (left + width)
        && mousePosition.y > top && mousePosition.y < (top + height))
        return true;
    else
        return false;
}
bool GUI::loginResult()
{
    return true;
}
void GUI::closeWindow()
{
    window.close();
}
