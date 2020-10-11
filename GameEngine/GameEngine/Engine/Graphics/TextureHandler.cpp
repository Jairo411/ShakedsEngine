#include "TextureHandler.h"

// MUST INCLUDE STATIC VARIABLES IN THE CPP vv
std::unique_ptr<TextureHandler> TextureHandler::textureInstance = nullptr;

std::vector<Texture*> TextureHandler::textures = std::vector<Texture*>();


TextureHandler::TextureHandler() {
	textures.reserve(10);
}

TextureHandler::~TextureHandler() {
	OnDestroy();
}

TextureHandler* TextureHandler::GetInstance() {
	if (textureInstance.get() == nullptr) {
		textureInstance.reset(new TextureHandler);
	}
	return textureInstance.get();
}

void TextureHandler::OnDestroy() {
	if (textures.size() > 0) {
		for (auto t : textures) {
			glDeleteTextures(sizeof(GLuint), &t->textureID);
			delete t;
			t = nullptr;
		}
		textures.clear();
	}
}

void TextureHandler::CreateTexture(const std::string& textureName_, const std::string& textureFilePath_) {
	Texture* t = new Texture();
	SDL_Surface* surface = nullptr;
	surface = IMG_Load(textureFilePath_.c_str());
	if (surface == nullptr) {
		Debug::Error("Surface failed to load " + textureName_, "TextureHandler.cpp", __LINE__);
		delete t;
		t = nullptr;
		// return inside of a void exits the function!
		return;
	}
	
	glGenTextures(1, &t->textureID);
	glBindTexture(GL_TEXTURE_2D, t->textureID);

	//         |.......boolean condition.........|    true  || false
	int mode = surface->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB;
	// same as this vv
	/*int mode;
	if (surface->format->BytesPerPixel == 4) {
		mode = GL_RGBA;
	}
	else {
		mode = GL_RGB;
	}*/

	// texture target | mipmap level | kind of format | texture width | texture height | should always be 0 | format of source image | data type of the data from the source image | actual image data
	// always need to call this function
	glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// mipmaps are just when things get smaller (minify)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	
	t->width = surface->w;
	t->height = surface->h;
	t->textureName = textureName_;

	textures.push_back(t);

	SDL_FreeSurface(surface);
	surface = nullptr;

	// texels = texture pixels

	// mipmap: opengl creates images based on the texture image that are half the size of the last one, for resolution when objects are further away
	
	// for textures, the coordinates are (s, t, r) instead of (x, y, z)
}

const GLuint TextureHandler::GetTexture(const std::string& textureName_) {
	for (auto t : textures) {
		if (t->textureName == textureName_) {
			return t->textureID;
		}
	}
	return 0;
}

const Texture* TextureHandler::GetTextureData(const std::string& textureName_) {
	for (auto t : textures) {
		if (t->textureName == textureName_) {
			return t	;
		}
	}
	return nullptr;
}