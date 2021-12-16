#pragma once

#include <GL/glew.h>

#include "stb_image.h"

#include <iostream>

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);
	~Texture();

	bool LoadTexture();
	// with alpha channel
	bool LoadTextureA();

	void UseTexture();
	void ClearTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLocation;

};

