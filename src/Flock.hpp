#ifndef FLOCK_H
#define FLOCK_H

#include "Boid.hpp"

using namespace std;

class Flock
{
   private:
    vector<Boid *> flock_;

   public:
    Flock(int n, sf::RenderWindow *window);

    vector<Boid *> *getFlock();

    void setFlockSeparationCeiling(float f);
    void setFlockSeparationRadius(float f);

    // Flock-wide functions
    void updateBoids(sf::RenderWindow *window);
    void flockEmUp(sf::RenderWindow *window);
    void flockToText(vector<sf::CircleShape> *shapes, sf::RenderWindow *window);
    void explodeEm();
};

#endif  // FLOCK_H
