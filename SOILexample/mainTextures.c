#include <GL/glut.h>
#include <SOIL/SOIL.h>

GLuint textureID1,textureID2;

void init() {
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);

    // Enable alpha blending
    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Load texture
    textureID1 = SOIL_load_OGL_texture(
        //"logoTBG.png",
        "pngTextures/bannerT.png",
        SOIL_LOAD_RGBA,//SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

	textureID2 = SOIL_load_OGL_texture(
        "pngTextures/wood.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    //if( textureID1 == 0 || textureID2 == 0 ) {
    //    printf( "Error loading texture: %s\n", SOIL_last_result() );
    //}
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    // Bind texture
    glBindTexture( GL_TEXTURE_2D, textureID2 );
    // Draw rectangle with texture
    //glBegin(GL_QUADS);
    //glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
    //glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
    //glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
    //glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);
    //glEnd();

    glTranslatef( 0.3, 0.3, 0.0 );
    glRotated( 15.0, 0.0, 0.0, 1.0 );

	// Enable blending, for transparency
    glEnable(GL_BLEND);
    // Bind texture
	glBindTexture( GL_TEXTURE_2D, textureID1 );
    // Draw rectangle with texture
    //glBegin(GL_QUADS);
    //glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.5f, -1.5f);
    //glTexCoord2f(1.0f, 0.0f); glVertex2f(1.5f, -1.5f);
    //glTexCoord2f(1.0f, 1.0f); glVertex2f(1.5f, 1.5f);
    //glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.5f, 1.5f);
    //glEnd();

    glTranslatef( -0.6, -0.5, 0.0 );
    glRotated( 60.0, 0.0, 0.0, 1.0 );
    glDisable(GL_BLEND);
	glBindTexture( GL_TEXTURE_2D, textureID1 );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //scale
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); //translation
    // Draw rectangle with texture
    //glBegin(GL_QUADS);
    //glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
    //glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
    //glTexCoord2f(1.0f, 2.0f); glVertex2f(0.5f, 0.5f);
    //glTexCoord2f(0.0f, 2.0f); glVertex2f(-0.5f, 0.5f);
    //glEnd();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Texture Example with transparency");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
