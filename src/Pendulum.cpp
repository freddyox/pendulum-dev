#include "../include/Pendulum.hh"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

Pendulum::Pendulum(float displayx, float displayy) {
  mscreenwidth = displayx;
  mscreenheight = displayy;
  width = 3.0;
  height = 150.0;
  sf::Vector2f pendulumSize(width,height);
  sf::Color pendulumColor = sf::Color( sf::Color(74,235,219) );

  float radius = 5.0;
  origin.setRadius(radius);
  sf::FloatRect originRect = origin.getLocalBounds();
  origin.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  origin.setFillColor( pendulumColor );
  origin.setPosition( mscreenwidth/2.0, mscreenheight/2.0 - height/2.0 );  

  pendulum.setSize( pendulumSize );
  pendulum.setOrigin( width/2.0, 0 ); // center origin
  pendulum.setFillColor( pendulumColor );
  pendulum.setPosition( mscreenwidth/2.0, mscreenheight/2.0 - height/2.0 );

  // Initial Conditions: theta_knot, theta_knot_dot = 0
  srand( time(NULL) );
  theta_knot = (rand() % 180); //0-180 degrees
  pendulum.setRotation( theta_knot ); //deg
  theta = theta_knot;
  theta_dot = 0.0;
  gravity = 9.8; // m/s^s
  omega = sqrt( gravity/(height/2.0) ); 
  t = 0.0;
}

void Pendulum::draw( sf::RenderTarget& target, sf::RenderStates) const {
  target.draw( pendulum );
  target.draw( origin );
}

void Pendulum::updatePendulum() {
  theta = theta_knot*cos( omega*t/60.0 );
  theta_dot = -omega*theta_knot*sin( omega*t );
  pendulum.setRotation(theta);
  t++;
}

sf::Vector2f Pendulum::getPendulumPosition() {
  sf::Vector2f temp(-height*sin(theta), height*cos(theta)  );
  sf::Vector2f origin2pendulum( mscreenwidth/2.0, mscreenheight/2.0 - height/2.0 );
  return temp+origin2pendulum;
}
