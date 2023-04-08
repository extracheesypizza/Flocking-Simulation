#include "Flock.hpp"

Flock::Flock(int n, sf::RenderWindow *window)
{
    int x = window->getSize().x;
    int y = window->getSize().y;
    for(int i = 0; i < n; i++)  //
        flock_.push_back(new Boid(randomFloat(0.05 * x, 0.95 * x), randomFloat(y / 4, y * 3 / 4)));
}

vector<Boid *> *Flock::getFlock() { return &flock_; }

void Flock::setFlockSeparationCeiling(float f)
{
    for(int i = 0; i < flock_.size(); i++)  //
        flock_[i]->setSeparationCeiling(f);
}

void Flock::setFlockSeparationRadius(float f)
{
    for(int i = 0; i < flock_.size(); i++)  //
        flock_[i]->setSeparationRadius(f);
}

void Flock::updateBoids(sf::RenderWindow *window)
{
    for(int i = 0; i < flock_.size(); i++)  //
        flock_[i]->update(window);
}

void Flock::flockEmUp(sf::RenderWindow *window)
{
    for(int i = 0; i < flock_.size(); i++)  //
        flock_[i]->flock(flock_, window);
}

void Flock::flockToText(vector<sf::CircleShape> *shapes, sf::RenderWindow *window)
{
    for(int i = 0; i < flock_.size(); i++)  //
        flock_[i]->flockToSteerable(flock_, shapes, window);
}

void Flock::explodeEm()
{
    for(int i = 0; i < flock_.size(); i++)  //
        flock_[i]->explode();
}
