#include	<GL/glut.h>
#include <SOIL/SOIL.h>

//main globals
extern float steerAngle;
extern void game(); //To draw general scenery of the game
extern void gameKeys( unsigned char key );
extern void resetGame();
extern void carAccel( float acc );
extern void carSteer( float ste );
extern float carAngle, steerAngle;
extern float carX, carY, carSpeed;	//Later will be moved to float

//Models
extern void car();
extern void house();

//OpenGL globals and functions
extern int advance, anim, alias;
extern int orthox1, orthoy1, orthox2, orthoy2;
//extern void initWindow( int argc, char **argv );
extern void init3D();

extern void defineCallbacks();
extern void glutPrintBM(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue );
extern void glutPrintSt(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue );

