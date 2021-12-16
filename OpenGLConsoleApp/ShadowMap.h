#pragma once

#include <stdio.h>
#include <iostream>

#include <GL/glew.h>

class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();

	virtual bool Init(GLuint width, GLuint height);
	virtual void Write();
	virtual void Read(GLenum textureUnit);
	GLuint GetShadowWidth() { return shadowWidth; }
	GLuint GetShadowHeight() { return shadowHeight; }

protected:
	GLuint FBO;
	GLuint shadowMap;
	GLuint shadowWidth, shadowHeight;

};

