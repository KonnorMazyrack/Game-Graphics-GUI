#include "main.h"

//Car
float carAngle=0.0f, steerAngle=0.0f;
float carX=0.0f, carY=0.0f, carSpeed=0.0f;	//Later will be moved to float

//Colors
static GLfloat  red[] = { 1.0, 0.0, 0.0 };   //rojo
static GLfloat  purple[] = { 1.0, 0.0, 1.0 };

//Main, initialize and go to the idle loop
int main( int argc, char **argv )
{
    initWindow( argc, argv ); //without &
	init3D();
	defineCallbacks();
	glutMainLoop( );

}

void game()
{
	glLoadIdentity();
//Text data
	char message[120];
	glColor3f( 0.0, 0.0, 0.0 );
	sprintf( message, "Speed: %.1f, Angle: %.1f, Steer: %.1f", carSpeed, carAngle, steerAngle );
	glutPrintBM( -95.0, 95.0, GLUT_BITMAP_TIMES_ROMAN_24, message, 0.0, 0.4, 0.0 );

//Origin lines, for reference
	glLineWidth( 1.0 );
	glColor3f( 1.0f, 1.0f, 1.0f );
	glBegin( GL_LINES );
	 glVertex2d( -10, 0 );
	 glVertex2d( 10, 0 );
	 glVertex2d( 0, -10 );
	 glVertex2d( 0, 10 );
	glEnd();
//House
    glLineWidth( 2.0 );
    house();
    texturecity();

//Car
	//Calculate new position
	float dX=carSpeed*cos(carAngle/57.29f);
	float dY=carSpeed*sin(carAngle/57.29f);
	carX-=dX; carY-=dY;
	//Adjust angle
	carAngle+=(steerAngle/2.0)*(carSpeed/1.0);
	//Move to new position
	glTranslated( carX, carY, 0 );
	//Rotate in current angle
	glRotated( carAngle, 0.0, 0.0, 1.0 );
	glScalef( 6.0, 3.0, 1.0 );
	//glColor3f( 1.0, 0.0, 0.0 );
    //car();
    texturecar();
}
//Action keys for this application, called the from keyboard() callback.
void gameKeys( unsigned char key )
{
	switch( key )
	{
	case 'W':		//increase speed
		carAccel( 0.05f );
		break;
	case 'S':
		carAccel( -0.05f );
		break;
	case 'A':
		carSteer( 90.0f );
		break;
	case 'D':
		carSteer( -90.0f );
		break;
	}
}
//Called from keyboard() callback
void resetGame()
{
	carSpeed=0.0; carAngle=0;steerAngle=0.0;
	carX=0.0; carY=0.0;
}
//Called from movement() callback, and gameKeys()
void carAccel( float acc )
{
	carSpeed+=acc;
	if( carSpeed> 0.5f ) carSpeed=0.5f;
	if( carSpeed<-0.1f ) carSpeed=-0.1f;
}
//Called from movement() callback, and gameKeys()
void carSteer( float ste )
{
	steerAngle+=ste;
	if( steerAngle>12.0f ) steerAngle=90.0f;
	if( steerAngle<-12.0f ) steerAngle=-90.0f;
}
