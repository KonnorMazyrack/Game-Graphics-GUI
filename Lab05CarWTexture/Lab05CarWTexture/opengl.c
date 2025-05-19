#include "main.h"
//Variables for initializing process
int advance=0, anim=1, alias=1;
int orthox1=-100, orthoy1=-100, orthox2=100, orthoy2=100;
//Mouse navigation
int mouse_left=0, mouse_right=0;
int mouse_ctrl=0, mn_x0, mn_y0;

GLuint textureID1,textureID2;

//Local prototypes
void loop( void );
void draw();
void reshape(int width, int height );
void keyboard( unsigned char key, int x, int y );
void mouse( int button, int state, int x, int y );
void movement( int x, int y );

void initWindow( int argc, char **argv )
{
    glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 1000, 1000 );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "2D Application with Menu" );
}
void init3D()
{


	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    textureID2 = SOIL_load_OGL_texture(
        //"logoTBG.png",
        "pngTextures/TransparentImage.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

	textureID1 = SOIL_load_OGL_texture(
        //"logoTBG.png",
        "pngTextures/CarTexture.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
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

//Function for the animation
void loop( void )
{
	advance++;
	draw();
	Sleep( 20 );//miliseconds
}
void texturecity()
{


    glEnable( GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureID2);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-100, -100);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(100, -100);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(100, 100);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-100, 100);
    glEnd();

    glDisable(GL_TEXTURE_2D);


}
void texturecar()
{


    glEnable( GL_TEXTURE_2D);
    glEnable( GL_BLEND);

    glBindTexture(GL_TEXTURE_2D, textureID1);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();

    glDisable(GL_TEXTURE_2D);


}
void draw()
{

    glClear( GL_COLOR_BUFFER_BIT );

    game();

    glutSwapBuffers();
}
//Callback, when a reshape happened
void reshape(int width, int height )
{
	glViewport(0, 0, width, height );
	float aspect=(float)width/height;
	if( aspect>=1.0 ) //wide
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
}

void keyboard( unsigned char key, int x, int y )
{
	switch( toupper( key ) )
	{
	case 27:
		exit( 0 );
		break;
	case ' ':
		anim = !anim;
		if( anim )
			glutIdleFunc( loop );
		else
			glutIdleFunc( 0 );
		break;
// moved
	case 'R':
		resetGame();
		draw();
		break;
	/*case 'A':
		alias = !alias;
		if( alias )
		{
			glEnable( GL_LINE_SMOOTH );
			glEnable( GL_POLYGON_SMOOTH );
			glEnable( GL_BLEND);
		} else {
			glDisable( GL_LINE_SMOOTH );
			glDisable( GL_POLYGON_SMOOTH );
			glDisable( GL_BLEND);
		}
		draw();
		break;  */
	default:
		gameKeys( toupper( key ) );
	}
}

void mouse( int button, int state, int x, int y )
{
	if( state==GLUT_DOWN )
	{
		mn_x0=x;
		mn_y0=y;
		mouse_left =  ( button==GLUT_LEFT_BUTTON ?1:0 );
		mouse_right = ( button==GLUT_RIGHT_BUTTON?1:0 );
	}
	if( state==GLUT_UP )
		mouse_left=mouse_right=0;
}
void movement( int x, int y )
{
	if( mouse_right )
		carAccel( (mn_y0-y)/200.0f );
	if( mouse_left )
		carSteer( (mn_x0-x)/20.0f );
	mn_x0=x;
	mn_y0=y;
}
//========================
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
