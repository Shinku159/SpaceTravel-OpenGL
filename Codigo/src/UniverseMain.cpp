//LIBRARIES ===========================
#include <glm/gtc/matrix_transform.hpp>
#include "../lib/dataInitializer.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../lib/utils.h"
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
//=====================================

/**
 * @file UniverseMain.cpp
 * The main file for generating the
 * aplication universe.
 *
 *  Projeto Final de Computação Gráffica -
 *          Space Explorer
 *  
 * @author Leonardo Vieira Ferreira - 2018009799
 * @author Lucas Praça de Souza - 2018013138
 * @author Thiago Silva Pereira - 2018008209
 * 
 * @date 06/12/2020
 */

/* === GLOBAL VARIABLES === */
/*Display Config*/
int win_width  = 800; //display window width (Changeable)
int win_height = 600; //display window height (Changeable)
int program; //Drawing programs (shaders)

/*Stars Config*/
#define STARSNUMBER 4000 //Number of stars in the created universe  (Changeable)
unsigned int starsVA[STARSNUMBER]; //Stars Vertex Array
unsigned int starsVB[STARSNUMBER]; //Stars Vertex Buffer
float starsColors[STARSNUMBER]; //Array of colors for each star
float starsSize[STARSNUMBER]; //Array of star sizes
int colorChangeRate = 8; //rate which the stars change colors (Changeable)

/*SpaceShip Config*/
unsigned int spaceShipVA[5]; //spaceShip Vertex Array 
unsigned int spaceShipVB[5]; //spaceShip Vertex Buffer
float spx_angle = 90.0f, spy_angle = 0.0f, spz_angle = 0.0f; //SpaceShip angle controllers
float rotationInc = 2.0f; //Rotation Increment (Changeable)
int spaceShipState = 2; //Which side the ship is looking at (left, right, up and down) 
float sp_scale = 0.1f; //Size of the ship (between 0.1f - 0.2f)
int choosenSP = 4; // Index of chooseen spaceShip  

/*Cube Planets Config*/
#define CUBEPLANETSNUMBER 5 //Number of planets in the created universe  (Changeable)
unsigned int cubePlanetsVA[CUBEPLANETSNUMBER]; //planets Vertex Array
unsigned int cubePlanetsVB[CUBEPLANETSNUMBER]; //planets Vertex Buffer
float cubePlanetsPositions[CUBEPLANETSNUMBER][5]; //planets Positions & orientations
float rc_angle = 0.0f, rc_inc = 1.0f; //Planets Rotation  (Changeable)

/*Sphere Planets Config*/
#define SPHEREPLANETSNUMBER 5 //Number of planets in the created universe  (Changeable)
unsigned int spherePlanetsVA[SPHEREPLANETSNUMBER]; //planets Vertex Array
unsigned int spherePlanetsVB[SPHEREPLANETSNUMBER]; //planets Vertex Buffer
float spherePlanetsPositions[SPHEREPLANETSNUMBER][3]; //planets Positions & orientations
float rs_angle = 0.0f, rs_inc = 1.0f; //Planets Rotation (Changeable)
int vertices; //number of vertices in the sphere

/*Pyramid Planets Config*/
#define PYRAMIDPLANETSNUMBER 5 //Number of planets in the created universe  (Changeable)
unsigned int pyramidPlanetsVA[PYRAMIDPLANETSNUMBER]; //planets Vertex Array
unsigned int pyramidPlanetsVB[PYRAMIDPLANETSNUMBER]; //planets Vertex Buffer
float pyramidPlanetsPositions[PYRAMIDPLANETSNUMBER][5]; //planets Positions & orientations
float rp_angle = 0.0f, rp_inc = 1.0f; //Planets Rotation (Changeable)

/*View & Projection*/
float viewX = 0.0f, viewY = 0.0f; // Projection Viewer position (x,y)
unsigned int loc; // shader variable getter. 
int scene =  1; //Which scene should be displayed in the screen

/*Auxiliaries*/
int i;
float j, r; 

/* === Functions === */
void keyboard(unsigned char, int, int);
void universeSerach(void);
void initStarsData(void);
void changeColors(void);
void reshape(int, int);
void shipChooser(void);
void display(void);
void idle(void);

