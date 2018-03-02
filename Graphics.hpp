#ifndef ADD_H
#define ADD_H
#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
using namespace sf;
class GUI
{
private:
    std::string String;
    bool loop=true;
public:
    //void initWindow(RenderWindow &,int,int,std::string );
    void createSprite(RenderWindow &,Texture &,Sprite &,std::string ,int ,int );
    int  isSpriteClicked(RenderWindow &,Sprite &,Sprite &);
    void textEntry(RenderWindow &,int ,int ,std::string &);
    void displayText(RenderWindow &,std::string ,int ,int ,int s=20);
    void drawBox(RenderWindow &,int ,int ,int width=300,int height=40);
    bool isAreaClicked(RenderWindow &,int ,int ,int width=300,int height=40);
    void closeWindow(RenderWindow &);
};

#endif
