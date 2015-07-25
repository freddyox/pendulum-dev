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

  // RK4
  u1_knot = theta_knot;
  u2_knot = 0.0;

  //Initialize RK4
  u1_nth=u1_knot;
  u2_nth=U2_knot;
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

void Pendulum::updatePendulumRK4(float time, float g) {
  timer = time;  
  float h = 1/g; // step size
  // k,l refers to (d/dt)(u1,u2) = (u2, -u2^2*sin(u1) )
  // step size at end of calculation
 

  float l0= -pow(omega,2)*sin(u1_nth);
  float l1= -pow(omega,2)*sin(u1_nth+h*0.5*l0);
  float l2= -pow(omega,2)*sin(u1_nth+h*0.5*l1);
  float l3= -pow(omega,2)*sin(u1_nth+h*0.5*l2);
  
  float u2soln= u2_nth+(h/6)*(l0+2*l1+2*l2+l3);

  float k0= u2_nth;
  float k1= u2_nth+h*0.5*k0;
  float k2= u2_nth+h*0.5*k1;
  float k3= u2_nth+h*0.5*k2;

  float u1soln= u1_nth+(h/6)*(k0+2*k1+2*k2+k3);

  u1_nth=u1soln;
  u2_nth=u2soln;



  // float k0 = u2_nth;
  
  //float l0 = -pow(u2_knot,2)*sin( u2_knot*time );
  
  // float k1 = u2_nth + 0.5*l0;
  // float l1 = -pow(u2_knot+0.5*l0,2)*sin( (u2_knot+0.5*l0)*(time+0.5*h) );

  // float k2 = u2_knot + 0.5*l1;
  // float l2 = -pow(u2_knot+0.5*l1,2)*sin( (u2_knot+0.5*l1)*(time+0.5*h) );

  // float k3 = u2_knot + l2;
  // float l3 = -pow(u2_knot+l2,2)*sin( (u2_knot+l2)*(time+h) );
  
  // float u1_plus_one = u1_knot + (h/6.0)*( k0 + 2*k1 + 2*k2 + k3);
  // float u2_plus_one = u2_knot + (h/6.0)*( l0 + 2*l1 + 2*l2 + l3);

  // u2_knot = u2_plus_one;
  //  pendulum.setRotation( u1_plus_one );

pendulum.setRotation( u1_nth );

}

void Pendulum::chooseMethod(float time, float h) {
  if( theta_knot < 10 )
    updatePendulum(time);
  else
    updatePendulumRK4(time,h);
}

void Pendulum::addDrag(float time) {
  ;
}

sf::Vector2f Pendulum::getPendulumPosition() {
  sf::Vector2f temp( -height*sin(theta/60.0), height*cos(theta/60.0) );
  sf::Vector2f origin2pendulum( mscreenwidth/2.0, mscreenheight/2.0 - height/2.0 );
  bottom.setPosition( temp+origin2pendulum );
  return temp + origin2pendulum;
}
