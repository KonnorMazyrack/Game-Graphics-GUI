#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <SOIL2/soil2.h>
#include <stb_image.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm.hpp>
#include <gtc/type_ptr.hpp> // glm::value_ptr
#include <gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include "Sphere.h"
#include "Utils.h"
using namespace std;

#define numVAOs 1
#define numVBOs 3

float cameraX, cameraY, cameraZ;
float sphLocX, sphLocY, sphLocZ;
GLuint renderingProgram;
GLuint vao[numVAOs];
GLuint vbo[numVBOs];
GLuint earthTexture;
GLuint backgroundTexture;
float rotAmt = 0.0f;
float movementSpeed = 5.0f;

bool moveUp = false;
bool moveDown = false;
bool moveLeft = false;
bool moveRight = false;


// variable allocation for display
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;

Sphere mySphere = Sphere(48);

void setupVertices(void) {
	std::vector<int> ind = mySphere.getIndices();
	std::vector<glm::vec3> vert = mySphere.getVertices();
	std::vector<glm::vec2> tex = mySphere.getTexCoords();
	std::vector<glm::vec3> norm = mySphere.getNormals();

	std::vector<float> pvalues;
	std::vector<float> tvalues;
	std::vector<float> nvalues;

	int numIndices = mySphere.getNumIndices();
	for (int i = 0; i < numIndices; i++) {
		pvalues.push_back((vert[ind[i]]).x);
		pvalues.push_back((vert[ind[i]]).y);
		pvalues.push_back((vert[ind[i]]).z);
		tvalues.push_back((tex[ind[i]]).s);
		tvalues.push_back((tex[ind[i]]).t);
		nvalues.push_back((norm[ind[i]]).x);
		nvalues.push_back((norm[ind[i]]).y);
		nvalues.push_back((norm[ind[i]]).z);
	}

	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(numVBOs, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, pvalues.size()*4, &pvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, tvalues.size()*4, &tvalues[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, nvalues.size()*4, &nvalues[0], GL_STATIC_DRAW);
}

void setupBackground() {
    // Vertices for a quad covering the entire screen
    float vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-left corner
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-right corner
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top-right corner
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f  // top-left corner
    };

    // Create and bind VAO
    glGenVertexArrays(1, &vao[1]); // Use a different VAO for the background
    glBindVertexArray(vao[1]);

    // Create and bind VBO
    glGenBuffers(1, &vbo[3]); // Use a different VBO for the background
    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Specify vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Load and bind texture for the background
    glGenTextures(1, &backgroundTexture);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    // Set texture wrapping and filtering options if needed
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	cameraX = 0.0f; cameraY = 0.0f; cameraZ = 2.0f;
	sphLocX = 0.0f; sphLocY = 0.0f; sphLocZ = -1.0f;

	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);

	setupBackground();

	backgroundTexture = Utils::loadTexture("stars.jpg");

	setupVertices();

	earthTexture = Utils::loadTexture("earth.jpg");
}

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderingProgram);

	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");

	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(sphLocX, sphLocY, sphLocZ));
	//mMat = glm::rotate(mMat, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));

	float scaleFactor = 0.25f;
	mMat = glm::scale(mMat,glm::vec3(scaleFactor, scaleFactor, scaleFactor));
	mvMat = vMat * mMat;

	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, earthTexture);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, mySphere.getNumIndices());
}

void window_size_callback(GLFWwindow* win, int newWidth, int newHeight) {
	aspect = (float)newWidth / (float)newHeight;
	glViewport(0, 0, newWidth, newHeight);
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Check if the key is pressed or repeated and perform actions accordingly
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_W:
                moveUp = true;
                break;
            case GLFW_KEY_S:
                moveDown = true;
                break;
            case GLFW_KEY_A:
                moveLeft = true;
                break;
            case GLFW_KEY_D:
                moveRight = true;
                break;
            // Add more cases for other keys if needed
        }
    } else if (action == GLFW_RELEASE) {
        switch (key) {
            case GLFW_KEY_W:
                moveUp = false;
                break;
            case GLFW_KEY_S:
                moveDown = false;
                break;
            case GLFW_KEY_A:
                moveLeft = false;
                break;
            case GLFW_KEY_D:
                moveRight = false;
                break;
            // Add more cases for other keys if needed
        }
    }
}

void updateSpherePosition() {
    float movementSpeed = 0.015f; // Adjust this value as needed

    float minX = -1.45f;
    float maxX = 1.45f;
    float minY = -1.45f;
    float maxY = 1.45f;
    // Update sphere position based on movement flags
    if (moveUp && (sphLocY + movementSpeed) <= maxY) {
        sphLocY += movementSpeed;
    }
    if (moveDown && (sphLocY - movementSpeed) >= minY) {
        sphLocY -= movementSpeed;
    }
    if (moveLeft && (sphLocX - movementSpeed) >= minX) {
        sphLocX -= movementSpeed;
    }
    if (moveRight && (sphLocX + movementSpeed) <= maxX) {
        sphLocX += movementSpeed;
    }
}

int main(void) {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Chapter 6 - program 1", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetKeyCallback(window, key_callback);

	init(window);

	while (!glfwWindowShouldClose(window)) {
        updateSpherePosition();

		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

