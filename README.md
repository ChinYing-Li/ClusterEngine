# OpenGL-kart
***Under construction!!!***

A kart-game written in C++, using OpenGL as the graphics API.
This project served as a means to learn OpenGL and GLSL, but  I ended (happily) up learning many gamedev techniques. And, yes, **OpenGL-kart** is gonna look like Super Mario Kart, my childhood favorite.

Gilbert–Johnson–Keerthi distance algorithm is used for collision detection between convex shapes.
QuickHull algorithm is used for creating the convex hull of objects.

## Dependencies

 - [GLEW](http://glew.sourceforge.net/)
 - [GLFW](https://www.glfw.org/](https://www.glfw.org/))
 - [GLM](https://glm.g-truc.net/0.9.9/index.html)
 - [Doxygen](https://www.doxygen.nl/index.html)

## Installation
### MacOSX (untested)

 1. Navigate to the directory where you want the game to be installed using command line
 2. ```git clone https://github.com/ChinYing-Li/OpenGL-cart.git```
 3. ```cd OpenGL-cart```
 4. ```mkdir build```
 5. ```cd build```
 6. ```cmake ..```
 7. ```make```

### Windows (untested)

TO BE UPDATED

## Backfill list
**High priority**

 - [ ] Test the lighting shaders
 - [ ] Complete the user kart control in all game states
 - [ ] Add documentation

**low priority**

 - [ ] Support height map
 - [ ] Add different scenes
