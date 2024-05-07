#pragma once

#include <iostream>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include <unordered_map>
#include <fstream>

#include "texture_manager.h"

#include "json.hpp"

using namespace std;
using namespace sf;
using json = nlohmann::json;

class SpriteManager {
public:
	SpriteManager() {
		cout << "Sprite Manager loaded successfuly." << endl;
	}
	~SpriteManager() {

	}

	void addSprite(const auto& _sprite, TextureManager& textureManager);
	void loadSprites(const string& spriteFileName, TextureManager& font);
	Sprite& getSprite(const string& name);

private:
	unordered_map<string, Sprite> sprites;
};