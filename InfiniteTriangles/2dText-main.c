#include	<GL/glut.h>
//#include    <cmath>
//Variables for initializing process
int time=0, anim=1;
float M_PI = 3.14159265;
int orthox1=-100, orthoy1=-100, orthox2=100, orthoy2=100;

//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;
//Colors
static GLfloat  rojo[] = { 1.0, 0.0, 0.0 };   //rojo
static GLfloat purple[] = { 1.0, 0.0, 1.0 };

void init3D( void );
void loop( void );
void vision( void );
void draw( void );
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void movement( int x, int y );
void draw1stTriangle();
void draw2ndTriangle();

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
		time++;
		draw();
	}
	Sleep( 20 );//miliseconds
}

void draw()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();

    glColor3fv( rojo );

    glLineWidth( 4.0 );

    glLoadIdentity();
    glScalef( 100.0, 100.0, 1.0 );

    glColor3fv( rojo );

    drawCircle(0.0, 0.0, 0.3, 100);

	glutSwapBuffers();
}
void drawCircle(float centerX, float centerY, float radius, int segments)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++)
    {
        float theta = 2.0f * M_PI * ((float)i) / ((float)segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(centerX + x, centerY +y);
    }
    glEnd();
}
void draw2ndTriangle()
{
    GLfloat triangleVertices[] = {
        -0.5f, -0.5f, 0.0f, // Vertex 1
        0.5f, -0.5f, 0.0f,  // Vertex 2
        0.0f, 0.5f, 0.0f    // Vertex 3
    };

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 3; i++)
        glVertex2f(triangleVertices[i * 3 + 0], triangleVertices[i * 3 + 1]);
    glEnd();
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



