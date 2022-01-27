#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
using std::string;
using std::map;

class TextureManager {
	static map<string, sf::Texture> textures;
public:
	static void loadTexture(string filename);
	static sf::Texture& getTexture(string key);
};