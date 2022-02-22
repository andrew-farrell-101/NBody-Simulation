
#include "CelestialBody.h"

#include <vector>
#include <memory>

class Universe{
public:
    explicit Universe(){;}; 

    Universe(int count);

    void output() const;

    void setDimensions(const sf::RenderWindow& target);

    void step(double seconds);

    void setRadius(const double& radius);
    
    friend istream& operator>>(istream& in, Universe& obj);

    void display(sf::RenderTarget& target) const;

private:
    //friend sf::Vector2<double> pairwise_force(const CelestialBody& a, const CelestialBody& b);
    
    std::vector<std::shared_ptr<CelestialBody>> bodies;
};