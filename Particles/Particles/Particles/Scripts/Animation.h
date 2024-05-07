#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Animation {
public:
	void addAnimation(Sprite& sprite, IntRect rectSource, unsigned short int moveRect, unsigned short int lastRect, unsigned short int resetRect, const float animationSpeed);
	void update(const float dt);
	void resetAnimationHandler(bool& trigger);
	bool hasResetted();
private:
	Sprite& sprite;
	IntRect rectSource;
	int moveRect;
	int lastRect;
	int resetRect;
	float animationSpeed;
	bool boolHasResetted = false;
	bool alive = true;

	float time = 0;
};