#include "Boid.hpp"

Boid::Boid(float x, float y)
{
    pos_ = {x, y};

    boid_.setFillColor(sf::Color::Transparent);
    boid_.setOutlineColor(sf::Color::White);
    boid_.setOutlineThickness(2);

    boid_.setPointCount(3);
    boid_.setRadius(size_);

    boid_.setOrigin(size_, size_);

    setRandomVelocity();
    setRandomAcceleration();
};

float getDistance(Boid* cur, Boid* neighbour, sf::RenderWindow* window)
{
    int screenX = window->getSize().x;
    int screenY = window->getSize().y;

    float diffX = (*cur->getPosition())[0] - (*neighbour->getPosition())[0];
    if(screenX - abs(diffX) < abs(diffX))
        diffX = screenX - abs(diffX);

    float diffY = (*cur->getPosition())[1] - (*neighbour->getPosition())[1];
    if(screenY - abs(diffY) < abs(diffY))
        diffY = screenY - abs(diffY);

    return sqrt((diffX * diffX) + (diffY * diffY));
}

void Boid::setPosition(float x, float y) { pos_ = {x, y}; }
vector<float>* Boid::getPosition() { return &pos_; }

void Boid::setVelocity(float x, float y) { vel_ = {x, y}; }
vector<float>* Boid::getVelocity() { return &vel_; }

void Boid::setAcceleration(float x, float y) { acc_ = {x, y}; }
vector<float>* Boid::getAcceleration() { return &acc_; }

sf::CircleShape* Boid::getBoidShape() { return &boid_; }

void Boid::setRandomVelocity() { vel_ = random2DVector(-2.0f, 2.0f); }
void Boid::setRandomAcceleration() { acc_ = random2DVector(-0.1f, 0.1f); }

void Boid::setSeparationCeiling(float f) { separationCeiling_ = f; }
void Boid::setSeparationRadius(float f) { separationRadius_ = f; }

void Boid::updateRotation()
{
    float angle = atan(vel_[0] / (-1 * vel_[1]));
    float res = (180 * angle / PI);

    if(vel_[1] > 0)
        res += 180.0f;

    boid_.setRotation(res);
}

void Boid::updatePosition(sf::RenderWindow* window)
{
    int screenX = window->getSize().x;
    int screenY = window->getSize().y;

    pos_[0] += vel_[0];  // x value
    pos_[1] += vel_[1];  // y value

    if(pos_[0] < 0)
        pos_[0] = screenX;
    if(pos_[0] > screenX)
        pos_[0] = 0;

    if(pos_[1] < 0)
        pos_[1] = screenY;
    if(pos_[1] > screenY)
        pos_[1] = 0;

    boid_.setPosition(pos_[0], pos_[1]);
}
void Boid::updateVelocity()
{
    float maxVelocity = MAX_SPEED;

    vel_[0] += acc_[0];  // x value
    vel_[1] += acc_[1];  // y value

    if(vel_[0] > maxVelocity)
        vel_[0] = maxVelocity;

    if(vel_[0] < -1 * maxVelocity)
        vel_[0] = -1 * maxVelocity;

    if(vel_[1] > maxVelocity)
        vel_[1] = maxVelocity;

    if(vel_[1] < -1 * maxVelocity)
        vel_[1] = -1 * maxVelocity;
}

void Boid::align(vector<Boid*> v, sf::RenderWindow* window)
{
    float radius = ALIGN_RADIUS;

    vector<float> avgVelocity = {0.0f, 0.0f};
    int count = 0;

    for(int i = 0; i < v.size(); i++)
    {
        Boid* cur = v[i];
        float diff = getDistance(this, cur, window);

        if(diff <= radius && cur != this)
        {
            count++;
            avgVelocity[0] += (*cur->getVelocity())[0];
            avgVelocity[1] += (*cur->getVelocity())[1];
        }
    }

    if(count > 0)
    {
        avgVelocity[0] /= count;
        avgVelocity[1] /= count;

        setMagnitude(avgVelocity, 3.0f);

        avgVelocity[0] -= (*this->getVelocity())[0];
        avgVelocity[1] -= (*this->getVelocity())[1];

        float ceiling = ALIGN_CEIL;
        limit(avgVelocity[0], ceiling);
        limit(avgVelocity[1], ceiling);
    }

    float accX = (*this->getAcceleration())[0];
    float accY = (*this->getAcceleration())[1];

    this->setAcceleration(accX + avgVelocity[0], accY + avgVelocity[1]);
}

