#include	<GL/glut.h>
//Variables for initializing process
int time=0, anim=0, speed=0, position=0;//, deep=1, spin=0, azoom=0;
float scale = 1.0;
int orthox1=-100, orthoy1=-100, orthox2=100, orthoy2=100;
GLdouble zoom=1.0;
//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;
//Colors
static GLfloat  red[] = { 1.0, 0.0, 0.0 };   //rojo

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
void triangle();

//Main, initialize and go to the idle loop
int main( int argc, char **argv )
{
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 1024, 1024 );
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
void init3D()
{
	glClearColor( 0.84,0.925,0.933, 0.0 );
}

//Function for the animation
void loop( void )
{
	//if( anim ){
        time++;
	//	if( azoom )
	//		zoom *= 1.01;
		draw();
	//}
	Sleep( 20 );//miliseconds
}

void draw()
{
	//time++;
	glClear( GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
    //TEXT
    glutPrintBM( -100.0, 90.0, GLUT_BITMAP_HELVETICA_18, "Options: <spc>:anim, s:spin, d:deep++, r: reset, <esc>:quit", 0.0, 0.0, 1.0 );
    //glutPrintSt( 40.0, -10.0, GLUT_STROKE_ROMAN, "To be or not to be WWiiWW", 0.6, 0.4, 0.0 );
    glColor3fv( red );
    glLineWidth( 2.0 );

    position+=speed;
	glRotatef( time+position, 0.0, 0.0, 1.0 );

	glScalef( 20.0*scale, 20.0*scale, 1.0 );

	//for( int i=0; i<deep; i++ )
	//{
		triangle();
	//glspeedd( 60, 0, 0, 1 );
	//glScalef( 0.5, 0.5, 1.0 );
	//}


	glutSwapBuffers();
}

void triangle()
{
    GLfloat sqr3=pow( 3.0, 0.5 ); //1.7320508f;

    glBegin( GL_LINE_LOOP );
     glVertex2f( 3.0, -sqr3 );
     glVertex2f( -3.0, -sqr3 );
     glVertex2f( 0, 2.0*sqr3 );
    glEnd();
}
//Callback, when a reshape happened
void reshape(int width, int height )
{
	glViewport(0, 0, width, height );

	float aspect=(float)width/height;
    if( aspect>=1.0f ) //wide
    {
        orthox1=-100*aspect; orthox2=100*aspect;
        orthoy1=-100; orthoy2=100;
    } else {
        orthox1=-100; orthox2=100;
        orthoy1=-100/aspect; orthoy2=100/aspect;
    }


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluOrtho2D( orthox1, orthox2, orthoy1, orthoy2 );

	glMatrixMode( GL_MODELVIEW );
	time++;
}
//------------------------------------------------------------------
void keyboard( unsigned char key, int x, int y )
{
	switch( toupper( key ) )
	{
	case 27:
		exit( 0 );
		break;
	/*case 'R':
		time=0;
		anim=0;
		zoom=1.0;
		deep=1;
		//spin=0;
		draw();
		break;
	case 'S':
		spin = !spin;
		break;*/
	case ' ':
	    anim = !anim;
        if( anim )
            glutIdleFunc( loop );
        else
            glutIdleFunc( 0 );
		break;
		/*
	case 'Z':
		azoom = !azoom;
		break;
	case 'D':
		deep++;
		draw();
		break; */
    case 'J':
        speed++;
        break;
    case 'L':
        speed--;
        break;
    case 'I':
        scale*= 1.1f;
        break;
    case 'K':
        scale/= 1.1f;
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
	draw();
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


