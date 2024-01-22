#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "Transform.h"

using namespace std;

class Camera : public Transform
{
private:
    


public:

    glm::vec3 ociste;
    glm::vec3 glediste;
    glm::vec3 up;

    Camera(glm::vec3 eye, glm::vec3 glediste, glm::vec3 up) : ociste(eye), glediste(glediste), up(up) {}
    ~Camera(){}

    vector<glm::mat4> getPerspectiveMatrix(int width, int height){
        glm::mat4 view = glm::lookAt(ociste, glediste, up);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        glm::mat4 modelMatrix = getModelMatrix();
        vector<glm::mat4> matriceProjekcije;
        matriceProjekcije.push_back(view);
        matriceProjekcije.push_back(projection);
        matriceProjekcije.push_back(modelMatrix);
        return matriceProjekcije;
    }

    void moveForward(float speed) {
        glm::vec3 direction = glm::normalize(glediste - ociste);
        ociste += direction * speed;
        glediste += direction * speed;
    }

    void moveRight(float speed) {
        glm::vec3 direction = glm::normalize(glediste - ociste);
        glm::vec3 right = glm::normalize(glm::cross(direction, up));
        ociste += right * speed;
        glediste += right * speed;
    }

    void moveUp(float speed) {
        glm::vec3 direction = glm::normalize(glediste - ociste);
        glm::vec3 right = glm::normalize(glm::cross(direction, up));
        glm::vec3 up = glm::normalize(glm::cross(right, direction));
        ociste += up * speed;
        glediste += up * speed;
    }

    void rotate(float angle, glm::vec3 axis) {
        glm::vec3 direction = glm::normalize(glediste - ociste);
        glm::vec3 right = glm::normalize(glm::cross(direction, up));
        glm::vec3 up = glm::normalize(glm::cross(right, direction));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
        glm::vec4 newDirection = rotationMatrix * glm::vec4(direction, 1.0f);
        glm::vec4 newUp = rotationMatrix * glm::vec4(up, 1.0f);
        glediste = ociste + glm::vec3(newDirection);
        up = glm::vec3(newUp);
    }

};