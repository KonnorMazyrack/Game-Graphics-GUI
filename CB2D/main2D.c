#include	<GL/glut.h>

//Variables for initializing process
int advance=0, anim=1;
int orthox1=-100, orthoy1=-100, orthox2=100, orthoy2=100;

//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;
//Colors
static GLfloat  red[] = { 1.0, 0.0, 0.0 };

void init3D( void );
void loop( void );
void vision( void );
void draw( void );
void reshape(int ancho, int alto );
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void movement( int x, int y );
void createMenu();
void menu(int value);

//Main, initialize and go to the idle loop
int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 1024, 700 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "2D Application with Menu" );
	createMenu();
	init3D();

	glutDisplayFunc( draw );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	glutMotionFunc( movement );
	glutIdleFunc( loop );
	glutMainLoop( );
}
void menu(int value)
{
    switch( value ) {
        case 1:
            // Handle menu item 1
            anim=!anim;
            break;
        case 2:
            // Handle menu item 2
            glClearColor( 1.0,1.0,1.0, 0.0 );
            break;
        case 3:
            // Handle menu item 3
            glClearColor( 0.0,0.0,0.0, 0.0 );
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
    glutAddMenuEntry( "White background", 2 );
    glutAddMenuEntry( "Black background", 3 );
    glutAddMenuEntry( "Quit", 4 );
    glutAttachMenu( GLUT_RIGHT_BUTTON );  // Attach the menu to the right mouse button
}
void init3D()
{
	glClearColor( 0.84,0.925,0.933, 0.0 );
}
//Function for the animation

void loop( void )
{
	if( anim ){
		advance++;
		draw();
	}
	Sleep( 20 );//milisegundos
}
//Redraw scene
void draw()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();

    glColor3fv( red );

    glLineWidth( 4.0 );
    glRotatef( advance, 0.0, 0.0, 1.0 );
    glBegin( GL_LINES );
     glVertex2d( -50, -50 );
     glVertex2d( 50,50 );
     glVertex2d( -50, 50 );
     glVertex2d( 50,-50 );
    glEnd();

	glutSwapBuffers();
}

void reshape(int ancho, int alto )
{
	glViewport(0, 0, ancho, alto );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D( orthox1, orthox2, orthoy1, orthoy2 );

	glMatrixMode( GL_MODELVIEW );
}
//------------------------------------------------------------------
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
	{
		orthox1 -= mn_x0-x;
        orthox2 += mn_x0-x;
        orthoy1 -= mn_x0-x;
        orthoy2 += mn_x0-x;
    }
	if( mouse_left )
	{
        orthox1 += mn_x0-x;
        orthox2 += mn_x0-x;
        orthoy1 -= mn_y0-y;
        orthoy2 -= mn_y0-y;
	}
	mn_x0=x;
	mn_y0=y;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluOrtho2D( orthox1, orthox2, orthoy1, orthoy2 );
	glMatrixMode( GL_MODELVIEW );
}





