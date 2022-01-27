#include "TextureManager.h"

map<string, sf::Texture> TextureManager::textures;

void TextureManager::loadTexture(string fileName) {
	string filePath = "images/";
	filePath += fileName;
	filePath += ".png";

	textures[fileName].loadFromFile(filePath);
}

sf::Texture& TextureManager::getTexture(string textureKey) {
	if (textures.find(textureKey) == textures.end()) {
		loadTexture(textureKey);
	}
	return textures[textureKey];
}