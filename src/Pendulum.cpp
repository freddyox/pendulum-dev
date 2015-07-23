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

  float radius = 3.0;
  origin.setRadius(radius);
  sf::FloatRect originRect = origin.getLocalBounds();
  origin.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  origin.setFillColor( pendulumColor );
  origin.setPosition( mscreenwidth/2.0, mscreenheight/2.0 - height/2.0 );  

  bottom.setRadius(radius);
  originRect = bottom.getLocalBounds();
  bottom.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  bottom.setFillColor( pendulumColor );
  
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
  omega_knot = 0.0;
}

void Pendulum::draw( sf::RenderTarget& target, sf::RenderStates) const {
  target.draw( pendulum );
  target.draw( origin );
  //target.draw( bottom );
}

void Pendulum::updatePendulum(float time) {
  timer = time;
  theta = exp(-time/30)*theta_knot*cos( omega*time );
  theta_dot = -omega*theta_knot*sin( omega*time );
  pendulum.setRotation(theta);
}

void Pendulum::updatePendulumRK4(float time, float h) {
  timer = time;
  // k refers to theta_dot = omega
  // l refers to omega_dot = -w^2*sin(theta)
//   float k0 = omega_knot;
//   float l0 = -omega_knot*omega_knot*sin(theta_knot);
//   float k1 = omega_knot+l0/2.0;
//   float l1 = -omega_knot*omegaknot*
// float k1 = 


}

void Pendulum::chooseMethod(float time, float h) {
  if( theta_knot < 10 )
    updatePendulum(time);
  else
    updatePendulumRK4(time,h);
}

void Pendulum::addDrag(float time) {
}

sf::Vector2f Pendulum::getPendulumPosition() {
  sf::Vector2f temp( -height*sin(theta/60.0), height*cos(theta/60.0) );
  sf::Vector2f origin2pendulum( mscreenwidth/2.0, mscreenheight/2.0 - height/2.0 );
  bottom.setPosition( temp+origin2pendulum );
  return temp+origin2pendulum;
}
