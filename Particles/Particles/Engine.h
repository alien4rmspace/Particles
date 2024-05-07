#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <cmath>
#include "Particle.h"
#include "animation_handler.h"
#include "sprite_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"

using namespace sf;
using namespace std;

class Engine
{
public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

	void followMouse(Sprite& sprite);
private:
	// A regular RenderWindow
	RenderWindow m_window;

	//vector for Particles
	vector<Particle> m_particles;

	TextureManager textureManager;

	SpriteManager spriteManager;

	AnimationHandler animationHandler;

	SoundManager soundManager;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

	bool skill_3_active = false;
	bool skill_4_active = false;
	bool skill_4_sound_played = false;
	bool ghost_active = true;
	bool ghost_vanish = false;
	bool ghost_vanish_sound_played = false;
	bool ghost_appear = false;
	bool ghost_appear_sound_played = false;
	Vector2f mousePosition;
	Vector2f lastClickedPosition;

	// Debug Variables
	bool debug_active = false;
	RectangleShape rectangle;
	RectangleShape square;
	Font debugFont;
	Text debugText;
};