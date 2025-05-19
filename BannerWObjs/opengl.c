#include "main.h"

//Prototypes
void draw();
void loop( void );
void vision( void );
void reshape(int width, int height );
void keyboard( unsigned char key, int x, int y );
void mouse( int button, int state, int x, int y );
void movement( int x, int y );
//globals
int advance=0;
//Vision parameters
float vx=150, vy=-50, vz=60, rx, ry, rz, elev, azim;
float d_lat, d_fro, d_azim, d_ver, m_d_fro; //desplazamientos lateral, frontal y vertical
//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;





void initWindow( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  );
	glutInitWindowSize( 1024, 700 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "3D Template" );

}
void init3D()
{
	//glEnable( GL_LIGHTING );
	//glEnable( GL_LIGHT0 );
	//glEnable( GL_LIGHT1 );
	glEnable( GL_DEPTH_TEST );
	//glClearColor( 0.84,0.925,0.933, 0.0 );
	glClearColor( 0.2,0.2,0.2, 0.0 );

	glEnable(GL_NORMALIZE);
}

void defineCallbacks()
{
	glutDisplayFunc( draw );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	glutMotionFunc( movement );
	glutIdleFunc( loop );
}
void draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt( vx, vy, vz,   rx, ry, rz,  0.0, 0.0, 1.0 );
//gluLookAt( 0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f );
	game();

	glutSwapBuffers();
}

void loop( void )
{
	advance++;
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

//Callbacks
void reshape(int width, int height )
{
	glViewport(0, 0, width, height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, (float)width/(float)height, 10.0, 800.0 );
	//gluPerspective( 45.0, 1.0, 1.0, 800.0 );

	glMatrixMode( GL_MODELVIEW );
}

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
		vz += (float)(mn_y0-y)*1.0;
	if( mouse_left )
	{
        azim+=(float)(x-mn_x0)*0.01;
	    vx +=  d_lat * cos( azim ) + ( d_fro +  (float)(mn_y0-y)*1.0   ) * sin( azim );
		vy += -d_lat * sin( azim ) + ( d_fro +  (float)(mn_y0-y)*1.0   ) * cos( azim );
	}
	mn_x0=x;
	mn_y0=y;
}

