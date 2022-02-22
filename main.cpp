#include "Universe.h"

using std::endl;

int main(int argc, char* argv[])
{
    sf::Image background;
    if(!background.loadFromFile("starfield.jpg"))
    {
        std::cout << "Failed to load starfield.jpg" << std::endl;
        exit(1);
    }
    sf::Texture background_texture;
    background_texture.loadFromImage(background);
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    background_sprite.setOrigin(0,0);
    background_sprite.setScale(2,2);
    
    double T(std::stod(argv[1])), dT(std::stod(argv[2])), radius;
    unsigned count;

    cin >> count;
    cin >> radius;

    Universe space;
    sf::RenderWindow window(sf::VideoMode(800, 800), "My window");

    for(unsigned i = 0; i < count; i++){
       cin >> space;
    }
   
    space.setDimensions(window);
    space.setRadius(radius);
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.draw(background_sprite);
        space.step(dT);
        space.display(window);
        window.display(); 
        
        T -= dT;
        if(T <= dT)
            break;
        
    }
    space.output();
    return 0;
}