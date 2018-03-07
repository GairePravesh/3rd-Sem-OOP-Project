#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>
using namespace sf;
class Utils
{
public:
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
                        displayText(window,word,x,y);
                   }
                   else if(event.text.unicode==32 && word.size()>0)
                   {
                        word+=" ";
                   }
                   else if (event.text.unicode > 32 && event.text.unicode < 125 && word.size()<limit)
                    {
                        word.push_back((char)event.text.unicode);
                        displayText(window,word,x,y);
                    }
                    else if(event.text.unicode==13 && word.size()>0 && limit==31)
                    {

                        displayText(window,"Pravesh",10,15+line*30);
                        if(line<17)
                        {
                            drawBox(window,x-5,y-5,w,h);
                            displayText(window,word,150,15+line*30);
                            word="";
                            line+=1;
                        }
                        else
                        {
                            line=0;
                            drawBox(window,x-5,y-5,w,h);
                            drawBox(window,10,10,580,530);
                            displayText(window,word,150,15+line*30);
                            word="";
                            line++;

                        }
                    }
                }
            }
         }
         window.display();
    }
}

};
class App:public Utils
{
private:
RenderWindow &window;
std::string Username,Password,message;
public:
App(RenderWindow &w):window(w){}

void makeWindow()
{
	window.setPosition(Vector2i(600,200));
	window.setVerticalSyncEnabled(true);
	window.clear(Color(240,240,240));
}
void showHomepage()
{
	window.clear(Color(240,240,240));
	Texture texture;
	Sprite sprite;
	Utils::createSprite(window,texture,sprite,"client",175,200);
	Event event;
	bool run=true;
	while(run)
	{
		while (window.pollEvent(event) && run)
		{
		    if (event.type == Event::Closed)
		        window.close();
		    if (Mouse::isButtonPressed(Mouse::Left))
		    {
		        if(Utils::isAreaClicked(window,sprite.getGlobalBounds().left,sprite.getGlobalBounds().top,
		        				(sprite.getGlobalBounds().left+sprite.getGlobalBounds().width),
		        				(sprite.getGlobalBounds().top+sprite.getGlobalBounds().height)))
		        {
		            run=false;
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

void login( )
{
    window.clear(Color(240,240,240));
    Texture Usertexture,Codetexture;
    Sprite Usersprite,Codesprite;
    Utils::createSprite(window,Usertexture,Usersprite,"User",50,150);
    Utils::drawBox(window,150,150,300,40);
    Utils::createSprite(window,Codetexture,Codesprite,"Password",50,350);
    Utils::drawBox(window,150,350,300,40);
    Utils::drawBox(window,350,450,100,45);
    Utils::displayText(window,"Submit",352,460);
    Utils::displayText(window,Username,155,300);
    Utils::displayText(window,Password,155,400);
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
	            if(Utils::isAreaClicked(window,150,150))
	            {
                    Utils::textEntry(window,Username,155,155);
	            }
	            else if(Utils::isAreaClicked(window,150,350))
	            {
                     Utils::textEntry(window,Password,155,355);
	            }
	            else if(Utils::isAreaClicked(window,350,450,100,45))
	            {
                    loop=false;
	            }
	        }
    	}
    }
}
void startChatWindow()
{
	window.clear(Color(240,240,240));
    window.clear(Color(150,150,150));
	bool run=true;
    Utils::drawBox(window,10,550,580,40);
    Utils::drawBox(window,10,10,580,530);
	Event event;
	while(window.isOpen() && run)
	{
		while(window.pollEvent(event)&&run)
		{
			if (event.type == Event::Closed)
		        window.close();
            if (Mouse::isButtonPressed(Mouse::Left))
	        {
	            if(Utils::isAreaClicked(window,10,550,580,40))
	            {
                    Utils::textEntry(window,message,15,555,580,40,31);
	            }
            }
		}
		window.display();
	}
}
};

int main(void)
{
    RenderWindow window(VideoMode(600,600),"Messenger");
	App app(window);
	app.makeWindow();
	app.showHomepage();
	app.login();
	app.startChatWindow();
	return 0;
}























