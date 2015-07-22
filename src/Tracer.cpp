#include "../include/Tracer.hh"
#include <iostream>

Tracer::Tracer(float displayx, float displayy) {
  mscreenwidth = displayx;
  mscreenheight = displayy;

  float radius = 6.0;
  circletracer.setRadius(radius);
  sf::FloatRect originRect = circletracer.getLocalBounds();
  circletracer.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  circletracer.setFillColor( sf::Color::Red );

  for(int i=0; i<100; i++) {
    trace.push_back( circletracer );
  }
}

void Tracer::draw( sf::RenderTarget& target, sf::RenderStates ) const {
  std::vector<sf::CircleShape>::const_iterator cit;
  for( cit = trace.begin(); cit != trace.end(); cit++ ) {
    target.draw( *cit );
  }
}

void Tracer::setPos(Pendulum* ptr) {
  sf::Vector2f x_knot = ptr->getPendulumPosition();
  for( it=trace.begin(); it != trace.end(); it++ ) {
    (*it).setPosition(x_knot);
  }
}
