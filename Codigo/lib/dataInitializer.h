#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <string.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

//Initialize the stars data.
void initStarsData (unsigned int VAO[], unsigned int VBO[], float color[], float size[], int starNumber);

//Initialize the starShip data
void initSpaceShip (unsigned int *VAO, unsigned int *VBO, int color); 

//Initialize the cube planets data
void initPlanet(unsigned int *VAO, unsigned int *VBO, float positions[], float x, float y, float R, float G, float B, float size);

//Initialize the sphere planets data
void initSpherePlanet(unsigned int *VAO, unsigned int *VBO, float positions[], float x, float y, float R, float G, float B, float size, int *vertices);

//Initialize the pyramid planets data
void initPyramidPlanet(unsigned int *VAO, unsigned int *VBO, float positions[], float x, float y, float R, float G, float B, float size);
