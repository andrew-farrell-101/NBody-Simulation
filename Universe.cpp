#include "Universe.h"

sf::Vector2<double> pairwise_force(const CelestialBody& a, const CelestialBody& b)
{   
    double gravity = 6.67e-11;
    double dX = b.position.x - a.position.x;
    //cout << "dX: " << dX << std::endl;
    double dY = b.position.y - a.position.y;
    // cout << dY << std::endl;
    // cout << "dY: " << dY << std::endl;
    double r = std::sqrt((pow(dX, 2.0)) + pow(dY, 2.0));
    // F = G * m1 * m2 / (r ** 2)
    double F = (gravity * a.mass * b.mass) / (pow(r, 2.0));
    // double distance = (((a.position.x - b.position.x) ** 2) + ((a.position.y - b.position.y) ** 2)) ** 0.5;
    sf::Vector2<double> force = sf::Vector2<double>(0, 0);
    force.x = F * (dX / r);
    force.y = F * (dY / r);
    return force;
}

void Universe::step(double seconds){
    //for each planet in the universe, calulate the net force
    
    for(auto i: bodies)
    {
        // cout << *i;
        sf::Vector2<double> velocity = i->getVelocity();
        sf::Vector2<double> netForce = sf::Vector2<double>(0,0);
        sf::Vector2<double> acceleration = sf::Vector2<double>(0,0);
        for(auto j: bodies)
        {
            if (i != j)
            {
                // Calculate the pairwise force and add it
                netForce += pairwise_force(*i, *j);
            }
        }
        // cout << "NetForce: " << "(" << netForce.x << " " << netForce.y << ")" << std::endl;

        acceleration =  i->get_acceleration(netForce);
        // cout << "Acceleration: " << "(" << acceleration.x << " " << acceleration.y << ")" << std::endl;

        velocity.x += seconds * acceleration.x;
        velocity.y += seconds * acceleration.y;
        // cout << "Velocity: " << "(" << velocity.x << " " << velocity.y << ")" << std::endl;
        
        sf::Vector2<double> position = i->getPosition();
        // cout << "Old Posititon: " << "(" << position.x << " " << position.y << ")" << std::endl;
        position.x += seconds * velocity.x;
        position.y += seconds * velocity.y;
        // cout << "New Posititon: " << "(" << position.x << " " << position.y << ")" << std::endl;

        i->setVelocity(velocity);
        i->setPosition(position);
    }
    // cout << std::endl;
}
void Universe::output() const
{
    for(auto i: bodies)
    {
        std::cout << *i << std::endl;
    }
}
void Universe::setDimensions(const sf::RenderWindow& target)
{
    for(auto i : bodies)
    {
        (*i).updateDimensions(target);
    }
} 

void Universe::display(sf::RenderTarget& target) const
{
    for (auto i: bodies)
    {
        // cout << *i;
        i->setPosition(i->getPosition());
        target.draw(*i);
    }
    // cout << std::endl;
}

void Universe::setRadius(const double& radius)
{
    for(auto i : bodies)
    {
        (*i).setRadius(radius);
    }
}

Universe::Universe(int count)
{
    for(int i = 0; i  < count; i++)
    {
        bodies.push_back(std::make_shared<CelestialBody>());
    }
}

istream& operator>>(istream& in, Universe& obj)
{
    obj.bodies.push_back(std::make_shared<CelestialBody>());
    in >> *(obj.bodies.back());
    return in;
}