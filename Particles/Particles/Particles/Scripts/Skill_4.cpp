#include "Skill_4.h"

Skill_4::Skill_4(Texture& texture, AnimationHandler& animationHandler, SoundManager& soundManager, Vector2f position, int skillID) : animationHandler(animationHandler), soundManager(soundManager) {
	this->uniqueSkillID = "skill_4_" + to_string(skillID);
	this->sprite.setTexture(texture);
	this->sprite.setPosition(position);
	this->sprite.setOrigin(spriteOrigin);
	this->sprite.setRotation(spriteRotation);
	this->sprite.setColor(Color::Green);
	this->animationHandler.addAnimation(uniqueSkillID, this->sprite, rectSource, 96, 768, 0, this->animationSpeed);

	soundManager.playSound("fire_sound");
	soundManager.playSound("water_sound");
}

void Skill_4::update(float dt) {
	this->animationHandler.update(uniqueSkillID, dt);
	this->sprite.move(0, -this->Velocity * dt);

	// Hitbox
	float skill4BufferTop = 25.0f;
	float skill4BufferLeft = 43.0f;
	float skill4BufferWidth = 95.0f;
	float skill4BufferHeight = 85.0f;

	this->bounds = this->sprite.getGlobalBounds();
	this->bounds.left += skill4BufferLeft;
	this->bounds.top += skill4BufferTop;
	this->bounds.width -= skill4BufferWidth;
	this->bounds.height -= skill4BufferHeight;

	if (debugMode) {
		rectangle.setSize(Vector2f(this->bounds.width, this->bounds.height));
		rectangle.setPosition(this->bounds.left, this->bounds.top);
		rectangle.setFillColor(sf::Color::Transparent);
		rectangle.setOutlineColor(sf::Color::Blue);
		rectangle.setOutlineThickness(1.0f);
	}
}

void Skill_4::draw(RenderTarget& target, RenderStates states) const {
	target.draw(this->sprite);

	if (debugMode) {
		target.draw(this->rectangle);
	}
}

bool Skill_4::collide(FloatRect otherBounds) {
	if (this->bounds.intersects(otherBounds)) {
		this->alive = false;
		this->sprite.setPosition(0, 0);

		soundManager.playSound("explosion_sound");

		return true;
	}
	// Check if sprite's y axis goes out of view.
	if (this->sprite.getPosition().y < 0) {
		this->alive = false;
	}
	return false;
}

bool Skill_4::collide() {
	// Check if sprite's y axis goes out of view.
	if (this->sprite.getPosition().y < 0) {
		this->alive = false;
		soundManager.playSound("explosion_sound");
		return true;
	}
	return false;
}