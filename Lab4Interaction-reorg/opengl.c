#include "main.h"
//Variables for initializing process
int advance=0, anim=1, alias=1;
int orthox1=-100, orthoy1=-100, orthox2=100, orthoy2=100;

//local prototypes


void intitWindow(int argc, char **argv)
{
    glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 1000, 1000 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "2D Application with Menu" );

	//createMenu();

}
void init3D()
{
	glClearColor( 0.84,0.925,0.933, 0.0 );
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH );
	glEnable(GL_POLYGON_SMOOTH );
	glEnable(GL_BLEND );
}

void draw()
{
    glClear( GL_COLOR_BUFFER_BIT );
    game();
    glutSwapBuffers();
}
//Callback, when a reshape happened
void reshape(int width, int height )
{
	glViewport(0, 0, width, height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D( orthox1, orthox2, orthoy1, orthoy2 );

	glMatrixMode( GL_MODELVIEW );
}
