#include <GL/freeglut.h>
#include <iostream>
#include <vector>

// Define the dimensions of the grid
const int gridWidth = 20;
const int gridHeight = 20;

// Define the size of each grid cell
const float cellSize = 20.0f;

// Define the Snake structure
struct Snake {
    std::vector<std::pair<int, int>> body;
    int direction; // 0: up, 1: right, 2: down, 3: left
};

// Define the initial state of the game
Snake snake{{10, 10}, {10, 9}, {10, 8}}, // Initial snake position
    food{rand() % gridWidth, rand() % gridHeight}; // Initial food position

// Function to draw a square at (x, y)
void drawSquare(float x, float y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + cellSize, y);
    glVertex2f(x + cellSize, y + cellSize);
    glVertex2f(x, y + cellSize);
    glEnd();
}

// Function to draw the entire game grid
void drawGrid() {
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            glColor3f(0.8f, 0.8f, 0.8f); // Light gray
            drawSquare(i * cellSize, j * cellSize);
        }
    }
}

// Function to draw the snake
void drawSnake() {
    glColor3f(0.0f, 1.0f, 0.0f); // Green
    for (const auto &segment : snake.body) {
        drawSquare(segment.first * cellSize, segment.second * cellSize);
    }
}

// Function to draw the food
void drawFood() {
    glColor3f(1.0f, 0.0f, 0.0f); // Red
    drawSquare(food.first * cellSize, food.second * cellSize);
}

// Function to handle keyboard input
void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        snake.direction = 0;
        break;
    case 'd':
        snake.direction = 1;
        break;
    case 's':
        snake.direction = 2;
        break;
    case 'a':
        snake.direction = 3;
        break;
    }
}

// Function to update the game state
void updateGame(int value) {
    // Update snake position based on the direction
    switch (snake.direction) {
    case 0:
        snake.body.insert(snake.body.begin(), {snake.body.front().first, snake.body.front().second - 1});
        break;
    case 1:
        snake.body.insert(snake.body.begin(), {snake.body.front().first + 1, snake.body.front().second});
        break;
    case 2:
        snake.body.insert(snake.body.begin(), {snake.body.front().first, snake.body.front().second + 1});
        break;
    case 3:
        snake.body.insert(snake.body.begin(), {snake.body.front().first - 1, snake.body.front().second});
        break;
    }

    // Check for collisions with walls or itself
    if (snake.body.front().first < 0 || snake.body.front().first >= gridWidth ||
        snake.body.front().second < 0 || snake.body.front().second >= gridHeight) {
        std::cout << "Game Over! Hit the wall." << std::endl;
        exit(0);
    }

    for (size_t i = 1; i < snake.body.size(); ++i) {
        if (snake.body.front() == snake.body[i]) {
            std::cout << "Game Over! Collided with yourself." << std::endl;
            exit(0);
        }
    }

    // Check if the snake eats the food
    if (snake.body.front() == food) {
        // Generate new food position
        food = {rand() % gridWidth, rand() % gridHeight};
    } else {
        // If not, remove the last segment of the snake
        snake.body.pop_back();
    }

    // Call the update function again after a delay
    glutTimerFunc(100, updateGame, 0);
}

// Function to display the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawGrid();
    drawSnake();
    drawFood();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Snake Game");
    glOrtho(0, gridWidth * cellSize, gridHeight * cellSize, 0, -1, 1);
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutTimerFunc(0, updateGame, 0);
    glutMainLoop();
    return 0;
}
