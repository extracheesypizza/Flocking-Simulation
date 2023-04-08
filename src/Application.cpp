#include "Application.hpp"

void Application::execute()
{
    // This part is dedicated to creating a random float generator
    int i, stime;
    long ltime;
    ltime = time(NULL);
    stime = (unsigned int)ltime / 2;
    srand(stime);

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Boiddy");
    window_ = &window;
    window_->setFramerateLimit(60);

    vector<sf::CircleShape> shapes;
    shapes = drawImage(window_);

    flock_ = new Flock(BOIDS, window_);
    vector<Boid *> vec = (*flock_->getFlock());
    bool startScreen = false;

    while(window_->isOpen())
    {
        sf::Event event;
        while(window_->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window_->close();

            if(event.type == sf::Event::Resized)
            {
                if(startScreen == false)
                    handleResizeStartup(event, shapes);
                else
                    handleResize(event);
            }

            if(event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Space)
                {
                    startScreen = true;
                    flock_->explodeEm();
                    flock_->setFlockSeparationCeiling(0.5f);
                    flock_->setFlockSeparationRadius(7.0f);
                }
        }

        if(!startScreen)
            flock_->flockToText(&shapes, window_);
        else
            flock_->flockEmUp(window_);

        flock_->updateBoids(window_);
        drawFlock(flock_, window_);
    }
}

void Application::handleResize(sf::Event event)
{
    // update the view to the new size of the window and keep the center
    sf::Vector2u windowSize;

    int width = event.size.width;
    int height = event.size.height;

    if(width < 500 && height > 500)
    {
        windowSize.x = 501;
        windowSize.y = height;
    }
    else if(width < 500 && height < 500)
    {
        windowSize.x = 501;
        windowSize.y = 501;
    }
    else if(width > 500 && height < 500)
    {
        windowSize.x = width;
        windowSize.y = 501;
    }
    else
    {
        windowSize.x = width;
        windowSize.y = height;
    }
    window_->setSize(windowSize);
    window_->setView(sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y)));
    drawFlock(flock_, window_);
}

void Application::handleResizeStartup(sf::Event event, vector<sf::CircleShape> &shapes)
{
    // recreate the text for boids to flock to
    shapes = shapes = drawImage(window_);

    // update the view to the new size of the window and keep the center
    sf::Vector2u windowSize;

    int width = event.size.width;
    int height = event.size.height;

    if(width < 500 && height > 500)
    {
        windowSize.x = 501;
        windowSize.y = height;
    }
    else if(width < 500 && height < 500)
    {
        windowSize.x = 501;
        windowSize.y = 501;
    }
    else if(width > 500 && height < 500)
    {
        windowSize.x = width;
        windowSize.y = 501;
    }
    else
    {
        windowSize.x = width;
        windowSize.y = height;
    }
    window_->setSize(windowSize);
    window_->setView(sf::View(sf::FloatRect(0, 0, windowSize.x, windowSize.y)));
    drawFlock(flock_, window_);
}
