#include "main.h"

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
	//Front wheels
	glBegin( GL_LINE_LOOP );
	for( int i=7; i<11; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();

    glPushMatrix();
	glRotated( steerAngle, 0.0, 0.0, 1.0 );
	glBegin( GL_LINE_LOOP );
	for( int i=11; i<15; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
    glPopMatrix();

	//Rear wheels
	glBegin( GL_LINE_LOOP );
	for( int i=15; i<19; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
	glPopMatrix();

    glPushMatrix();
	glRotated( steerAngle, 0.0, 0.0, 1.0 );
	glBegin( GL_LINE_LOOP );
	for( int i=19; i<23; i++ )
		 glVertex2f( carVertices[ i*3+0], carVertices[ i*3+1 ] );
	glEnd();
    glPopMatrix();
}
void house()
{
    glBegin( GL_LINE_LOOP );
     glVertex2d( 0, 0 );
     glVertex2d( 10, 0);
     glVertex2d( 10, 10 );
     glVertex2d( 5, 15 );
     glVertex2d( 0, 10 );
    glEnd();
}
