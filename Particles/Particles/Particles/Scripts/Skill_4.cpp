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
}

void Skill_4::draw(RenderTarget& target, RenderStates states) const {
	target.draw(this->sprite);
}

bool Skill_4::collide(FloatRect otherBounds) {
	if (this->bounds.intersects(otherBounds)) {
		this->alive = false;
		this->sprite.setPosition(0, 0);
		//skill_4_active = false;
		//ghost_active = false;
		//ghost_vanish = true;

		soundManager.playSound("explosion_sound");

		//// Generate out particles on collision
		//random_device rd;
		//mt19937 gen(rd());
		//uniform_real_distribution<float> pointsDis(25, 50);

		//for (unsigned short i = 0; i < 10; i++) {
		//	Particle particle(this->m_window, pointsDis(gen), Vector2i(lastClickedPosition));
		//	this->m_particles.push_back(particle);
		//}
		return true;
	}
	// Check if sprite's y axis goes out of view.
	if (this->sprite.getPosition().y < 0) {
		this->alive = false;
	}
	return false;
}