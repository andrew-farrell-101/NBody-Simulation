// #ifndef CB
// #define CB
#include <math.h>
#include <time.h> 
#include <string.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
// #endif
using std::string;
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::vector;
using std::unique_ptr;

class CelestialBody : public sf::Drawable {
public:
    // Constructor
    CelestialBody(){;}

    CelestialBody(double x_in, double y_in, double xVel_in, double yVel_in, double mass_in, string filename_in);
    // Utility function
    void updateDimensions(const sf::RenderWindow& target);

    void setRadius(double rad){radius = rad;}

    sf::Vector2f getCartesianPosition() const;

    void setPosition(sf::Vector2<double>& pos);

    void setVelocity(sf::Vector2<double>& vel);

    sf::Vector2<double>& getVelocity() {return velocity;}

    sf::Vector2<double>& getPosition();
   
    friend istream& operator>>(istream& input, CelestialBody &body);

    friend ostream& operator<<(ostream& output, const CelestialBody &body);

     virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }
    
    sf::Vector2<double> get_acceleration(const sf::Vector2<double>& force) const;

    friend sf::Vector2<double> pairwise_force(const CelestialBody& a, const CelestialBody& b);
private:
   

    sf::Vector2u window_dimensions;
    sf::Vector2<double> position;
    sf::Vector2<double> velocity;
    string filename;
    sf::Image image;
    sf::Sprite sprite;
    sf::Texture texture;
    
    double radius;
    double mass;
};