void Boid::cohesion(vector<Boid*> v, sf::RenderWindow* window)
{
    float radius = COHESION_RADIUS;

    vector<float> avgVelocity = {0.0f, 0.0f};
    int count = 0;

    for(int i = 0; i < v.size(); i++)
    {
        Boid* cur = v[i];
        float diff = getDistance(this, cur, window);

        if(diff <= radius && cur != this)
        {
            count++;
            avgVelocity[0] += (*cur->getPosition())[0];
            avgVelocity[1] += (*cur->getPosition())[1];
        }
    }

    if(count > 0)
    {
        avgVelocity[0] /= count;
        avgVelocity[1] /= count;

        avgVelocity[0] -= (*this->getPosition())[0];
        avgVelocity[1] -= (*this->getPosition())[1];

        // setMagnitude(avgVelocity, 10);

        avgVelocity[0] -= (*this->getVelocity())[0];
        avgVelocity[1] -= (*this->getVelocity())[1];

        float ceiling = COHESION_CEIL;
        limit(avgVelocity[0], ceiling);
        limit(avgVelocity[1], ceiling);
    }

    float accX = (*this->getAcceleration())[0];
    float accY = (*this->getAcceleration())[1];

    this->setAcceleration(accX + avgVelocity[0], accY + avgVelocity[1]);
}

void Boid::separation(vector<Boid*> v, sf::RenderWindow* window)
{
    float radius = separationRadius_;

    vector<float> avgVelocity = {0.0f, 0.0f};
    int count = 0;

    for(int i = 0; i < v.size(); i++)
    {
        Boid* cur = v[i];
        float diff = getDistance(this, cur, window);

        if(diff <= radius && cur != this)
        {
            float posDiffX = (*this->getPosition())[0] - (*cur->getPosition())[0];
            float posDiffY = (*this->getPosition())[1] - (*cur->getPosition())[1];

            if(diff != 0.0f)
            {
                posDiffX /= diff;
                posDiffY /= diff;
            }
            else
            {
                posDiffX /= 0.01f;
                posDiffY /= 0.01f;
            }
            count++;

            avgVelocity[0] += posDiffX;
            avgVelocity[1] += posDiffY;
        }
    }

    if(count > 0)
    {
        avgVelocity[0] /= count;
        avgVelocity[1] /= count;

        // setMagnitude(avgVelocity, 2.0f);

        avgVelocity[0] -= (*this->getVelocity())[0];
        avgVelocity[1] -= (*this->getVelocity())[1];

        float ceiling = separationCeiling_;
        limit(avgVelocity[0], ceiling);
        limit(avgVelocity[1], ceiling);
    }

    float accX = (*this->getAcceleration())[0];
    float accY = (*this->getAcceleration())[1];

    this->setAcceleration(accX + avgVelocity[0], accY + avgVelocity[1]);
}

void Boid::flock(vector<Boid*> flock, sf::RenderWindow* window)
{
    align(flock, window);
    cohesion(flock, window);
    separation(flock, window);
}

void Boid::attach(vector<sf::CircleShape>* s)
{
    float radius = ATTACHMENT_RADIUS;

    vector<float> avgVelocity = {0.0f, 0.0f};
    int count = 0;

    for(int i = 0; i < s->size(); i++)
    {
        sf::CircleShape cur = (*s)[i];

        float diffX = (*this->getPosition())[0] - cur.getPosition().x;
        float diffY = (*this->getPosition())[1] - cur.getPosition().y;
        float diff = sqrt(diffX * diffX + diffY * diffY);

        if(diff <= radius)
        {
            count++;
            avgVelocity[0] += cur.getPosition().x;
            avgVelocity[1] += cur.getPosition().y;
        }
    }

    if(count > 0)
    {
        avgVelocity[0] /= count;
        avgVelocity[1] /= count;

        avgVelocity[0] -= (*this->getPosition())[0];
        avgVelocity[1] -= (*this->getPosition())[1];

        // setMagnitude(avgVelocity, 10);

        avgVelocity[0] -= (*this->getVelocity())[0];
        avgVelocity[1] -= (*this->getVelocity())[1];

        float ceiling = ATTACHMENT_CEIL;
        limit(avgVelocity[0], ceiling);
        limit(avgVelocity[1], ceiling);
    }

    float accX = (*this->getAcceleration())[0];
    float accY = (*this->getAcceleration())[1];

    this->setAcceleration(accX + avgVelocity[0], accY + avgVelocity[1]);
}

void Boid::flockToSteerable(vector<Boid*> flock, vector<sf::CircleShape>* s, sf::RenderWindow* window)
{
    attach(s);
    separation(flock, window);
}

void Boid::explode()
{
    acc_ = random2DVector(-15.0f, 15.0f);
    vel_ = random2DVector(-15.0f, 15.0f);
}

void Boid::update(sf::RenderWindow* window)
{
    updatePosition(window);
    updateVelocity();
    updateRotation();
    this->setAcceleration(0, 0);
}
