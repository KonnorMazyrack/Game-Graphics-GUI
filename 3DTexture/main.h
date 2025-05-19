#include <GL/glut.h>

#define LIGHT_POSX 120.0f
#define LIGHT_POSY 120.0f
#define LIGHT_POSZ 120.0f

//main.c
/*extern static GLfloat	blue[];	//blue
extern static GLfloat	white[];	//white
extern static GLfloat	fullWhite[];
extern static GLfloat	cooper[];
extern static GLfloat	gold[]; */
void game();

//opengl.c
extern int advance;
extern float vx, vy, vz, rx, ry, rz, elev, azim;
extern float d_lat, d_fro, d_azim, d_ver, m_d_fro; //desplazamientos lateral, frontal y vertical
extern int mouse_left, mouse_right;
extern int mouse_ctrl, mn_x0, mn_y0;
void initWindow( int argc, char **argv );
void init3D();
void defineCallbacks();

//texture.c
extern GLuint textureID1, textureID2;
void initTexture();
