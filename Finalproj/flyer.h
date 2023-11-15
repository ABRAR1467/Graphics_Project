#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"


void flyer(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 als, float FLYER_Y,float x =0,float y=0,float z = 0) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;


	//BACK
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, 0.0f+y, 0.3f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 6.0f, 0.1f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.02, 0.21, 0.29);

	//LEFT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, 0.0f+y, 0.3f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 6.0f, 0.3f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.02, 0.21, 0.29);

	//RIGHT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f+x, 0.0f+y, 0.3f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 6.0f, 0.3f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.02, 0.21, 0.29);

	//ROPES
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.5f+x, 0.0f+y, 0.4f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 6.0f, 0.05f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.75, 0.68, 0.98);

	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0f+x, 0.0f+y, 0.4f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 6.0f, 0.05f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.75, 0.68, 0.98);


	//CARRIER	BACK

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.08f+x, (FLYER_Y + 0.1)+y, 0.6f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.43f, 1.0f, 0.05f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.09, 0.42, 0.53);


	//CARRIER SEAT 1

	//BASE
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.2f+x, (FLYER_Y + 0.3)+y, 0.7f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.08f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.42, 0.61, 0.54);

	//LEFT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.2f+x, (FLYER_Y + 0.3)+y, 0.7f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.42, 0.61, 0.54);

	//RIGHT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.6f+x, (FLYER_Y + 0.3)+y, 0.7f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.42, 0.61, 0.54);

	//CARRIER SEAT 2
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0f+x, (FLYER_Y + 0.3)+y, 0.7f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 0.08f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.42, 0.61, 0.54);

	//LEFT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.0f+x, (FLYER_Y + 0.3)+y, 0.7f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.42, 0.61, 0.54);

	//RIGHT
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.4f+x, (FLYER_Y + 0.3)+y, 0.7f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.3f, 0.5f));
	model = als * translateMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.42, 0.61, 0.54);


}