/* Scene 1 - Ship Selector */
void shipChooser(){
    // SpaceShip Definition ----------
    glBindVertexArray(spaceShipVA[choosenSP]);
    loc = glGetUniformLocation(program, "hasColor");
	glUniform1i(loc, 1);
    glm::mat4 S  = glm::scale(glm::mat4(1.0f), glm::vec3(sp_scale, sp_scale, sp_scale));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(spx_angle), glm::vec3(0.0f,0.0f,1.0f));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), glm::radians(spy_angle), glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), glm::radians(spz_angle), glm::vec3(1.0f,0.0f,0.0f));
    glm::mat4 T  = glm::translate(glm::mat4(1.0f), glm::vec3((viewX*-1),(viewY*-1),-1.0f));
    glm::mat4 model = T*Ry*Rx*Rz*S;
    loc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 12);
    // -------------------------------
}

/* Scene 0 - Main Universe */
void universeSerach(){
    // Stars Definition ----------
    loc = glGetUniformLocation(program, "hasLight");
    glUniform1i(loc, 0);
    loc = glGetUniformLocation(program, "hasColor");
	glUniform1i(loc, 0);
    for (i = 0; i < STARSNUMBER; i++){
        glPointSize(starsSize[i]);
       	glBindVertexArray(starsVA[i]);
       	glm::mat4 T  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-1.0f));
       	loc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(T));
    	j = starsColors[i];
        loc = glGetUniformLocation(program, "color");
    	glUniform3f(loc, j, j, j);
        glDrawArrays(GL_POINTS, 0, 1);
    } // ------------------------

    // SpaceShip Definition ----------
    glBindVertexArray(spaceShipVA[choosenSP]);
    loc = glGetUniformLocation(program, "hasColor");
	glUniform1i(loc, 1);
    glm::mat4 S  = glm::scale(glm::mat4(1.0f), glm::vec3(sp_scale, sp_scale, sp_scale));
    glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(spx_angle), glm::vec3(0.0f,0.0f,1.0f));
    glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), glm::radians(spy_angle), glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), glm::radians(spz_angle), glm::vec3(1.0f,0.0f,0.0f));
    glm::mat4 T  = glm::translate(glm::mat4(1.0f), glm::vec3((viewX*-1),(viewY*-1),-1.0f));
    glm::mat4 model = T*Ry*Rx*Rz*S;
    loc = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
    glDrawArrays(GL_TRIANGLES, 0, 12);
    // -------------------------------

    // Planets Definition ----------
    loc = glGetUniformLocation(program, "hasLight");
    glUniform1i(loc, 1);
    loc = glGetUniformLocation(program, "lightColor");
    glUniform3f(loc, 1.0, 1.0, 1.0);
    loc = glGetUniformLocation(program, "lightPosition");
    glUniform3f(loc, (viewX*-1),(viewY*-1),-1.0f);
    loc = glGetUniformLocation(program, "cameraPosition");
    glUniform3f(loc,viewX,viewY,0.0f);
    for (i = 0; i < CUBEPLANETSNUMBER; i++){
       	glBindVertexArray(cubePlanetsVA[i]);
       	glm::mat4 T  = glm::translate(glm::mat4(1.0f), glm::vec3(cubePlanetsPositions[i][0], cubePlanetsPositions[i][1],-5.0f));
        Rz = glm::rotate(glm::mat4(1.0f), glm::radians(cubePlanetsPositions[i][2]), glm::vec3(0.0f,0.0f,1.0f));
        Ry = glm::rotate(glm::mat4(1.0f), glm::radians(cubePlanetsPositions[i][3]), glm::vec3(0.0f,1.0f,0.0f));
        Rx = glm::rotate(glm::mat4(1.0f), glm::radians(cubePlanetsPositions[i][4]), glm::vec3(1.0f,0.0f,0.0f));
        if((i % 2) == 0) Ry = glm::rotate(glm::mat4(1.0f), glm::radians(rc_angle), glm::vec3(0.0f,1.0f,0.0f));
        glm::mat4 model = T*Rz*Ry*Rx;
       	loc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    } // ------------------------

    // Sphere Planets Definition ----------
    for (i = 0; i < SPHEREPLANETSNUMBER; i++){
       	glBindVertexArray(spherePlanetsVA[i]);
       	glm::mat4 T  = glm::translate(glm::mat4(1.0f), glm::vec3(spherePlanetsPositions[i][0], spherePlanetsPositions[i][1],-5.0f));
        Ry = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(0.0f,1.0f,0.0f));
        if((i % 2) == 0) Ry = glm::rotate(glm::mat4(1.0f), glm::radians(rs_angle), glm::vec3(0.0f,1.0f,0.0f));
        glm::mat4 S  = glm::scale(glm::mat4(1.0f), glm::vec3(spherePlanetsPositions[i][2], spherePlanetsPositions[i][2], spherePlanetsPositions[i][2]));
        glm::mat4 model = T*Ry*S;
       	loc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, vertices);
    } // ------------------------

    // Pyramid Planets Definition ----------
    for (i = 0; i < PYRAMIDPLANETSNUMBER; i++){
       	glBindVertexArray(pyramidPlanetsVA[i]);
       	glm::mat4 T  = glm::translate(glm::mat4(1.0f), glm::vec3(pyramidPlanetsPositions[i][0], pyramidPlanetsPositions[i][1],-5.0f));
        Rz = glm::rotate(glm::mat4(1.0f), glm::radians(pyramidPlanetsPositions[i][2]), glm::vec3(0.0f,0.0f,1.0f));
        Ry = glm::rotate(glm::mat4(1.0f), glm::radians(pyramidPlanetsPositions[i][3]), glm::vec3(0.0f,1.0f,0.0f));
        Rx = glm::rotate(glm::mat4(1.0f), glm::radians(pyramidPlanetsPositions[i][4]), glm::vec3(1.0f,0.0f,0.0f));
        if((i % 2) == 0) Ry = glm::rotate(glm::mat4(1.0f), glm::radians(rp_angle), glm::vec3(0.0f,1.0f,0.0f));
        glm::mat4 model = T*Ry;
       	loc = glGetUniformLocation(program, "model");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 18);
    } // ------------------------
}

