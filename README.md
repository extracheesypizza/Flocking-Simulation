# Flocking Simulation
![](res/preview.gif)

In order to travel and survive, birds and animals form flocks. Flocks require coordination within themselves and within individual creatures. This application models the [behavioural pattern] of so called ['Boids'] such that they form beautiful flocks. 

## How to build
1. ```git clone``` the repository
2. Run  ```git submodule init && git submodule update``` to download the SFML Library (it will take some time and may seem stuck, but be patient)
3. For Windows run ```cmake -S . -B build/ -G "MinGW Makefiles" -DBUILD_SHARED_LIBS=OFF && cd build && make && .\FlockingSimulation```
4. For MacOS/Linux run ```cmake -S . -B build/ -DBUILD_SHARED_LIBS=OFF && cd build && make && ./FlockingSimulation```

## How to use:
- Upon launching the app you will be greeted with Boids forming a neat title screen saying "Flock".
- Now, to temporarily stop their idyllic existence, press 'Spacebar' and watch them fly off in random directions and form flocks! You may press 'Spacebar' as many times as you wish and the Boids will always line up into flocks.


[behavioural pattern]: <https://www.red3d.com/cwr/boids/>
['Boids']: <https://en.wikipedia.org/wiki/Boids>

