#pragma once
#ifndef H_SHADER
#define H_SHADER
#include<string>
#include<GL\glew.h>
#include"Matrices.h"

using namespace _Maths;
class Shader {
public:
	Shader(const std::string& fileName);
	void Bind();
	void SetTransform(Matrix4X4 transform);
	void SetColor(vec4 color);
	~Shader();
	

private:
	Shader(const Shader &other);
	static const unsigned int NUM_SHADERS = 2;
	enum {
		TRANSFORM_U,
		COLOR_U,

		NUM_UNIFORMS
	};

	GLuint m_Program;
	GLuint m_Shaders[NUM_SHADERS];		//A handle to access the shaders
	GLuint m_uniforms[NUM_UNIFORMS];	//A handle to refer our uniforms by

	
};

#endif