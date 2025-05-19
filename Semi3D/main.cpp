//#define GLUT_DISABLE_ATEXIT_HACK
#include "importObj.h"
#include <GL/glut.h>
#include <windows.h>
#include <math.h>

//#include <math.h>
#define LIGHT_POSX 120.0f
#define LIGHT_POSY 120.0f
#define LIGHT_POSZ 120.0f

using namespace std;

//Init variables
int animAdvance=0;

//Car
float carAngle=0.0f, steerAngle=0.0f;
float carX=0.0f, carY=0.0f, carSpeed=0.0f;	//Later will be moved to float

//Vision parameters
float vx=150, vy=-50, vz=20, rx, ry, rz, elev, azim;
float d_lat, d_fro, d_azim, d_ver, m_d_fro; //desplazamientos lateral, frontal y vertical
//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;
//Colors and position
static GLfloat	blue[] =   { 0.3f, 0.3f, 1.0f };	//blue
static GLfloat	white[] = { 0.2f, 0.2f, 0.2f };	//white
static GLfloat	whitefull[]={1.0f, 1.0f, 1.0f };

static GLfloat	cooper[] =  { 0.75f, 0.4f, 0.0f };
static GLfloat	gold[] =    { 0.7f, 0.6f, 0.0f };

static GLfloat pos[4] = { LIGHT_POSX, LIGHT_POSY, LIGHT_POSZ, 1.0f }; //position. 0.0 for infinite

vector<Vertex> vertices;
vector<TextureCoord> texCoords;
vector<Normal> normals;
vector<Face> faces;

void init3D( void );
void loop( void );
void vision( void );
void draw( void );
void reshape(int width, int height );
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void movement( int x, int y );

//Main function, initialize graphics
int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  );
	glutInitWindowSize( 1024, 700 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "3D Template" );
	init3D();

	glutDisplayFunc( draw );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	glutMotionFunc( movement );
	glutIdleFunc( loop );
	//glutIdleFunc( 0 );
	glutMainLoop( );
}
void init3D()
{
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_DEPTH_TEST );
	glClearColor( 0.2,0.2,0.2, 0.0 );

	glEnable(GL_NORMALIZE);
	//if (loadOBJ( "basicCube.obj", vertices, texCoords, normals, faces ) )
	if( loadOBJ( "Car.obj", vertices, texCoords, normals, faces ) )
		;//showObjInfo( vertices, texCoords, normals, faces );
}
//Loop function for the animation

void loop( void )
{
	animAdvance++;
	vision();
	draw();
	Sleep( 20 );//miliseconds
}

void vision( void )
{
	//For mouse navigation
	d_fro+=m_d_fro;

	azim += d_azim;
	vx += d_lat * cos( azim ) + d_fro * sin( azim );
	vy += -d_lat * sin( azim ) + d_fro * cos( azim );
	vz += d_ver;

	rx = vx + 10.0 * sin( azim );
	ry = vy + 10.0 * cos( azim );
	rz = vz * 0.95;
}

void draw()
{
	int	x, y;
	glLightfv( GL_LIGHT0, GL_POSITION, pos ); //needed here

	glLoadIdentity();
	gluLookAt( vx, vy, vz,   rx, ry, rz,  0.0, 0.0, 1.0 );

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//Grid
	glNormal3f( 0.0, 0.0, 1.0 );

	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue );
	glMaterialfv( GL_FRONT, GL_SPECULAR, whitefull );
	glMaterialf( GL_FRONT, GL_SHININESS, 50 );
	glLineWidth(1.0);
	glBegin( GL_LINES );
	for ( x = 0; x <= 300; x += 10 ) {
		glVertex3d( x, 0, 0 );
		glVertex3d( x, 300, 0 );
	}

	for ( y = 0; y <= 300; y += 10 ) {
		glVertex3f( 0, y, 0 );
		glVertex3f( 300, y, 0 );
	}
	glEnd();

	//Gold teapot
	//glPushMatrix();

	//glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gold );
	//glTranslated( 200, 200, 0 );
	//glRotatef( animAdvance, 0.0, 0.0, 1.0 );
	//glRotated( 90.0, 1.0, 0.0, 0.0 );
	//glutSolidTeapot( 20.0 );
	//glPopMatrix();

	//Cooper model
	glPushMatrix();
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cooper );
	glTranslated( 100, 100, 0 );
	//glRotated( animAdvance, 0.0, 0.0, 1.0 );
	glRotated( 90.0, 1.0, 0.0, 0.0 );
	//glRotated( 0, 0, 0, 1.0);

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

	glScalef( 1.0, 1.0, 1.0 );
	drawModel( vertices, texCoords, normals, faces );
	glPopMatrix();

	//Light source (just to indicate position, not really needed
	glPushMatrix();
	glTranslatef( LIGHT_POSX, LIGHT_POSY, LIGHT_POSZ );
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white );
	glDisable( GL_LIGHTING );
	glutSolidSphere( 2.0, 10, 10 );
	glEnable( GL_LIGHTING );
	glPopMatrix();

	glutSwapBuffers();
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
	if( steerAngle>12.0f ) steerAngle=12.0f;
	if( steerAngle<-12.0f ) steerAngle=-12.0f;
}

void gameKeys( unsigned char key )
{
	switch( toupper( key ) )
	{
	case 'W':		//increase speed
		carAccel( 0.05f );
		break;
	case 'S':
		carAccel( -0.05f );
		break;
	case 'A':
		carSteer( 2.0f );
		break;
	case 'D':
		carSteer( -2.0f );
		break;
	}
}

void reshape(int width, int height )
{
	glViewport(0, 0, width, height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, (float)width/(float)height, 10.0, 800.0 );
	//gluPerspective( 45.0, 1.0, 1.0, 800.0 );

	glMatrixMode( GL_MODELVIEW );
}
//------------------------------------------------------------------
//Keyboard actions
void keyboard( unsigned char key, int x, int y )
{
	switch( toupper( key ) )
	{
	case 27:
		exit( 0 );
		break;
	default:
		;
	}
}

void mouse( int button, int state, int x, int y )
{
	if( state==GLUT_DOWN )
	{
		mn_x0=x;
		mn_y0=y;
		mouse_left = ( button==GLUT_LEFT_BUTTON?1:0 );
		mouse_right = ( button==GLUT_RIGHT_BUTTON?1:0 );
	}
	if( state==GLUT_UP )
		mouse_left=mouse_right=0;
}

void movement( int x, int y )
{
	if( mouse_right )
		//vz += (float)(mn_y0-y)*1.0;
		carAccel( (mn_y0-y)/200.0f );
	if( mouse_left )
	{
        //azim+=(float)(x-mn_x0)*0.01;
        carSteer( (mn_x0-x)/20.0f );
	    //vx +=  d_lat * cos( azim ) + ( d_fro +  (float)(mn_y0-y)*1.0   ) * sin( azim );
		//vy += -d_lat * sin( azim ) + ( d_fro +  (float)(mn_y0-y)*1.0   ) * cos( azim );
	}
	mn_x0=x;
	mn_y0=y;
}





