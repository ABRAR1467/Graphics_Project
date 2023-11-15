#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"

void object(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 als)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix,model;
    model = identityMatrix;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.15, 0.375, 0.235));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.15f, 0.05f));
    model = als * translateMatrix *  scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.6f, 0.5f, 0.5f);
}