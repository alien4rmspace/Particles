#pragma once
#include "GameObject.h"

class Skill_4 : public GameObject {
public:
	Skill_4(Texture& texture, AnimationHandler& animationHandler, SoundManager& soundManager, Vector2f position, int skillID);

	void update(float dt) override;
	void draw(RenderTarget& target, RenderStates states) const override;
	bool collide();
	bool collide(FloatRect otherBounds);
private:
	AnimationHandler& animationHandler;
	SoundManager& soundManager;
	RectangleShape rectangle;
	string uniqueSkillID;
	IntRect rectSource = { 0, 0, 96, 112 };
	Vector2f spriteOrigin = { 50, 50 };
	FloatRect bounds;
	int spriteRotation = 120;
	float animationSpeed = 0.18;
	int Velocity = 400;
};