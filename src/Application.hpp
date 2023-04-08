#ifndef APPLICATION_H
#define APPLICATION_H

#include "Boid.hpp"
#include "Flock.hpp"
#include "Render.cpp"

class Application
{
   private:
    Flock* flock_;
    sf::RenderWindow* window_;

   public:
    Application(){};
    void execute();
    void handleResize(sf::Event event);
    void handleResizeStartup(sf::Event event, vector<sf::CircleShape>& shapes);
};

#endif  // APPLICATION_H
