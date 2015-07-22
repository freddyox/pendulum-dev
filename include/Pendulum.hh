#ifndef PENDULUM_HH
#define PENDULUM_HH

#include <SFML/Graphics.hpp>

class Pendulum : public sf::Drawable, public sf::Transformable
{
private:
sf::Vector2f pendulumSize;
float width,height;
float mscreenwidth, mscreenheight;
sf::Color pendulumColor;
sf::RectangleShape pendulum;
sf::CircleShape origin;
float theta_knot;
float omega;
float gravity;
float theta;
float theta_dot;
float t;

public:
Pendulum(float,float);
~Pendulum() {};
void draw(sf::RenderTarget&, sf::RenderStates) const;
sf::Vector2f getpendulumSize() { return pendulumSize; }
void updatePendulum();
sf::Vector2f getPendulumPosition();
};
#endif
