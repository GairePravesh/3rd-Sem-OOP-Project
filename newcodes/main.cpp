#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>
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
bool checkLogin()
{
	return true;
}
void login(RenderWindow &window)
{
	std::string Username,Password
    Texture Usertexture,Codetexture;
    Sprite Usersprite,Codesprite;
    createSprite(window,Logintexture,Loginsprtie,"User",50,300);
    drawBox(window,150,300);
    createSprite(window,Logintexture,Loginsprtie,"Password",50,400);
    drawBox(window,150,400);
    drawBox(window,350,450,100,45);
    displayText(window,"Submit",352,460);
    displayText(window,Username,155,300);
    displayText(window,Password,155,400);
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
	            if(isAreaClicked(window,150,300))
	            {
	                textEntry(window,155,300,Username);
	            }
	            else if(isAreaClicked(window,150,400))
	            {
	                 textEntry(window,155,400,Password);
	            }
	            else if(isAreaClicked(window,350,450))
	            {
	               loop=checkLogin();
	            }
	        }
    	}
    }
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
void messageHandler(RenderWindow &window)
{
	bool run=true;
	Event event;
	while(run)
	{
		while(window.pollEvent(event)&&run)
		{
			if (event.type == Event::Closed)
		        window.close();
		}
	}
}
int main()
{
	RenderWindow window(VideoMode(600,600),"Messenger",Style::TitleBar|Style::Close);
	window.setPosition(Vector2i(600,200));
	window.setVertical()SyncEnabled(true);
	window.clear(Color(240,240,240));
	Texture texture;
	Sprite sprite;
	createSprite(window,texture,sprite,"client.png",130,255);
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
		        if(isAreaClicked(window,sprite.getGlobalBounds().left,sprite.getGlobalBounds().top,
		        				(sprite.getGlobalBounds().left+sprite.getGlobalBounds().width),
		        				(sprite.getGlobalBounds().right+sprite.getGlobalBounds().height))
		        {
		            run=false;
		        }
		    }
		}
		window.display();
	}
	window.clear(Color(240,240,240));
    login(window);
    window.clear(Color(240,240,240));
    messageHandler(window);
	return 0;
}

