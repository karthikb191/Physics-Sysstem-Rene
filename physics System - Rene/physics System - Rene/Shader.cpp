#include"Shader.h"
//#include<iostream>
#include<fstream>
#include<iostream>
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg);
static std::string LoadShader(const std::string &fileName);
static GLuint CreateShader(const std::string &text, GLenum shaderType);

Shader::Shader(const std::string& fileName) {
	std::cout << "started"<<std::endl;
	//This tells GPU to create a new program for our shader, thus allocating some memory in the GPU for the shader
	m_Program = glCreateProgram();
	m_Shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	m_Shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	//This attaches the shaders we have created to our the program created
	for (int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_Program, m_Shaders[i]);


	glBindAttribLocation(m_Program, 0, "position");		//Attaching position attrib
	glBindAttribLocation(m_Program, 1, "texCoord");		//Attaching texture attrib


	//We are linking our program
	glLinkProgram(m_Program);
	//Linking can fail. We must check if the shader has compiled properly or not
	CheckShaderError(m_Program, GL_LINK_STATUS, true, "ERROR: Link Failed: ");

	//After linking, we must still validate the program so that we have something meaningful
	glValidateProgram(m_Program);
	CheckShaderError(m_Program, GL_VALIDATE_STATUS, true, "ERROR: Validation Failed: ");

	//Send the MVP matrix data to shader
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_Program, "transform");
	m_uniforms[COLOR_U] = glGetUniformLocation(m_Program, "color");
}

Shader::~Shader() {
	//Delete the shaders first
	for (int i = 0; i < NUM_SHADERS; i++) {
		glDetachShader(m_Program, m_Shaders[i]);
		glDeleteShader(m_Shaders[i]);
	}

	//We don't want our program to be in the GPU forever. So, we must delete the created program
	glDeleteProgram(m_Program);
}


void Shader::Bind() {
	glUseProgram(m_Program);
}

void Shader::SetTransform(Matrix4X4 transform) {
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, transform.asArray);
}
void Shader::SetColor(Vec4 color) {
	glUniform4f(m_uniforms[COLOR_U], color.x, color.y, color.z, color.w);
}

static GLuint CreateShader(const std::string &text, GLenum shaderType) {
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Shader creation failed" << std::endl;

	//Converting regular string to list of C-type string with an exit character at the end
	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];
	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);

	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR: Shader compilation failed: ");

	return shader;
}

//Funtions for loading shader from the disk
std::string LoadShader(const std::string &fileName) {
	//open the file
	std::ifstream file;
	//c_str() returns a pointer to an array that contains nul-terminated sequence of characters
	
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good())
		{
			//Get a single line from the string.
			//After the line is obtained, the seek position points to the next line
			std::getline(file, line);
			//Append the obtained lines into a single string.
			output.append(line + "\n");
		}

		//Printing the output for debug purposes
		std::cout << output;
	}
	else {
		std::cout << "File read error";
	}
	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMsg) {
	GLint success = 0;
	GLchar error[2000] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMsg << " : '" << error << "'" << std::endl;
	}
}