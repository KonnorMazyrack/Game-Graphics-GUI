#include "main.h"
#include <SOIL/SOIL.h>

GLuint textureID1, textureID2;

void initTexture()
{

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	textureID1 = SOIL_load_OGL_texture(
        "wood.png",
        SOIL_LOAD_AUTO,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

	textureID2 = SOIL_load_OGL_texture(
        "bannerT.png",
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
}
void textureSquare()
{
	// Enable blending, for transparency
	glEnable(GL_TEXTURE_2D);
    //glEnable(GL_BLEND);
    // Bind texture
	glBindTexture( GL_TEXTURE_2D, textureID1 );
    // Draw rectangle with texture
    glBegin(GL_QUADS);
     glTexCoord2f(1.0f, 0.0f); glVertex2f( -1.0f, -0.5f );
     glTexCoord2f(0.0f, 0.0f); glVertex2f(  1.0f, -0.5f );
     glTexCoord2f(0.0f, 1.0f); glVertex2f(  1.0f,  0.5f );
     glTexCoord2f(1.0f, 1.0f); glVertex2f( -1.0f,  0.5f );
    glEnd();
    glDisable(GL_TEXTURE_2D);
    //glDisable(GL_BLEND);
}
void textureCity()
{
    glEnable( GL_TEXTURE_2D );
    //glEnable(GL_BLEND);
    // Bind texture
	glBindTexture( GL_TEXTURE_2D, textureID2 );
    // Draw rectangle with texture
    glBegin(GL_QUADS);
     glTexCoord2f(1.0f, 0.0f); glVertex2d( -100, -100);
     glTexCoord2f(0.0f, 0.0f); glVertex2d(100, -100 );
     glTexCoord2f(0.0f, 1.0f); glVertex2d(100, 100);
     glTexCoord2f(1.0f, 1.0f); glVertex2d(-100,100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
