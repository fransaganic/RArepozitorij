#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "Object.h"
#include "Shader.h"
#include "Transform.h"

#pragma once

class Render
{
private:
   
public:

    vector<Object> objects;
    Shader s = Shader();

    Render(vector<Object> objects){
        this->objects = objects;
        string vertexSource = "/Users/Fran/Documents/GitHub/IRG/irglab/irgLab/vjezba7/shaders/shader.vert";
        string fragmentSource = "/Users/Fran/Documents/GitHub/IRG/irglab/irgLab/vjezba7/shaders/shader.frag";
        string geometrySource = "/Users/Fran/Documents/GitHub/IRG/irglab/irgLab/vjezba7/shaders/shader.geom";
        s = Shader(vertexSource.c_str(), fragmentSource.c_str(),  geometrySource.c_str());  
    }
    ~Render(){
        objects.clear();
    }
    Shader getShader(){
        return s;
    }
   
    void draw(){
        for (auto objekt : objects) {
            glUniformMatrix4fv(glGetUniformLocation(s.ID, "model"), 1, GL_FALSE, &objekt.meshes[0].transform.getModelMatrix()[0][0]);
            s.use();
            objekt.draw();
        }
    }
   
    
};