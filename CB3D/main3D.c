#include <GL/glut.h>
//#include <math.h>

//Global variables for init
int advance=0, anim=1;

//View parameters
float vx=150, vy=-50, vz=20, rx, ry, rz, elev, azim;
float d_lat, d_fro, d_azim, d_ver, m_d_fro; //desplazamientos lateral, frontal y vertical
//mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;
//Colors and position
static GLfloat	blue[] =   { 0.3, 0.3, 1.0 };	//azul
static GLfloat	white[] = { 0.2, 0.2, 0.2 };	//blanco
static GLfloat	fullwhite[]={1.0, 1.0, 1.0 };

static GLfloat	cooper[] =  { 0.75, 0.4, 0.0 };
static GLfloat	gold[] =    { 0.7, 0.6, 0.0 };

static GLfloat pos[4] = {120.0, 120.0, 10.0, 1.0};

void init3D( void );
void loop( void );
void vision( void );
void draw( void );
void reshape( int ancho, int alto );
void keyboard( unsigned char key, int x, int y);
void mouse( int button, int state, int x, int y);
void move( int x, int y );
void createMenu();
void menu(int value);

//Función principal, inicializa gráficos
int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH  );
	glutInitWindowSize( 1024, 700 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Skeleton" );
	createMenu();
	init3D();

	glutDisplayFunc( draw );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	glutMotionFunc( move );
	glutIdleFunc( loop );
	glutMainLoop( );
}
void menu(int value)
{
    switch( value ) {
        case 1:
            // Handle menu item 1
            anim = !anim;
            break;
        case 2:
            // Handle menu item 2
            break;
        case 3:
            // Handle menu item 3
            break;
        case 4:
            exit(0);  // Quit the program
            break;
    }
}
void createMenu()
{
    glutCreateMenu( menu );
    glutAddMenuEntry( "Start/Stop", 1 );
    glutAddMenuEntry( "Menu Item 2", 2 );
    glutAddMenuEntry( "Menu Item 3", 3 );
    glutAddMenuEntry( "Quit", 4 );
    glutAttachMenu( GLUT_RIGHT_BUTTON );  // Attach the menu to the right mouse button
}
void init3D()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glClearColor( 0.84,0.925,0.933, 0.0 );
	glClearColor( 0.2,0.2,0.2, 0.0 );

	//glEnable(GL_NORMALIZE);
}
//Función que será invocada cada vez que haya que redibujar

void loop( void )
{
	if( anim )
		advance++;
	vision();
	draw();
	Sleep( 20 );//miliseconds
}

void vision( void )
{
	//adjust navigation with mouse
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//grid
	glNormal3f( 0.0, 0.0, 1.0 );

	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue );
	glMaterialfv( GL_FRONT, GL_SPECULAR, fullwhite );
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

	glPushMatrix();

	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gold );
	glTranslated( 150, 150, 0 );
	glRotatef( advance, 0.0, 0.0, 1.0 );
	glRotated( 90.0, 1.0, 0.0, 0.0 );
	glutSolidTeapot( 20.0 );
	//glLineWidth(2.0);
	//glRotatef( advance, 0.0, 0.0, 1.0 );
	//glutWireSphere( 50.0, 12, 12 );

	glPopMatrix();

	glPushMatrix();
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cooper );
	glTranslated( 100, 100, 0 );
	glRotatef( advance, 0.0, 0.0, 1.0 );
	glRotated( 90.0, 1.0, 0.0, 0.0 );
	glutSolidTeapot( 20.0 );
	//glutSolidSphere( 100.0, 60, 60 );
	glPopMatrix();

	glPushMatrix();
	glTranslated( 120, 120, 10 );
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white );
	glDisable( GL_LIGHTING );
	glutSolidSphere( 2.0, 10, 10 );
	glEnable( GL_LIGHTING );
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int width, int height )
{
	glViewport(0, 0, width, height );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, (float)width/(float)height, 1.0, 800.0 );
	//gluPerspective( 45.0, 1.0, 1.0, 800.0 );
	glMatrixMode( GL_MODELVIEW );
}
//------------------------------------------------------------------
//Keyboard handling
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

void move( int x, int y )
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





