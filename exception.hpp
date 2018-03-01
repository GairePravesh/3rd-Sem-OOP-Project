#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include"Graphics.hpp"
class Exception:public GUI
{
private:
    RenderWindow &window;
public:
    Exception(RenderWindow &w):window(w){}

}
