#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SOIL/SOIL.h>

#define GRID_SIZE 20
#define INITIAL_SNAKE_SIZE 3

int gridSize = GRID_SIZE;
int snakeSize = INITIAL_SNAKE_SIZE;

int snakeX[100], snakeY[100];
int foodX, foodY;
int direction = 1; // 0: left, 1: up, 2: right, 3: down

bool gameStarted = false;
bool gameOver = false;

GLuint textureID1, textureID2, textureID3;

void initGame() {
    // Initialize the snake at the center of the grid
    for (int i = 0; i < INITIAL_SNAKE_SIZE; ++i) {
        snakeX[i] = gridSize / 2 - i;
        snakeY[i] = gridSize / 2;
    }

    // Place the initial food randomly
    foodX = rand() % gridSize;
    foodY = rand() % gridSize;
}
void init2D() {
    glClearColor( 0.84,0.925,0.933, 0.0 );
    glEnable( GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    textureID1 = SOIL_load_OGL_texture(
        "pngTextures/Fruit.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    textureID2 = SOIL_load_OGL_texture(
        "pngTextures/SnakeSkin2.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    textureID3 = SOIL_load_OGL_texture(
        "pngTextures/SnakeHead.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );
    if (textureID1 == 0 || textureID2 == 0)
    {
        printf("Error loading CityTexture: %s\n", SOIL_last_result());
    }
}


void drawSquare(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

void drawSnake() {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    //glColor3f(0.0f, 0.0f, 1.0f); // Green color
    for (int i = 0; i < snakeSize; ++i) {
        if (i == 0)
        {
            if (direction == 0) //left
            {
                glBindTexture( GL_TEXTURE_2D, textureID3 );
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] - 0.5);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] - 0.5);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] + 1.5);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] + 1.5);
                glEnd();
            } else if (direction == 1) //up
            {
                glBindTexture( GL_TEXTURE_2D, textureID3 );
                glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] - 0.5);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] - 0.5);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] + 1.5);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] + 1.5);
                glEnd();
            } else if (direction == 2) //right
            {
                glBindTexture( GL_TEXTURE_2D, textureID3 );
                glBegin(GL_QUADS);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] - 0.5);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] - 0.5);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] + 1.5);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] + 1.5);
                glEnd();
            } else if (direction == 3) //down
            {
                glBindTexture( GL_TEXTURE_2D, textureID3 );
                glBegin(GL_QUADS);
                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] - 0.5);
                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] - 0.5);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(snakeX[i] + 1.5, snakeY[i] + 1.5);
                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(snakeX[i] - 0.5, snakeY[i] + 1.5);
                glEnd();
            }
        } else {
            glBindTexture( GL_TEXTURE_2D, textureID2 );
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(snakeX[i], snakeY[i]);
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(snakeX[i] + 1, snakeY[i]);
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(snakeX[i] + 1, snakeY[i] + 1);
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(snakeX[i], snakeY[i] + 1);
            glEnd();
        }
        //drawSquare(snakeX[i], snakeY[i]);
    }
    glDisable(GL_TEXTURE_2D);
}

void drawFood() {
    //glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glEnable(GL_TEXTURE_2D);
    glBindTexture( GL_TEXTURE_2D, textureID1 );
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(foodX, foodY);
    //drawSquare(foodX, foodY);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(foodX + 1, foodY);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(foodX + 1, foodY + 1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(foodX, foodY + 1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawTitleScreen() {
    glColor3f(0.0f, 0.0f, 0.0f);// White color
    glRasterPos2f(3.5f, 8.0f);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press 'SPACE' to Start");
    glColor3f(0.0f, 0.0f, 1.0f);// Blue color
    glRasterPos2f(5.0f, 10.0f);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"The Snake Game");
}
void drawGameOverScreen() {
    glColor3f(0.0f, 0.0f, 0.0f);// White color
    glRasterPos2f(3.5f, 8.0f);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press 'R' to Restart");
    glRasterPos2f(3.5f, 6.5f);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Press 'E' to Exit");
    glColor3f(1.0f, 0.0f, 0.0f);// Red color
    glRasterPos2f(5.0f, 10.0f);
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)"Game Over!");
}

void drawScore() {
    glColor3f(0.0f, 0.0f, 0.0f); // White color
    glRasterPos2f((gridSize/2)-2.5f, gridSize - 1.0f); // Position to display score
    char scoreText[20];
    sprintf(scoreText, "Score: %d", (snakeSize - INITIAL_SNAKE_SIZE) * 10);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char*)scoreText);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if(gameStarted){
        drawSnake();
        drawFood();
        drawScore();
    }else{
        drawTitleScreen();
    }

    if(gameOver){
        drawGameOverScreen();
    }

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    if (!gameStarted && key == 32) { //space bar = 32
        gameStarted = true;
        initGame();
    } else if (gameStarted) {
        switch (key) {
            case 'w':
                if (direction != 3) // prevent moving down if current direction is up
                    direction = 1;
                break;
            case 's':
                if (direction != 1) // prevent moving up if current direction is down
                    direction = 3;
                break;
            case 'a':
                if (direction != 2) // prevent moving right if current direction is left
                    direction = 0;
                break;
            case 'd':
                if (direction != 0) // prevent moving left if current direction is right
                    direction = 2;
                break;
            case 'r':
                snakeSize = INITIAL_SNAKE_SIZE;
                direction = 1;
                gameStarted = false;
                gameOver = false;
                initGame();
                break;
            case 'e':
                exit(0);
                break;
        }
    } else if (gameOver && key == 'r') {
            exit(42);
    }
}

void updateGame() {
    if(!gameStarted)
        return;

    // Move the snake
    if(gameOver != true)
    {
        for (int i = snakeSize - 1; i > 0; --i) {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }

        // Update the head based on the direction
        switch (direction) {
            case 0: // left
                snakeX[0]--;
                break;
            case 1: // up
                snakeY[0]++;
                break;
            case 2: // right
                snakeX[0]++;
                break;
            case 3: // down
                snakeY[0]--;
                break;
        }
    }

    // Check for collisions with food
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        // Increase the snake size
        snakeSize++;
        // Place a new food randomly
        foodX = rand() % gridSize;
        foodY = rand() % gridSize;
    }

    // Check for collisions with walls or itself
    if (snakeX[0] < 0 || snakeX[0] >= gridSize || snakeY[0] < 0 || snakeY[0] >= gridSize) {
        gameOver = true;
        //exit(0); // Game over
    }

    for (int i = 1; i < snakeSize; ++i) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = true;
            //exit(0); // Game over
        }
    }
}

void timer(int value) {
    updateGame();
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(gridSize * 20, gridSize * 20);
    glutCreateWindow("Snake Game");
    init2D();

    glOrtho(0, gridSize, 0, gridSize, -1, 1);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(100, timer, 0);

    // Initialize random seed
    srand(time(NULL));

    initGame();

    glutMainLoop();

    return 0;
}
