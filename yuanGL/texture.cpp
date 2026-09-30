#include "pch.h"
#include "texture.h"

#include <stb_image.h>

#include "gl_call.h"

yuanGL::Texture::Texture(const char* file_path) :
	_file_path(file_path)
{
	stbi_set_flip_vertically_on_load(1);
	_local_buffer = stbi_load(file_path, &_width, &_height, &_bpp, 4);

	GLCall(glGenTextures(1, &_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, _id));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _local_buffer));
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

yuanGL::Texture::~Texture()
{
	if (_local_buffer) {
		stbi_image_free(_local_buffer);
	}

	unbind();
	GLCall(glDeleteTextures(1, &_id));
}

void yuanGL::Texture::bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, _id));
}

void yuanGL::Texture::unbind()
{
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
