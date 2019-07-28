#pragma once

#include<iostream>
#include<string>

#include "GL\glew.h"

class Texture {
public:
	
private:
	GLuint m_Texture;	//This will be out handle for the texture

public:
	Texture(const std::string &filePath);
	~Texture();

	//Once this is called, it sets the openGL to start using this texture
	//You can bind multiple textures at once. The parameter is a way to distinguish which texture we are binding
	void Bind(const unsigned int unit);

};