/* Display Function */
void display(){
    //Clear
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Projection Definition ----------
    glUseProgram(program);
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), (win_width/(float)win_height), 0.1f, 100.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(viewX,viewY,0.0f));
    loc = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
    loc = glGetUniformLocation(program, "projection");
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
    // -----------------------------

    if(scene) shipChooser(); // Ship Selector
    else universeSerach(); // Main Universe 

	glutSwapBuffers();
}

/* Window Reshape Function */
void reshape(int width, int height){
    win_width = width;
    win_height = height;
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

/* KeyBoard Controler */
void keyboard(unsigned char key, int x, int y){
    if(scene){
    switch (key){
        case 27: 
            exit(0); //Esc Key to exit
        case 13:
            scene = 0; //Enter to start universe simulation with choosen SpaceShip
            break;
        case 'a':
        case 'A':
            choosenSP -= ((choosenSP-1) >= 0 ? 1 : 0); //Changes the spaceship (-1)
            break;
        case 'd':
        case 'D':
            choosenSP += ((choosenSP+1) <= 4 ? 1 : 0); //Changes the spaceship (+1)
            break;
        case 'w':
        case 'W':
            sp_scale += ((sp_scale+0.05f) <= 0.2f ? 0.05f : 0); //Changes the spaceship Size (+1)
            break;
        case 's':
        case 'S':
            sp_scale -= ((sp_scale-0.05f) >= 0.1f ? 0.05f : 0); //Changes the spaceship Size (-1)
            break;
    }}
    else{
    switch (key){
        case 27: 
            exit(0); //Esc Key to exit
        case 'w':
        case 'W':
        	viewY -= ((viewY-0.1) >= -10 ? 0.1 : 0); //View port Up
            if(spaceShipState != 0){
	        	spx_angle = 0.0f;
                spz_angle = 0.0f;
	            spaceShipState = 0;
        	}
        	break;
        case 'a':
        case 'A':
        	viewX += ((viewX+0.1) <= 10 ? 0.1 : 0); //View port Left
            if(spaceShipState != 2){
	        	spx_angle = 90.0f;
	            spy_angle = 0.0f;
	            spaceShipState = 2;
        	}
        	break;
        case 's':
        case 'S':
 	       	viewY += ((viewY+0.1) <= 10 ? 0.1 : 0); //View port Down
            if(spaceShipState != 1){
	        	spx_angle = 180.0f;
                spz_angle = 0.0f;
	            spaceShipState = 1;
        	}
        	break;
    	case 'd':
        case 'D':
        	viewX -= ((viewX-0.1) >= -10 ? 0.1 : 0); //View port Right
            if(spaceShipState != 3){
	        	spx_angle = 270.0f;
                spy_angle = 0.0f;
	            spaceShipState = 3;
        	}
        	break;
    }}
	glutPostRedisplay();
}

/* Change Stars Colors*/
void changeStarsColors(){
    for(int i = 0;i < STARSNUMBER; i++){
        if((rand() % 10) == 0)
            starsColors[i] = ((float)rand()/(float)(RAND_MAX));
    }
}

/* Idle State Actions*/
void idle() {
    //Stars colors handler ---
    int x = rand() % colorChangeRate;
	if(x == 0)
    	changeStarsColors();
    // -----------------------

    //SpaceShip rotation handler ---
    if(scene) r = 0.1f;
    else r = rotationInc;
    if(spaceShipState == 2 || spaceShipState == 3)
    	spz_angle = ((spz_angle+r) < 360.0f) ? spz_angle+r : 360.0-spz_angle+r;
    else
    	spy_angle = ((spy_angle+r) < 360.0f) ? spy_angle+r : 360.0-spy_angle+r;
    // -----------------------------

    //Planets rotation handler ---
    rc_angle = ((rc_angle+rc_inc) < 360.0f) ? rc_angle+rc_inc : 360.0-rc_angle+rc_inc;
    rs_angle = ((rs_angle+rs_inc) < 360.0f) ? rs_angle+rs_inc : 360.0-rs_angle+rs_inc;
    rp_angle = ((rp_angle+rp_inc) < 360.0f) ? rp_angle+rp_inc : 360.0-rp_angle+rp_inc;
    // ---------------------------
    glutPostRedisplay();
}

/* ===== MAIN ===== */
int main(int argc, char *argv[]){ 
    //glut inicialization and config
    glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    //window inicialization
	glutInitWindowSize(win_width,win_height);
	glutCreateWindow(argv[0]);

    //Glew Inicialization
	glewExperimental = GL_TRUE;
	glewInit();

    //Data & Shaders
	initStarsData(starsVA, starsVB, starsColors, starsSize, STARSNUMBER); //Stars Data inicialization
    for(i = 0; i < 5; i++){
    initSpaceShip(&spaceShipVA[i], &spaceShipVB[i], i);} //starShip Data inicialization
    glEnable(GL_DEPTH_TEST); //Enable projection
    for(i = 0; i < CUBEPLANETSNUMBER; i++){
    initPlanet(&cubePlanetsVA[i], &cubePlanetsVB[i], cubePlanetsPositions[i], ((((float)rand()/(float)(RAND_MAX)) * 28) - 14), ((((float)rand()/(float)(RAND_MAX)) * 28) - 14), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)));} // Make cubeplanets
    for(i = 0; i < SPHEREPLANETSNUMBER; i++){
    initSpherePlanet(&spherePlanetsVA[i], &spherePlanetsVB[i], spherePlanetsPositions[i], ((((float)rand()/(float)(RAND_MAX)) * 28) - 14), ((((float)rand()/(float)(RAND_MAX)) * 28) - 14), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)), (((float)rand()/(float)(RAND_MAX) * 2) -1), &vertices);} // Make sphereplanets
    for(i = 0; i < PYRAMIDPLANETSNUMBER; i++){
    initPyramidPlanet(&pyramidPlanetsVA[i], &pyramidPlanetsVB[i], pyramidPlanetsPositions[i], ((((float)rand()/(float)(RAND_MAX)) * 28) - 14), ((((float)rand()/(float)(RAND_MAX)) * 28) - 14), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)), ((float)rand()/(float)(RAND_MAX)));} // Make pyramidsplanets
    program = createShaderProgram();// Create shaders.

    //Glut Functions and Main Loop
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

	glutMainLoop();

    return EXIT_SUCCESS;
}