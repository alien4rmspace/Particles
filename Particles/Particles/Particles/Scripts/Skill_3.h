#pragma once
#include <random>
#include "GameObject.h"
#include "Skill_4.h"


class Skill_3 : public GameObject {
public:
	Skill_3(Texture& texture, AnimationHandler& animationHandler, SoundManager& soundManager, Vector2f position, int skillID);

	void update(float dt) override;
	void draw(RenderTarget& target, RenderStates states) const override;
	bool collide(FloatRect otherBounds);
private:
	AnimationHandler& animationHandler;
	SoundManager& soundManager;
	string uniqueSkillID;
	IntRect rectSource = { 0, 0, 116, 47 };
	Vector2f spriteOrigin = { 58, 0 };
	FloatRect bounds;
	float animationSpeed = 0.18;
};