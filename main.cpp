#include"graphics.hpp"
int main()
{
    //initialize window
    RenderWindow window(VideoMode(500, 500), "Messenger");
    GUI app(window);
    app.run();
    app.closeGUI();
    return 0;
}
