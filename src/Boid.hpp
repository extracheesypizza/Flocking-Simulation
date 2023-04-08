#ifndef BOID_H
#define BOID_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "Functions.hpp"

using namespace std;

//////////////////////////////////////////////////////////
#define PI 3.14159265

#define ALIGN_RADIUS 100.0f
#define ALIGN_CEIL 0.1f

#define COHESION_RADIUS 100.0f
#define COHESION_CEIL 0.01f

#define ATTACHMENT_RADIUS 75.0f
#define ATTACHMENT_CEIL 0.50f

#define MAX_SPEED 7

#define BOIDS 250
//////////////////////////////////////////////////////////

class Boid
{
   private:
    float size_ = 3.0f;
    vector<float> pos_ = {0.0f, 0.0f};
    vector<float> vel_ = {0.0f, 0.0f};
    vector<float> acc_ = {0.0f, 0.0f};
    sf::CircleShape boid_;
    float separationCeiling_ = 30.8f;
    float separationRadius_ = 35.0f;

   public:
    Boid(){};
    Boid(float x, float y);

    void setPosition(float x, float y);
    vector<float>* getPosition();

    void setVelocity(float x, float y);
    vector<float>* getVelocity();

    void setAcceleration(float x, float y);
    vector<float>* getAcceleration();

    sf::CircleShape* getBoidShape();

    void setRandomVelocity();
    void setRandomAcceleration();

    void setSeparationCeiling(float f);
    void setSeparationRadius(float f);

    // update parameters
    void update(sf::RenderWindow* window);
    void updatePosition(sf::RenderWindow* window);
    void updateVelocity();
    void updateRotation();

    // functions
    void flock(vector<Boid*> v, sf::RenderWindow* window);
    void align(vector<Boid*> v, sf::RenderWindow* window);
    void cohesion(vector<Boid*> v, sf::RenderWindow* window);
    void separation(vector<Boid*> v, sf::RenderWindow* window);

    // startup screen functions
    void flockToSteerable(vector<Boid*> b, vector<sf::CircleShape>* s, sf::RenderWindow* window);
    void attach(vector<sf::CircleShape>* s);
    void explode();
};

#endif  // BOID_H
