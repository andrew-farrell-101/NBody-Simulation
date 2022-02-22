#include "CelestialBody.h"

using std::cin;
using std::cout;
using std::endl;

CelestialBody::CelestialBody(double x_in, double y_in, double xVel_in, double yVel_in, double mass_in, string filename_in)
{
    if(!image.loadFromFile(filename_in))
    {
        std::cout << "Failed to load " << filename_in << std::endl;
        exit(1);
    }
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    //figure out x and y pixl pos for the sprite
    filename = filename_in;
   
    position = sf::Vector2<double>(x_in, y_in);
    velocity = sf::Vector2<double>(xVel_in, yVel_in);
    
    mass = mass_in;
}

sf::Vector2f CelestialBody::getCartesianPosition() const
{
    //std::cout << "Radius: " << radius << '\n' << "X Position" << '\n'  << position.x << '\n' << "Window X" << window_dimensions.x << std::endl;
    float x = (radius + position.x)*((window_dimensions.x) / (2 * radius));
    float y = (radius - position.y)*((window_dimensions.y) / (2 * radius));
    //std::cout << "Target->(" << x << ", " << y << ")" << std::endl;
    return sf::Vector2f(x, y);
}

sf::Vector2<double> CelestialBody::get_acceleration(const sf::Vector2<double>& force) const
{
    double x, y;
    x = force.x / mass;
    y = force.y / mass;
    return sf::Vector2<double> (x, y);
}

void CelestialBody::setPosition(sf::Vector2<double>& pos)
{
    this->position = pos;
    //std::cout << "Radius: " << radius << '\n' << "X Position" << '\n'  << position.x << '\n' << "Window X" << window_dimensions.x << std::endl;
    //std::cout << "Target->(" << x << ", " << y << ")" << std::endl;
    sprite.setPosition(this->getCartesianPosition());
}

void CelestialBody::setVelocity(sf::Vector2<double>& vel)
{
    velocity = vel;
}

sf::Vector2<double>& CelestialBody::getPosition()
{
    return position;
}

void CelestialBody::updateDimensions(const sf::RenderWindow& target)
{
    window_dimensions = target.getSize();
    //std::cout << "WindowDimensions->(" << window_dimensions.x << ", " << window_dimensions.y << ")" << std::endl;
}

istream& operator>>(istream& in, CelestialBody& obj)
{
    in >> obj.position.x >> obj.position.y >> obj.velocity.x >> obj.velocity.y >> obj.mass;
    string filename_in;
    cin >> filename_in;
    obj.filename = filename_in;
    if(!obj.image.loadFromFile(filename_in))
    {
        std::cout << "Failed to load " << filename_in << std::endl;
        exit(1);
    }
    obj.texture.loadFromImage(obj.image);
    obj.sprite.setTexture(obj.texture);
    return in;
}

ostream& operator<<(ostream& out, const CelestialBody &obj)
{
    out << obj.position.x << "  " << obj.position.y << "  " << obj.velocity.x << "  " << obj.velocity.y << "  " << obj.mass << "  " << obj.filename << std::endl;
    return out;
}