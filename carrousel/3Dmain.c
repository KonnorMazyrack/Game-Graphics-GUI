//#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
//#include <math.h>
#define LIGHT_POSX 120.0f
#define LIGHT_POSY 120.0f
#define LIGHT_POSZ 120.0f
//Init variables
int advance=0;

//Vision parameters
float vx=150, vy=-50, vz=20, rx, ry, rz, elev, azim;
float d_lat, d_fro, d_azim, d_ver, m_d_fro; //desplazamientos lateral, frontal y vertical
//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;
//Colors and position
static GLfloat	blue[] =   { 0.3f, 0.3f, 1.0f };	//blue
static GLfloat	white[] = { 0.2f, 0.2f, 0.2f };	//white
//static GLfloat  red[] =   { 1.0, 0.0, 0.0 };	//red
//static GLfloat  red2[] =   { 0.2, 0.0, 0.0 };	//red2
static GLfloat	whitefull[]={1.0f, 1.0f, 1.0f };

static GLfloat	cooper[] =  { 0.75f, 0.4f, 0.0f };
static GLfloat	gold[] =    { 0.7f, 0.6f, 0.0f };
static GLfloat  brown[] = {0.6f, 0.4f, 0.2f};
static GLfloat  green[] = {0.0f, 0.8f, 0.0f};

static GLfloat pos[4] = { LIGHT_POSX, LIGHT_POSY, LIGHT_POSZ, 1.0f }; //position. 0.0 for infinite
static GLfloat pos1[4] = { 50.0f, 50.0f, 50.0f, 1.0f};

void init3D( void );
void loop( void );
void vision( void );
void draw( void );
void reshape(int ancho, int alto );
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
	glutMainLoop( );
}
void init3D()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	//glClearColor( 0.84,0.925,0.933, 0.0 );
	glClearColor( 0.2,0.2,0.2, 0.0 );

	glEnable(GL_NORMALIZE);
}
//Loop function for the animation

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

void draw()
{
	int	x, y, tpColor = 0;
	glLightfv( GL_LIGHT0, GL_POSITION, pos ); //needed here
	glLightfv( GL_LIGHT1, GL_POSITION, pos1 );


	glLoadIdentity();
	gluLookAt( vx, vy, vz,   rx, ry, rz,  0.0, 0.0, 1.0 );


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green );
	glPushMatrix();
	//translate to the center
	glTranslated( 150, 150, 0 );
	//Repeat N times
	glRotated( advance, 0.0f, 0.0f, 1.0f );
	for(int i=0; i <= 20; i++)
    {
	//Rotate advance
        glRotated( 18, 0.0f, 0.0f, 1.0f );
	//Push
        glPushMatrix();
	//Translate in X
        glTranslated( 100, 0, 0 );
	//Draw teapot
        if (tpColor)
        {
            glTranslatef(0.0f, 0.0f, sin( advance / 10.0 ) * 5);
            glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green );
        }
        else
        {
            glTranslatef(0.0f, 0.0f, -sin( advance / 10.0 ) * 5);
            glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown );
        }
        glRotated( 90.0, 1.0, 0.0, 0.0 );
        glRotated( 90.0, 0.0, 1.0, 0.0 );
        tpColor =! tpColor;
        glScalef(5, 5, 5);
        glutSolidDodecahedron( );
	//Pop
        glPopMatrix();
    }

	glPopMatrix();

	//Gold teapot
	glPushMatrix();

	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, whitefull );
	glTranslated( 150, 150, 0 );
	glRotatef( advance, 0.0, 0.0, 1.0 );
	glRotated( 90.0, 1.0, 0.0, 0.0 );
	glutSolidTeapot( 20.0 );
	//glLineWidth(2.0);
	//glRotatef( advance, 0.0, 0.0, 1.0 );
	//glutWireSphere( 50.0, 12, 12 );
	glPopMatrix();

//	//Cooper teapot
//	glPushMatrix();
//	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green );
//	glTranslated( 100, 100, 0 );
//	glRotatef( advance, 0.0, 0.0, 1.0 );
//	glRotated( 90.0, 1.0, 0.0, 0.0 );
//	glutSolidTeapot( 20.0 );
//	//glutSolidSphere( 100.0, 60, 60 );
//	glPopMatrix();

	//Light source 0(just to indicate position, not really needed
	glPushMatrix();
	glTranslatef( LIGHT_POSX, LIGHT_POSY, LIGHT_POSZ );
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gold );
	glDisable( GL_LIGHTING );
	glutSolidSphere( 2.0, 10, 10 );
	glEnable( GL_LIGHTING );
	glPopMatrix();

	//Light source 1(just to indicate position, not really needed
	glPushMatrix();
	glTranslatef( 50.0f, 50.0f, -50.0f );
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white );
	glDisable( GL_LIGHTING );
	glutSolidSphere( 2.0, 10, 10 );
	glEnable( GL_LIGHTING );
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int ancho, int alto )
{
	glViewport(0, 0, ancho, alto );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, (float)ancho/(float)alto, 10.0, 800.0 );
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





