#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>

class Utils
{
public:
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
void textEntry(RenderWindow &window,int x,int y,std::string &word)
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
void drawBox(RenderWindow &window,int setX,int setY,int width,int height=40)
{
    RectangleShape rect;
    rect.setSize(Vector2f(width,height));
    rect.setPosition(setX,setY);
    window.draw(rect);
}
bool isAreaClicked(RenderWindow &window,int left,int top,int width=300,int height=400)
{
    Vector2i mousePosition = Mouse::getPosition(window);
    if(mousePosition.x > left && mousePosition.x < (left + width)
        && mousePosition.y > top && mousePosition.y < (top + height))
        return true;
    else
        return false;
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
};
class App:public Utils
{
private:
RenderWindow &window;
std::string Username,Password,message;
public:
App(RenderWindow &w):window(w){}
void makeWindow(std::string title,int x,int y)
{
	RenderWindow window(VideoMode(x,y),title,Style::TitleBar|Style::Close);
	window.setPosition(Vector2i(600,200));
	window.setVertical()SyncEnabled(true);
	window.clear(Color(240,240,240));
}
void showHomepage()
{
	window.clear(Color(240,240,240));
	Texture texture;
	Sprite sprite;
	Utils::createSprite(window,texture,sprite,"client.png",130,255);
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
		        				(sprite.getGlobalBounds().right+sprite.getGlobalBounds().height))
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

void login()
{
	window.clear(Color(240,240,240));
    Texture Usertexture,Codetexture;
    Sprite Usersprite,Codesprite;
    Utils::createSprite(window,Logintexture,Loginsprtie,"User",50,300);
    drawBox(window,150,300);
    Utils::createSprite(window,Logintexture,Loginsprtie,"Password",50,400);
    Utils::drawBox(window,150,400);
    Utils::drawBox(window,350,450,100,45);
    Utils::displayText(window,"Submit",352,460);
    Utils::displayText(window,Username,155,300);
    Utils::displayText(window,Password,155,400);
    window.display();
    Event event;
    bool loop=false;
    while(!loop)
    {
    	while(window.pollEvent(event) && !loop)
    	{
	    	if(event.type==Event::Closed)
	    		window.close();
	        if (Mouse::isButtonPressed(Mouse::Left))
	        {
	            if(Utils::isAreaClicked(window,150,300))
	            {
	                Utils::textEntry(window,155,300,Username);
	            }
	            else if(Utils::isAreaClicked(window,150,400))
	            {
	                 Utils::textEntry(window,155,400,Password);
	            }
	            else if(Utils::isAreaClicked(window,350,450))
	            {
	               loop=checkLogin();
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
                    textEntry(window,message,15,555,580,40,43);
	            }
            }
		}
		window.display();
	}
}
};

int main(void)
{
	App app;
	app.makeWindow("Messenger",600,600);
	app.showHomepage();
	app.login();
	app.startChatWindow();
	
	
	return 0;
}
