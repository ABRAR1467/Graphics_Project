#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "drawcube.h"
#include "sylinder.h"
#include "object.h"


void moving_obj(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 als,float r,float x =0,float y = 0,float z = 0) {

	glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, .02f+y, 0.9f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.3f, 2.0f, .4f));
	model = als * translateMatrix * scaleMatrix;
	Cylinder cylinder = Cylinder();
	cylinder.drawCylinder(lightingShader, model, 0.545f, 0.271f);

	//rope
	// 

	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, 1.8f+y, 0.9f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f));
	model = identityMatrix * translateMatrix  * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);

	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, 1.8f+y, 0.9f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r+90), glm::vec3(0.0f, 1.0f, 0.0f));
	model = identityMatrix * translateMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);

	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, 1.8f+y, 0.9f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 180), glm::vec3(0.0f, 1.0f, 0.0f));
	model = identityMatrix * translateMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);



	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, 1.8f+y, 0.9f+z));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(r + 270), glm::vec3(0.0f, 1.0f, 0.0f));
	model = identityMatrix * translateMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);
	/*model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.6f, 2.6f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = identityMatrix * translateMatrix * rotateXMatrix * rotateYMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);

	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(4.5f, 0.6f, 0.9f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = identityMatrix * translateMatrix * rotateXMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);


	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f, 0.6f, -0.6f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(.03f, 2.0f, .05f));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	rotateXMatrix = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = identityMatrix * translateMatrix * rotateXMatrix * rotateYMatrix * scaleMatrix;
	drawCube(cubeVAO, lightingShader, model, 0.6, 0.2f, 0.3f);*/
	
	//
	float rr1 = r - 15.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, -0.9f+y, 0.8f+z));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr1), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);

	float rr2 = r - 105.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, -0.9f+y, 0.8f+z));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr2), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);

	float rr3 = r - 195.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, -0.9f+y, 0.8f+z));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr3), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);

	float rr4 = r - 285.0f;
	model = identityMatrix;
	translateMatrix = glm::translate(identityMatrix, glm::vec3(3.0f+x, -0.9f+y, 0.8f+z));
	rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rr4), glm::vec3(0.0f, 1.0f, 0.0f));
	scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.3f, 2.5f, 5.5f));
	model = model * translateMatrix * rotateYMatrix * scaleMatrix;
	object(cubeVAO, lightingShader, model);



	

}