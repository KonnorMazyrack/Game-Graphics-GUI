#include	"main.h"
//#include    <math.h>
float carAngle=0.0f, steerAngle=0.0f;
float carX = 0.0f, carY = 0.0f, carSpeed = 0.0f,carAccel = 0.0f;
//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;
//Colors
static GLfloat  rojo[] = { 1.0, 0.0, 0.0 };   //rojo
static GLfloat purple[] = { 1.0, 0.0, 1.0 }; //purple

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
void menu(int value);
void createMenu();
void car();

//Main, initialize and go to the idle loop
int main( int argc, char **argv )
{
    //initWindow();

    glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 1000, 1000 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "2D Application with Menu" );
	//createMenu();
	init3D();

	glutDisplayFunc( draw );
	glutReshapeFunc( reshape );
	glutKeyboardFunc( keyboard );
	glutMouseFunc( mouse );
	glutMotionFunc( movement );
	//glutIdleFunc( loop );
	glutIdleFunc( 0 );
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

//Function for the animation
void loop( void )
{
	//if( anim ){
		draw();
	//}
	Sleep( 20 );//miliseconds
	advance++;
}

void game()
{
	glLoadIdentity();
//text data
	char message[120];
	glColor3f( 0.0, 0.0, 0.0 );
	sprintf( message, "Speed: %.lf, Angle: %.lf, Steer: %.1f", carSpeed, carAngle, steerAngle );
	glutPrintBM(-91.0, 95.0, GLUT_BITMAP_TIMES_ROMAN_24, message, 0.0, 0.4, 0.0 );

    glColor3fv( rojo );
    glLineWidth( 2.0 );

    glLoadIdentity();
    glPushMatrix();
    carSpeed += carAccel;
    float a = cos(carAngle/57.29)*carSpeed;
    float b = sin(carAngle/57.29)*carSpeed;
    carX += a;
    carY += b;
    glTranslatef(carX, carY, 0.0);
    glRotatef(carAngle, 0.0, 0.0, 1.0 );
    glRotated(0.0, 0.0, 0.0, 1.0);
    glScalef( 10.0, 10.0, 1.0 );
    car();
    glPopMatrix();

    //scene();
    glColor3fv( purple );
    glPopMatrix();
    //glRotatef( advance, 0.0, 0.0, 1.0 );
    glScalef( 10.0, 10.0, 1.0 );
    drawHouse();
    glPopMatrix();

}
void scene()
{
    if( advance==0 )
    {
        carX=0.0; carY=0.0; carAngle=90; carSpeed=1.0; carAccel = 0.01;
        return;
    }
    if( advance==50 )
    {
        //carX=0.0; carY=50.0;
        carAngle=0;
        //carSpeed=1.0;
        return;
    }
    if(advance == 100)
    {
        //carX=50.0; carY=50.0;
        carAngle=-90; carSpeed=2.0;
        return;
    }
    if(advance == 150)
    {
        //carX=50.0; carY=-50.0;
        carAngle=180; carSpeed=1.0;
        return;
    }
    if(advance == 200)
    {
        carAngle = 90;
        return;
    }
    if(advance == 250)
    {
        carSpeed = 0.0;
        return;
    }
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
        -0.5f, -0.2f, 0.0f, // Vertex 1
        0.5f, -0.2f, 0.0f,  // Vertex 2
        0.5f, 0.5f, 0.0f,   // Vertex 3
        -0.5f, 0.5f, 0.0f,  // Vertex 4

        // Roof
        -0.6f, 0.5f, 0.0f,  // Vertex 5
        0.6f, 0.5f, 0.0f,   // Vertex 6
        0.0f, 0.8f, 0.0f,   // Vertex 7
    };

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; i++)
        glVertex2f(houseVertices[i * 3 + 0], houseVertices[i * 3 + 1]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 4; i < 7; i++)
        glVertex2f(houseVertices[i * 3 + 0], houseVertices[i * 3 + 1]);
    glEnd();
}
//------------------------------------------------------------------
void keyboard( unsigned char key, int x, int y )
{
	switch( toupper( key ) )
	{
	case 27:
		exit( 0 );
		break;
    case ' ':
        anim != anim;
        if(anim)
            glutIdleFunc(loop);
        else
            glutIdleFunc(0);
    case 'W':
        carSpeed+= .1f;
        break;
    case 'S':
        carSpeed-= .1f;
        break;
    case 'A':
        carAngle-= 4.0f;
        break;
    case 'D':
        carAngle+= 4.0f;
        break;
    case 'R':
        carAngle=0;
        carSpeed=0.0f;
        carX=0.0f;
        carY=0.0f;
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
		//orthox1 -= mn_x0-x;
        //orthox2 += mn_x0-x;
        //orthoy1 -= mn_x0-x;
        //orthoy2 += mn_x0-x;
        carAngle -= 4.0f;
    }
	if( mouse_left )
	{
        //orthox1 += mn_x0-x;
        //orthox2 += mn_x0-x;
        //orthoy1 -= mn_y0-y;
        //orthoy2 -= mn_y0-y;
        carAngle += 4.0f;
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
