#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include <cassert>

Texture::Texture(const std::string &filePath) {
	int width, height, numComponents;

	//loads the image
	unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
		std::cerr << "Texture loading Failed for " << filePath << std::endl;
	else
		std::cout << "Texture loading Succeded for: " << filePath << std::endl;

	//std::cout << "Image Data: " << imageData << std::endl;

	//We are going to send this data to the GPU through OpenGl.
	//We must first generate space for the textures
	//We will be generating 1 texture and m_Texture is a handle and points to it
	glGenTextures(1, &m_Texture);
	//After creating the space in the GPU, we must bind it 
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	//we now specify the type of data we will be sending. This is an optional step
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//Horizonal tiling is set to repeat
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//Vertical tiling is set to repeat

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	//Filtering mode is set to linear
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	
	//Feeding in the actual texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	//Flshes out the texture data from the CPU
	stbi_image_free(imageData);
}
Texture::~Texture() {
	glDeleteTextures(1, &m_Texture);	//Delete a single texture at m_Texture
}

void Texture::Bind(const unsigned int unit) {
	assert(unit >= 0 && unit <= 31);

	//glActiveTexture(GL_TEXTURE0 + unit);	//This function changes the active texture that OpenGL is working on
	glBindTexture(GL_TEXTURE_2D, m_Texture);	//OpenGl binds our texture to the unit that we set
}