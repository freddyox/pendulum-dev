#ifndef TRACER_HH
#define TRACER_HH

#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Pendulum.hh"

class Pendulum;

class Tracer : public sf::Transformable, public sf::Drawable
{
private:
  float mscreenwidth, mscreenheight;
  sf::CircleShape circletracer;
  std::vector<sf::CircleShape> trace;
  std::vector<sf::CircleShape>::iterator it;

public:
  Tracer(float,float);
  ~Tracer() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void setPos(Pendulum*);

};
#endif
