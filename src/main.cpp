//    ************************************************************
//    *                    Pendulum Simulation                   *
//    *                         June 2015                        *
//    ************************************************************
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../include/Pendulum.hh"
#include "../include/Tracer.hh"

#include <iostream>


const float gDisplayx = 800;
const float gDisplayy = 800;
int main() {
  //GAME SETUP
  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Simulation");
  window.setFramerateLimit(60);

  // Initializing
  Pendulum pendulum( window.getSize().x, window.getSize().y );
  Tracer tracer( window.getSize().x, window.getSize().y );

  // Handling Time
  float t = 0.0;
  float dt = 1.0/60.0;
 
  while( window.isOpen() ) {
      sf::Event event;
      while( window.pollEvent(event) ) {
	if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	  window.close();
	}
      }
      // UPDATING
      pendulum.updatePendulum(t);

      tracer.setPos(&pendulum);
      tracer.dissolve(&pendulum);
      // DRAWINGS
      window.clear();

      // Pendulum    
      window.draw( pendulum );
    
      // Tracers
      window.draw(tracer);

      window.display();   

      t+=dt;
 
  }
  return 0;
}
