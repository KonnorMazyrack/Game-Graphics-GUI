#include "main.h"
#include <SOIL/SOIL.h>

GLuint textureID1, textureID2;

void initTexture()
{

//			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA ); //for 2D, ordered
//	glBlendFunc( GL_ONE, GL_ZERO ); //default, no transparency
	glBlendFunc( GL_ONE_MINUS_DST_ALPHA, GL_ONE );

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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

