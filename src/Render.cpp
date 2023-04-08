#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "Boid.cpp"
#include "Flock.cpp"

using namespace std;

void drawFlock(Flock* flock, sf::RenderWindow* window)
{
    window->clear(sf::Color::Black);

    vector<Boid*> v = *flock->getFlock();

    for(int i = 0; i < v.size(); i++)
    {
        sf::CircleShape curBoidShape = *v[i]->getBoidShape();
        window->draw(curBoidShape);
    }

    window->display();
}

// ONLY USED TO CREATE THE STARTUP SCREEN

void drawText(sf::RenderWindow* window)
{
    sf::Font font_;
    if(!font_.loadFromFile("arial.ttf"))
    {
        std::cout << "ERROR LOADING FONT" << std::endl;
        return;
    }

    window->clear(sf::Color::Black);

    sf::Text Flock;
    Flock.setFont(font_);
    Flock.setString("Flock");
    Flock.setCharacterSize(384);
    Flock.setFillColor(sf::Color::White);

    Flock.setOutlineColor(sf::Color::Cyan);
    Flock.setOutlineThickness(0);
    Flock.setLetterSpacing(3);

    window->draw(Flock);
    window->display();
}

float getDistanceCircles(float newX, float newY, float oldX, float oldY)
{
    float diffX = newX - oldX;
    float diffY = newY - oldY;

    return sqrt(diffX * diffX + diffY * diffY);
}

vector<sf::CircleShape> drawImage(sf::RenderWindow* window)
{
    window->clear(sf::Color::Black);

    sf::Texture background;
    if(!background.loadFromFile("text.png"))
    {
        cout << "ERROR" << endl;
        // return;
    }

    sf::Sprite textImage;
    textImage.setTexture(background);

    textImage.setPosition(window->getSize().x / 2 - textImage.getGlobalBounds().width / 2, window->getSize().y / 2 - textImage.getGlobalBounds().height / 2);
    sf::Image temp = textImage.getTexture()->copyToImage();

    float leastDiff = 40;

    int count = 0;
    vector<sf::CircleShape> res;
    for(int y = 0; y < background.getSize().y; y++)
    {
        for(int x = 0; x < background.getSize().x; x++)
        {
            if(temp.getPixel(x, y) == sf::Color::White)
            {
                count++;

                if(count >= 100)  // 124
                {
                    float newX = x + window->getSize().x / 2 - textImage.getGlobalBounds().width / 2;
                    float newY = y + window->getSize().y / 2 - textImage.getGlobalBounds().height / 2;
                    float d = 100;

                    if(res.size() > 0)
                        for(int i = 0; i < res.size(); i++)
                        {
                            float temp = getDistanceCircles(newX, newY, res[i].getPosition().x, res[i].getPosition().y);
                            if(temp < d)
                                d = temp;
                        }

                    if(d > leastDiff)
                    {
                        count = 0;
                        sf::CircleShape c;
                        c.setRadius(10);
                        c.setFillColor(sf::Color::Transparent);
                        c.setOutlineColor(sf::Color::White);
                        c.setOutlineThickness(1);
                        c.setPointCount(10);
                        c.setPosition(newX, newY);
                        res.push_back(c);
                        window->draw(c);
                    }
                }
            }
        }
    }

    // window->draw(textImage);
    // window->display();
    return res;
}
