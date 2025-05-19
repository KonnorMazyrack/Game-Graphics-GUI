#include	<GL/glut.h>
//#include    <math.h>
//Variables for initializing process
int advance=0, anim=1;
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
void glutPrintBM(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue );
void glutPrintSt(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue );
void car();

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
	Sleep( 20 );//miliseconds
}

void draw()
{
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();

    glColor3fv( rojo );

    glLineWidth( 4.0 );
    glRotatef( advance, 0.0, 0.0, 1.0 );
    //glBegin( GL_LINES );
     //glVertex2d( -50, -50 );
     //glVertex2d( 50,50 );
     //glVertex2d( -50, 50 );
     //glVertex2d( 50,-50 );
    //glEnd();
    //glutPrintBM( 40.0, 10.0, GLUT_BITMAP_TIMES_ROMAN_24, "To be or not to be WWiiWW", 0.0, 0.4, 0.0 );
    //glutPrintSt( 40.0, -10.0, GLUT_STROKE_ROMAN, "To be or not to be WWiiWW", 0.6, 0.4, 0.0 );

    glLoadIdentity();
    glRotatef( advance, 0.0, 0.0, 1.0 );
    glScalef( 50.0, 50.0, 1.0 );

    glPushMatrix();
    car();
    glPopMatrix();

    glColor3fv( purple );
    glPushMatrix();
    glRotatef(-3*advance, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 1.0, 0.0);
    glScalef( 2.0, 2.0, 1.0 );
    drawHouse();
    glPopMatrix();

	glutSwapBuffers();
}

void car()
{
	GLfloat carVertices[] = {
		// Car body
		-0.5f, -0.2f, 0.0f, // Vertex 1
		0.5f, -0.2f, 0.0f,  // Vertex 2
		0.5f, 0.2f, 0.0f,   // Vertex 3
		-0.5f, 0.2f, 0.0f,  // Vertex 4

		// Roof
		-0.2f, 0.2f, 0.0f,  // Vertex 5
		0.2f, 0.2f, 0.0f,   // Vertex 6
		0.0f, 0.4f, 0.0f,   // Vertex 7

		// Front left wheel
		-0.4f, -0.2f, 0.0f, // Vertex 8
		-0.3f, -0.2f, 0.0f, // Vertex 9
		-0.3f, -0.1f, 0.0f, // Vertex 10
		-0.4f, -0.1f, 0.0f, // Vertex 11

		// Front right wheel
		0.3f, -0.2f, 0.0f,  // Vertex 12
		0.4f, -0.2f, 0.0f,  // Vertex 13
		0.4f, -0.1f, 0.0f,  // Vertex 14
		0.3f, -0.1f, 0.0f,  // Vertex 15

		// Rear left wheel
		-0.4f, 0.2f, 0.0f,  // Vertex 16
		-0.3f, 0.2f, 0.0f,  // Vertex 17
		-0.3f, 0.1f, 0.0f,  // Vertex 18
		-0.4f, 0.1f, 0.0f,  // Vertex 19

		// Rear right wheel
		0.3f, 0.2f, 0.0f,   // Vertex 20
		0.4f, 0.2f, 0.0f,   // Vertex 21
		0.4f, 0.1f, 0.0f,   // Vertex 22
		0.3f, 0.1f, 0.0f    // Vertex 23
	};
	glBegin( GL_LINE_LOOP );
	for( int i=0; i<4; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
	glBegin( GL_LINE_LOOP );
	for( int i=4; i<7; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
	glBegin( GL_LINE_LOOP );
	for( int i=7; i<11; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
	glBegin( GL_LINE_LOOP );
	for( int i=11; i<15; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
		glBegin( GL_LINE_LOOP );
	for( int i=15; i<19; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
		glBegin( GL_LINE_LOOP );
	for( int i=19; i<23; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
}
void drawHouse()
{
    GLfloat houseVertices[] = {
        // House body
        -0.35f, -0.35f, 0.0f, // Vertex 1
        0.35f, -0.35f, 0.0f,  // Vertex 2
        0.35f, 0.35f, 0.0f,   // Vertex 3
        -0.35f, 0.35f, 0.0f,  // Vertex 4

        // Roof
        -0.35f, 0.35f, 0.0f,   // Vertex 5
        0.35f, 0.35f, 0.0f,    // Vertex 6
        0.0f, 0.7f, 0.0f      // Vertex 7
    };

    GLfloat windowVertices[] = {
        // Window
        -0.125f, 0.225f, 0.0f,  // Vertex 8
        0.125f, 0.225f, 0.0f,   // Vertex 9
        0.125f, 0.325f, 0.0f,   // Vertex 10
        -0.125f, 0.325f, 0.0f   // Vertex 11
    };

    GLfloat doorVertices[] = {
        // Door
        -0.125f, -0.35f, 0.0f,  // Vertex 12
        0.125f, -0.35f, 0.0f,   // Vertex 13
        0.125f, 0.0f, 0.0f,     // Vertex 14
        -0.125f, 0.0f, 0.0f     // Vertex 15
    };

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
        glVertex2f(houseVertices[i * 3 + 0], houseVertices[i * 3 + 1]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 4; i < 7; i++)
        glVertex2f(houseVertices[i * 3 + 0], houseVertices[i * 3 + 1]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
        glVertex2f(windowVertices[i * 3 + 0], windowVertices[i * 3 + 1]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
        glVertex2f(doorVertices[i * 3 + 0], doorVertices[i * 3 + 1]);
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
//Render text using bitmap
void glutPrintBM(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue )
{
    if( !text || !strlen( text ) ) return;
    glColor3f( red, green, blue );
    glRasterPos2f( x,y );
    glutBitmapString( font, text );
}
//Render text using vectors
void glutPrintSt(float x, float y, LPLC_ID font, char* text, GLfloat red, GLfloat green, GLfloat blue )
{
    if( !text || !strlen( text ) ) return;
    glColor3f( red, green, blue );
    glLineWidth( 2.0 );
    glRasterPos2f( x,y );
    glPushMatrix();
    glScalef( 0.04, 0.04, 1.0 );
    glutStrokeString( font, text );
    glPopMatrix();
}


