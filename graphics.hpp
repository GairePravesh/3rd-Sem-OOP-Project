#include<SFML/Graphics.hpp>

using namespace sf;
class GUI
{
private:
    int sizeX,sizeY;
    int screenWidth;
    int screenHeight;
    RenderWindow &window;

public:
    GUI(RenderWindow &w):window(w){}
    void run()
    {
        // run the program as long as the window is open
        while (window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                    window.close();

            }
        }
    }
    void closeGUI()
    {
        window.close();
    }
};
