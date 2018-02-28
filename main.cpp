#include"homepage.hpp"
#include<iostream>

int main()
{
    RenderWindow home(VideoMode(500, 500), "Messenger",Style::Titlebar | Style::Close);
    GUI app(home);
    app.run();
    app.closeWindow();
    return 0;
}
