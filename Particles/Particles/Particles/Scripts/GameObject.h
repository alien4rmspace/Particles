#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "animation_handler.h"
#include "sound_manager.h"
#include <random>
#include <iostream>

using namespace sf;
using namespace std;

class GameObject : public Drawable {
public:
	virtual void update(float dt) = 0;
	virtual void draw(RenderTarget& target, RenderStates states) const = 0;
	virtual bool collide(FloatRect bounds) = 0;
	void setAlive(bool alive) { this->alive = alive; };
	bool isAlive() { return alive; };
	bool isActive() { return active; };
protected:
	Sprite sprite;
	bool active = true;
	bool alive = true;
};