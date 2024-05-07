#include "sprite_manager.h"

void SpriteManager::addSprite(const auto& _sprite, TextureManager& textureManager) {
Sprite sprite;

sprite.setTexture(textureManager.getRef(string(_sprite["content"])));
sprite.setPosition(_sprite["position"].at("x"), _sprite["position"].at("y"));
sprite.setOrigin(_sprite["origin"].at("x"), _sprite["origin"].at("y"));
sprite.setScale(_sprite["scale"].at("x"), _sprite["scale"].at("y"));

sprites.emplace(_sprite["name"], sprite);
}

void SpriteManager::loadSprites(const string& spriteFileName, TextureManager& textureManager) {
  
   ifstream file(spriteFileName);
  if (!file.is_open()) {
    cerr << "Error: Failed to open file " << spriteFileName << endl;
    return;
  }

  json jsonData;
  try {
    file >> jsonData;
  }
  catch (const json::parse_error& e) {
    cerr << "Error " << spriteFileName << ": " << e.what() << endl;
    return;
  }

  for (const auto& sprite : jsonData["sprites"]) {
    addSprite(sprite, textureManager);
  }
}

Sprite& SpriteManager::getSprite(const string& name) {
    return sprites.at(name);
}