#include <cmath>
#include <vector>
#include <iostream>
#include <glm.hpp>
#include "Maze.h" // Include the Maze header file instead of Sphere.h
using namespace std;

class MazeGenerator {
private:
    int numVertices;
    int numIndices;
    std::vector<int> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> tangents;
    void initMaze(int rows, int cols);

public:
    MazeGenerator();
    MazeGenerator(int rows, int cols);
    int getNumVertices();
    int getNumIndices();
    std::vector<int> getIndices();
    std::vector<glm::vec3> getVertices();
    std::vector<glm::vec2> getTexCoords();
    std::vector<glm::vec3> getNormals();
    std::vector<glm::vec3> getTangents();
};

MazeGenerator::MazeGenerator() {
    initMaze(5, 5); // Default maze size 5x5
}

MazeGenerator::MazeGenerator(int rows, int cols) {
    initMaze(rows, cols);
}

void MazeGenerator::initMaze(int rows, int cols) {
    // Your maze generation logic goes here
    // Generate vertices, texture coordinates, normals, tangents, and indices for the maze
}

int MazeGenerator::getNumVertices() { return numVertices; }
int MazeGenerator::getNumIndices() { return numIndices; }
std::vector<int> MazeGenerator::getIndices() { return indices; }
std::vector<glm::vec3> MazeGenerator::getVertices() { return vertices; }
std::vector<glm::vec2> MazeGenerator::getTexCoords() { return texCoords; }
std::vector<glm::vec3> MazeGenerator::getNormals() { return normals; }
std::vector<glm::vec3> MazeGenerator::getTangents() { return tangents; }
