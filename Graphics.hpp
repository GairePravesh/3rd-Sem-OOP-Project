#ifndef ADD_H
#define ADD_H
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
    bool loop=true;
public:
    GUI(RenderWindow &w):window(w){}
    void createSprite(Texture &,Sprite &,std::string ,int ,int );
    int isSpriteClicked(Sprite &,Sprite &);
    void closeWindow();
    void serverHome();
    void clientHome();
    void textEntry(int ,int ,std::string &);
    void displayText(std::string ,int ,int ,int s=20);
    void drawBox(int ,int ,int width=300,int height=40);
    bool isAreaClicked(int ,int ,int width=300,int height=40);
    bool loginResult();
};

#endif
