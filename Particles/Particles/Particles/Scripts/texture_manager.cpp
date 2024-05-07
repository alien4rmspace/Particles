#include "texture_manager.h"

void TextureManager::loadTexture(const string& name, const string& filename) {
	Texture texture;
	texture.loadFromFile(filename);

	this->textures[name] = texture;
}

Texture& TextureManager::getRef(const string& textureName) {
	return this->textures.at(textureName);
}

TextureManager& TextureManager::getTextureManager() {
	return *this;
}