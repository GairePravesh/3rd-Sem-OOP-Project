#include"Graphics.hpp"
void GUI::textEntry(RenderWindow &window,int x,int y,std::string &word)
{
    bool run=true;
    while(window.isOpen() && run)
    {
        Event event;
        while (window.pollEvent(event) && run)
        {
            if(event.type==Event::Closed)
                window.close();
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if(isAreaClicked(window,x,y))
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
                        drawBox(window,x-5,y);
                   }
                   if (event.text.unicode > 32 && event.text.unicode < 125 && word.size()<15)
                    {
                        word.push_back((char)event.text.unicode);
                    }
                   displayText(window,word,x,y);
                }
            }
         }
         window.display();
    }
}
void GUI::drawBox(RenderWindow &window,int setX,int setY,int width,int height)
{
    RectangleShape rect;
    rect.setSize(Vector2f(width,height));
    rect.setPosition(setX,setY);
    window.draw(rect);
}
void GUI::displayText(RenderWindow &window,std::string word,int x,int y,int s)
{
    Font font;
    if(!font.loadFromFile("font.ttf"))
    {
        window.close();
    }
    Text text;
    text.setFont(font);
    text.setColor(Color::Black);
    text.setCharacterSize(s);
    text.setString(word);
    text.setPosition(x,y);
    window.draw(text);
}
void GUI::createSprite(RenderWindow &window,Texture &texture,Sprite &sprite,std::string image,int x,int y)
{
    if(!texture.loadFromFile(image))
        {
            window.close();
        }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setColor(Color(240,240,240));
    sprite.setPosition(Vector2f(x, y));
    window.draw(sprite);
}
int GUI::isSpriteClicked(RenderWindow &window,Sprite &spr1,Sprite &spr2)
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
bool GUI::isAreaClicked(RenderWindow &window,int left,int top,int width,int height)
{
    Vector2i mousePosition = Mouse::getPosition(window);
    if(mousePosition.x > left && mousePosition.x < (left + width)
        && mousePosition.y > top && mousePosition.y < (top + height))
        return true;
    else
        return false;
}

