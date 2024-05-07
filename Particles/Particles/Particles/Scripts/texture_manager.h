#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class TextureManager {
public:
	TextureManager() {
		cout << "Texture Manager loaded successfully." << endl;
	}
	
	void loadTexture(const string& name, const string& filename);
	Texture& getRef(const string& texture);
	TextureManager& getTextureManager();

private:
	unordered_map<string, Texture> textures;
};