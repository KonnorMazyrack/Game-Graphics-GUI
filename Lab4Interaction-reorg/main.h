#include	<GL/glut.h>

//main globals
extern float steerAngle;
extern void game();  //to draw general scenery of the game

//Models
extern void car();
extern void house();

//OpenGL globals and functions
extern int advance, anim, alias;
extern int orthox1, orthoy1, orthox2, orthoy2;
//void initWindow(int argc, char **argv);
extern void init3D();
//extern void defineCallbacks();
extern void draw();
extern void reshape();
