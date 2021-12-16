#pragma once

#include "Light.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

class DirectionalLight :
    public Light
{
public:
    DirectionalLight();
	DirectionalLight(GLfloat shadowWidth, GLfloat shadowHeight, 
		GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);
    ~DirectionalLight();

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
		GLfloat diffuseIntensityLocation, GLfloat directionLocation);

	glm::mat4 CalculateLightTransform();

private:
    glm::vec3 direction;

};

