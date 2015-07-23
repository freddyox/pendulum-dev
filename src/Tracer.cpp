#include "../include/Tracer.hh"

Tracer::Tracer(float displayx, float displayy) {
  mscreenwidth = displayx;
  mscreenheight = displayy;
  life = 3.0;
  float radius(1.0);
  sf::Color tracercolor = sf::Color::Red;
  circletracer.setRadius(radius);
  sf::FloatRect originRect = circletracer.getLocalBounds();
  circletracer.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  circletracer.setFillColor( tracercolor );
}

void Tracer::draw( sf::RenderTarget& target, sf::RenderStates ) const {
  std::vector<sf::CircleShape>::const_iterator cit;
  for( cit = trace.begin(); cit != trace.end(); cit++ ) {
    target.draw( *cit );
  }
}

void Tracer::setPos(Pendulum* ptr) {
  sf::Vector2f x_knot = ptr->getPendulumPosition();
  circletracer.setPosition( x_knot );
  trace.push_back( circletracer );
}

void Tracer::dissolve(Pendulum* ptr) {
  sf::Clock timer;
  time+=timer.getElapsedTime();
  float life = time.asSeconds();
  sf::Vector2f temp = ptr->getPendulumPosition();
  for( it=trace.begin(); it != trace.end(); it++) {
    sf::Vector2f tracerposition = (*it).getPosition();
    sf::Vector2f distanceVec = temp - tracerposition;
    float distance = sqrt( pow(distanceVec.x,2) + pow(distanceVec.y,2) );
    float ratio = 255/(0.2*distance);
    tracercolor = sf::Color(255,0,0,ratio);
    (*it).setFillColor( tracercolor );
    if( ratio < 10 || life >0.00001) {
	trace.erase(it);
	life = 0;
    }
  }
}
