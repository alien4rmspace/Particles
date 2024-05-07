#include "Animation.h"

void Animation::addAnimation(Sprite& sprite, IntRect rectSource, unsigned short int moveRect, unsigned short int lastRect, unsigned short int resetRect, const float animationSpeed) {
	sprite.setTextureRect(rectSource);
	this->sprite = sprite;
	this->rectSource = rectSource;
	this->moveRect = moveRect;
	this->lastRect = lastRect;
	this->resetRect = resetRect;
	this->animationSpeed = animationSpeed;
}

void Animation::update(const float dt) {
	// Using delta time to sync our animation speed with the user's computer spec.
	// Idk if it actually works, in Unity it's built into the api lol.
	this->time += dt;
	int frame = int(this->time / animationSpeed);

	// If animation's intRect exceeds our sprite intRect bounds (lastRect), 
	// reset the animation to the frame we want and reset the time as well.
	if (this->rectSource.left >= lastRect) {
		this->rectSource.left = resetRect;
		this->time = 0; // resets the clock

		this->boolHasResetted = true;
	}
	else if (!this->boolHasResetted) {
		this->rectSource.left = (frame * moveRect);
	}
	else {
		this->rectSource.left = this->resetRect + (frame * this->moveRect);
	}

	this->sprite.setTextureRect(rectSource);
}

void Animation::resetAnimationHandler(bool& trigger) {
	if (this->boolHasResetted == true) {
		this->boolHasResetted = false;
		this->rectSource.left = 0;
		trigger = false;
	}
}

bool Animation::hasResetted() {
	return this->boolHasResetted;
}
