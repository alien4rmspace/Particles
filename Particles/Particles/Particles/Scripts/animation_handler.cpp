#include "animation_handler.h"

void AnimationHandler::addAnimation(const string& name, Sprite& sprite, IntRect rectSource, unsigned short int moveRect, unsigned short int lastRect, unsigned short int resetRect, const float animationSpeed) {
	sprite.setTextureRect(rectSource);
	animations.emplace(name, _Animation{ sprite, rectSource, moveRect, lastRect, resetRect, animationSpeed });
}

void AnimationHandler::update(const string& name, const float dt) {
	// Using delta time to sync our animation speed with the user's computer spec.
	// Idk if it actually works, in Unity it's built into the api lol.
	_Animation& animation = animations.at(name);
	animation.time += dt;
	int frame = int(animation.time / animation.animationSpeed);

	// If animation's intRect exceeds our sprite intRect bounds (lastRect), 
	// reset the animation to the frame we want and reset the time as well.
	if (animation.rectSource.left >= animation.lastRect) {
		animation.rectSource.left = animation.resetRect; 
		animation.time = 0; // resets the clock

		animation.hasResetted = true;
	}
	else if (!animation.hasResetted){
		animation.rectSource.left = (frame * animation.moveRect);
	}
	else {
		animation.rectSource.left = animation.resetRect + (frame * animation.moveRect);
	}

	animation.sprite.setTextureRect(animation.rectSource);
}

void AnimationHandler::resetAnimationHandler(const string& name, bool& trigger) {
	_Animation& animation = animations.at(name);

	if (animation.hasResetted == true) {
		animation.hasResetted = false;
		animation.rectSource.left = 0;
		trigger = false;
	}
}

bool AnimationHandler::hasResetted(const string& name) {
	return this->animations.at(name).hasResetted;
}
