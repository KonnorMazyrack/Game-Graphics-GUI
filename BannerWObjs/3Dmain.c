#include "main.h"

//Colors and position
static GLfloat	blue[] =    { 0.3f, 0.3f, 1.0f };	//blue
static GLfloat	white[] =   { 0.2f, 0.2f, 0.2f };	//white
static GLfloat	fullWhite[]={ 1.0f, 1.0f, 1.0f };
static GLfloat	cooper[] =  { 0.75f, 0.4f, 0.0f };
static GLfloat	gold[] =    { 0.7f, 0.6f, 0.0f };
static GLfloat pos[4] = { LIGHT_POSX, LIGHT_POSY, LIGHT_POSZ, 1.0f }; //position. 0.0 for infinite

static GLfloat rgold[][4] = { 0.2473f, 0.1995f, 0.0745f,
                              0.7516f, 0.6065f, 0.2265f,
                              0.6283f, 0.5558f, 0.3661f };

//Main function, initialize graphics
int main( int argc, char **argv )
{
	initWindow( argc, argv );
	defineCallbacks();
	init3D();
	initTexture();
	initModel( "basicCube.obj" ); //"semi.obj"
	glutMainLoop();
	modelCleanUp();
}

void game()
{
	int	x, y;
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glLightfv( GL_LIGHT0, GL_POSITION, pos  );
	//glLightfv( GL_LIGHT0, GL_AMBIENT, white );
	//glLightfv( GL_LIGHT0, GL_DIFFUSE, white );
	//glLightfv( GL_LIGHT1, GL_POSITION, pos2 );

//GRID
	glNormal3f( 0.0, 0.0, 1.0 );

	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue );
	glMaterialfv( GL_FRONT, GL_SPECULAR, fullWhite );
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

//LIGHT SOURCE REPRESENTATION
 glPushMatrix();
	glTranslatef( LIGHT_POSX, LIGHT_POSY, LIGHT_POSZ );
	glMaterialfv( GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white );
	glDisable( GL_LIGHTING );
	glColor3f( 1.0f, 1.0f, 1.0f );
	glutSolidSphere( 2.0, 10, 10 );
	glEnable( GL_LIGHTING );
 glPopMatrix();

//NEW CENTER
	glTranslated( 150, 150, 10 );


//SPHERE WITH QUADRIC
 glPushMatrix();
	glTranslated( 30, 0, 0 );
	glRotatef( advance/2.0f, 0.0f, 1.0f, 2.0f );
	glRotated( 90.0, 1.0, 0.0, 0.0 );

	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, fullWhite );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, white );

	glEnable( GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, textureID1 );
	GLUquadricObj *qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle( qobj, GLU_FILL );
	gluQuadricTexture( qobj, GL_TRUE );
	gluSphere( qobj, 40.0, 40, 40 );
	glDisable( GL_TEXTURE_2D );
	//glutSolidSphere( 10.0, 20, 20 );
 glPopMatrix();

//LOADED MODEL
 glPushMatrix();
	glTranslated( -60, 0, 0 );
	glScaled( 20, 20, 20 );
	glRotatef( advance/2.0f, 0.0f, 0.0f, 1.0f );
	glRotated( 90, 1.0, 0.0, 0.0 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, cooper );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, cooper );
	/* If the display list has not been made yet, create a new one and
	   fill it with scene contents */
	createSceneList();
	glCallList( scene_list );
 glPopMatrix();

//TRANSPARENT BANNER, must be the last because of the transparency
 glPushMatrix();
	glTranslated( 0, 0, 40 );
	glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, fullWhite );
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, white );
	glBindTexture( GL_TEXTURE_2D, textureID2 );
	glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND);
	glNormal3f( 0.0f, 0.0f, 1.0f );
	glBegin( GL_QUADS );
	 glTexCoord2f( 0.0f, 0.0f );
	 glVertex3d( -100, -100, 0 );
	 glTexCoord2f( 1.0f, 0.0f );
	 glVertex3d(  100, -100, 0 );
	 glTexCoord2f( 1.0f, 1.0f );
	 glVertex3d(  100,  100, 0 );
	 glTexCoord2f( 0.0f, 1.0f );
	 glVertex3d( -100,  100, 0 );
	glEnd();
	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
 glPopMatrix();
}






