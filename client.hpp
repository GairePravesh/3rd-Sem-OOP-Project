#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace sf;
class Client:public GUI
{
private:
    std::string IP_address;
    std::string Port_no;
    std::string Username;
    std::string Password;
    public:
    void clientHome(RenderWindow &window)
    {
        window.setTitle("Messenger : Client");
        Texture Logintexture,IPtexture,Porttexture,Usertexture,Codetexture;
        Sprite Loginsprtie,IPsprite,Portsprite,Usersprite,Codesprite;
        createSprite(window,Logintexture,Loginsprtie,"login",50,10);
        GUI::displayText(window,"Login Credentials",150,10,30);
        GUI::createSprite(window,Logintexture,Loginsprtie,"IP",50,100);
        GUI::drawBox(window,150,100);
        GUI::createSprite(window,Logintexture,Loginsprtie,"Port",50,200);
        GUI::drawBox(window,150,200);
        GUI::createSprite(window,Logintexture,Loginsprtie,"User",50,300);
        GUI::drawBox(window,150,300);
        GUI::createSprite(window,Logintexture,Loginsprtie,"Password",50,400);
        GUI::drawBox(window,150,400);
        GUI::drawBox(window,350,450,100,45);
        GUI::displayText(window,"Submit",352,460);
        GUI::displayText(window,IP_address,155,100);
        GUI::displayText(window,Port_no,155,200);
        GUI::displayText(window,Username,155,300);
        GUI::displayText(window,Password,155,400);
        window.display();
        while(true)
        {
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                if(GUI::isAreaClicked(window,150,100))
                {
                    GUI::textEntry(window,155,100,IP_address);
                }
                else if(GUI::isAreaClicked(window,150,200))
                {
                     GUI::textEntry(window,155,200,Port_no);
                }
                else if(GUI::isAreaClicked(window,150,300))
                {
                    GUI::textEntry(window,155,300,Username);
                }
                else if(GUI::isAreaClicked(window,150,400))
                {
                     GUI::textEntry(window,155,400,Password);
                }
                else if(GUI::isAreaClicked(window,350,450))
                {
                   break;
                }
            }
        }
    }

    bool loginResult(){}
};
