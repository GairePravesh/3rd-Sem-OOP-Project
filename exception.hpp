#include<SFML/Graphics.hpp>
#include"Graphics.hpp"
#include<string>
#include<iostream>
using namespace sf;
class Exception:public GUI
{
private:
    int error;
public:
    Exception(int s):error(s){}
    void displayError()
    {
        RenderWindow popup(VideoMode(400,100), "Messenger",Style::Titlebar | Style::Close);
        popup.setPosition(Vector2i(800,400));
        popup.setVerticalSyncEnabled(true);
        popup.clear(Color(240,240,240));
        switch (error)
        {
            case 1: //server host problem
            case 2: //client login problem
                GUI::displayText(popup,"Sorry Wrong Input, Try Again",5,5);
                break;
        }
        GUI::drawBox(popup,250,50,100);
        GUI::displayText(popup,"Ok",278,58);
        Event event;
        while(popup.isOpen())
        {
            while(popup.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    popup.close();
                if (Mouse::isButtonPressed(Mouse::Left))
                {
                    if(GUI::isAreaClicked(popup,250,60,100,40))
                        popup.close();;
                }
            }
            popup.display();
        }
    }
};
