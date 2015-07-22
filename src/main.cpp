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

  Pendulum pendulum( window.getSize().x, window.getSize().y );
  Tracer tracer( window.getSize().x, window.getSize().y );

  while( window.isOpen() ) {
    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }
    
    window.clear();
    
    // Pendulum
    pendulum.updatePendulum();
    window.draw( pendulum );

    // Tracers
    tracer.setPos(&pendulum);
    window.draw(tracer);


    window.display();    
  }
  return 0;
}
