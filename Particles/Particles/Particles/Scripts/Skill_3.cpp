#include "Skill_3.h"

Skill_3::Skill_3(Texture& texture, AnimationHandler& animationHandler, SoundManager& soundManager, Vector2f position, int skillID) : animationHandler(animationHandler), soundManager(soundManager) {
	this->uniqueSkillID = "skill_3_" + to_string(skillID);
	this->skillID = skillID;
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
	this->sprite.setOrigin(spriteOrigin);
	this->animationHandler.addAnimation(uniqueSkillID, this->sprite, rectSource, 116, 812, 0, this->animationSpeed);

	soundManager.playSound("ice_sound");
	soundManager.playSound("wind_sound");
}

void Skill_3::update(float dt) {
	if (this->animationHandler.hasResetted(uniqueSkillID)) {
		this->active = false;
	}
	this->animationHandler.update(uniqueSkillID, dt);
}

void Skill_3::draw(RenderTarget& target, RenderStates states) const {
	target.draw(this->sprite);
}

bool Skill_3::collide(FloatRect otherBounds) {
	if (this->bounds.intersects(otherBounds)) {
		return true;
	}
	return false;
}


