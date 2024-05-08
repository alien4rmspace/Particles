#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <random>
#include <cmath>
#include <thread>
#include <chrono>

#include "Particle.h"
#include "animation_handler.h"
#include "sprite_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "Skill_3.h"
#include "Skill_4.h"

const int SKILL_Y_VALUE = 495;

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
	vector<unique_ptr<GameObject>> gameObjects;

	TextureManager textureManager;
	SpriteManager spriteManager;
	SoundManager soundManager;

	AnimationHandler animationHandler;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();
	void ultimatePower();
	void loopThread();

	int skill_id = 0;
	bool unit_tests_done = false;
	bool background_sound_played = false;
	bool skill_3_active = false;
	bool skill_4_active = false;
	bool skill_4_sound_played = false;
	bool ghost_active = true;
	bool ghost_vanish = false;
	bool ghost_vanish_sound_played = false;
	bool ghost_appear = false;
	bool ghost_appear_sound_played = false;
	Vector2f mousePosition;
	Vector2f skillPosition;

	// Debug Variables
	bool debug_active = false;
	RectangleShape rectangle;
	Font debugFont;
	Text debugText;
};