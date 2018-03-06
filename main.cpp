#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
using namespace sf;
bool isAreaClicked(RenderWindow &window,int left,int top,int width=300,int height=40)
{
    Vector2i mousePosition = Mouse::getPosition(window);
    if(mousePosition.x > left && mousePosition.x < (left + width)
        && mousePosition.y > top && mousePosition.y < (top + height))
        return true;
    else
        return false;
}
void createSprite(RenderWindow &window,Texture &texture,Sprite &sprite,std::string image,int x,int y)
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
void drawBox(RenderWindow &window,int setX,int setY,int width,int height)
{
    RectangleShape rect;
    rect.setSize(Vector2f(width,height));
    rect.setPosition(setX,setY);
    window.draw(rect);
}

void displayText(RenderWindow &window,std::string word,int x,int y,int s=20)
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
void textEntry(RenderWindow &window,std::string &word,int x,int y,int w=300,int h=40,int limit=16)
{
    bool run=true;
    static int line=0;
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
                        drawBox(window,x-5,y-5,w,h);
                   }
                   else if(event.text.unicode==32 && word.size()>0)
                   {
                        word+=" ";
                   }
                   else if (event.text.unicode > 32 && event.text.unicode < 125 && word.size()<limit)
                    {
                        word.push_back((char)event.text.unicode);
                    }
                    else if(event.text.unicode==13 && word.size()>0)
                    {
                        if(line<30)
                        {
                            displayText(window,word,15,15+line*20,15);
                            word="";
                            drawBox(window,x-5,y-5,w,h);
                            line+=2;
                        }
                    }
                   displayText(window,word,x,y);
                }
            }
         }
         window.display();
    }
}

bool checkLogin()
{
	return true;
}
void login(RenderWindow &window)
{
    window.clear(Color(240,240,240));
	std::string Username,Password;
    Texture Usertexture,Codetexture;
    Sprite Usersprite,Codesprite;
    createSprite(window,Usertexture,Usersprite,"User",50,150);
    drawBox(window,150,150,300,40);
    createSprite(window,Codetexture,Codesprite,"Password",50,350);
    drawBox(window,150,350,300,40);
    drawBox(window,350,450,100,45);
    displayText(window,"Submit",352,460);
    displayText(window,Username,155,300);
    displayText(window,Password,155,400);
    window.display();
    Event event;
    bool loop=true;
    while(window.isOpen() && loop)
    {
    	while(window.pollEvent(event) && loop)
    	{
	    	if(event.type==Event::Closed)
	    		window.close();
	        if (Mouse::isButtonPressed(Mouse::Left))
	        {
	            if(isAreaClicked(window,150,150))
	            {
                    textEntry(window,Username,155,155);
	            }
	            else if(isAreaClicked(window,150,350))
	            {
                     textEntry(window,Password,155,355);
	            }
	            else if(isAreaClicked(window,350,450,100,45))
	            {
                    loop=false;
	            }
	        }
    	}
    }
}

void messageHandler(RenderWindow &window)
{
    std::string message;
    window.clear(Color(150,150,150));
	bool run=true;
    drawBox(window,10,550,580,40);
    drawBox(window,10,10,580,530);
	Event event;
	while(window.isOpen() && run)
	{
		while(window.pollEvent(event)&&run)
		{
			if (event.type == Event::Closed)
		        window.close();
            if (Mouse::isButtonPressed(Mouse::Left))
	        {
	            if(isAreaClicked(window,10,550,580,40))
	            {
                    textEntry(window,message,15,555,580,40,33);
	            }
            }
		}
		window.display();
	}
}
int main()
{
	RenderWindow window(VideoMode(600,600),"Messenger");
	window.setPosition(Vector2i(600,200));
	window.setVerticalSyncEnabled(true);
	Texture texture;
	Sprite sprite;
	window.clear(Color(240,240,240));
	createSprite(window,texture,sprite,"client",175,200);
	Event event;
	bool run=true;
	while(window.isOpen() && run)
	{
        window.display();
		while (window.pollEvent(event) && run)
		{
		    if (event.type == Event::Closed)
		        window.close();
		    if (Mouse::isButtonPressed(Mouse::Left))
		    {
		        if(isAreaClicked(window,sprite.getGlobalBounds().left,sprite.getGlobalBounds().top,(sprite.getGlobalBounds().left+sprite.getGlobalBounds().width),(sprite.getGlobalBounds().top+sprite.getGlobalBounds().height)))
		        {
		            run=false;
		        }
		    }
		}
	}
    login(window);
    messageHandler(window);
	return 0;
}
























