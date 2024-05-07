#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using namespace sf;

struct _Animation {
public:
	Sprite& sprite;
	IntRect rectSource;
	int moveRect;
	int lastRect;
	int resetRect;
	float animationSpeed;
	bool hasResetted = false;
	bool alive = true;

	float time = 0;
};

class AnimationHandler {
public:
	AnimationHandler() {
		cout << "Animation Handler loaded successfully" << endl;
	}
	~AnimationHandler() {
	}

	void addAnimation(const string& name, Sprite& sprite, IntRect rectSource, unsigned short int moveRect, unsigned short int lastRect, unsigned short int resetRect, const float animationSpeed);
	void update(const string& string, const float dt);
	void resetAnimationHandler(const string& name, bool& trigger);
	bool hasResetted(const string& name);

private:
	unordered_map <string, _Animation> animations;
};