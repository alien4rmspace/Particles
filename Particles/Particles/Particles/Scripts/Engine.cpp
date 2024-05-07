#include "Engine.h"

Engine::Engine() {
	unsigned short windowWidth = VideoMode::getDesktopMode().width / 2;
	unsigned short windowHeight = VideoMode::getDesktopMode().height / 2;
	this->m_window.create(VideoMode(windowWidth, windowHeight), "The Parti-cular Game", Style::Default);

	// Manage Texts
	debugFont.loadFromFile("Fonts/Debug.otf");
	debugText.setFont(debugFont);
	debugText.setFillColor(Color::Red);
	debugText.setStyle(Text::Bold);
	debugText.setPosition(370, 50);
	debugText.setString("Debug Mode Active");

	// Manage Sounds
	soundManager.loadBuffer("background_sound", "Sounds/background_sound.wav");
	soundManager.loadBuffer("wind_sound", "Sounds/wind_sound.wav");
	soundManager.loadBuffer("electricity_sound", "Sounds/electricity_sound.wav");
	soundManager.loadBuffer("ice_sound", "Sounds/ice_sound.wav");
	soundManager.loadBuffer("charge_sound", "Sounds/charge_sound.wav");
	soundManager.loadBuffer("fire_sound", "Sounds/fire_sound.wav");
	soundManager.loadBuffer("water_sound", "Sounds/water_sound.wav");
	soundManager.loadBuffer("explosion_sound", "Sounds/explosion_sound.wav");
	soundManager.loadBuffer("ghost_shriek_sound", "Sounds/ghost_shriek_sound.mp3");

	// Initializing sprites and textures
	textureManager.loadTexture("background", "Textures/background.png");
	textureManager.loadTexture("idle_mage", "Textures/idle_mage_spritesheet.png");
	textureManager.loadTexture("skill_3", "Textures/skill_3.png");
	textureManager.loadTexture("skill_4", "Textures/skill_4.png");
	textureManager.loadTexture("skill_3_mage", "Textures/skill_3_mage_spritesheet.png");
	textureManager.loadTexture("idle_ghost", "Textures/idle_ghost_spritesheet.png");
	textureManager.loadTexture("vanish_ghost", "Textures/vanish_ghost_spritesheet.png");
	textureManager.loadTexture("appear_ghost", "Textures/appear_ghost_spritesheet.png");

	spriteManager.loadSprites("Settings/game_sprites.json", textureManager.getTextureManager());

	// Creating animation handlers
	IntRect rectSourceIdleMage(0, 0, 56, 67);
	float animationSpeed = 0.18;
	this->animationHandler.addAnimation("idle_mage", this->spriteManager.getSprite("idle_mage"), rectSourceIdleMage, 56, 280, 0, animationSpeed);

	IntRect rectSourceSkill3Mage(0, 0, 56, 67);
	animationSpeed = 0.18;
	this->animationHandler.addAnimation("skill_3_mage", this->spriteManager.getSprite("skill_3_mage"), rectSourceSkill3Mage, 56, 560, 0, animationSpeed);

	IntRect rectSourceIdleGhost(0, 0, 64, 80);
	animationSpeed = 0.18;
	this->animationHandler.addAnimation("idle_ghost", this->spriteManager.getSprite("idle_ghost"), rectSourceIdleGhost, 64, 448, 0, animationSpeed);

	IntRect rectSourceVanishGhost(0, 0, 64, 80);
	animationSpeed = 0.18;
	this->animationHandler.addAnimation("vanish_ghost", this->spriteManager.getSprite("vanish_ghost"), rectSourceVanishGhost, 64, 704, 0, animationSpeed);

	IntRect rectSourceAppearGhost(0, 0, 64, 80);
	animationSpeed = 0.18;
	this->animationHandler.addAnimation("appear_ghost", this->spriteManager.getSprite("appear_ghost"), rectSourceAppearGhost, 64, 384, 0, animationSpeed);
}

void Engine::run() {
	Clock clock;

	while (m_window.isOpen()) {
		Time elapsedTime = clock.restart();
		float dt = elapsedTime.asSeconds();

		if (!unit_tests_done) {
			unit_tests_done = true;
			cout << "Starting Particle unit tests..." << endl;
			Particle p(m_window, 4, { (int)m_window.getSize().x / 2, (int)m_window.getSize().y / 2 });
			p.unitTests();
			cout << "Unit tests complete.  Starting engine..." << endl;
		}

		input();

		update(dt);

		draw();
	}
}

void Engine::input() {
	Event event;

	while (this->m_window.pollEvent(event)) {
		switch (event.type) {
		case Event::Closed: {
			this->m_window.close();
			break;
		}
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape) {
				this->m_window.close();
				break;
			}
			if (event.key.code == Keyboard::Space) {
				if (debug_active == false) {
					debug_active = true;
					cout << "DEBUG MODE ACTIVATED" << endl;
				}
				else {
					debug_active = false;
				}
				break;
			}
		case Event::MouseButtonPressed: {
			if (event.mouseButton.button == Mouse::Left) {
				cout << "Left mouse button was pressed" << endl;
				cout << "mouse x: " << event.mouseButton.x << endl;
				cout << "mouse y: " << event.mouseButton.y << endl;

				if (skill_3_active == false) {
					int y = 495; // Fixed y position (floor level)
					skillPosition = Vector2f(event.mouseButton.x, y);

					unique_ptr<Skill_3> skill_3 = make_unique<Skill_3>(textureManager.getRef("skill_3"), animationHandler, soundManager, skillPosition, skill_id);
					skill_id++;

					gameObjects.push_back(move(skill_3));

				}
			}
			break;
		}
		case Event::MouseMoved: {
			this->mousePosition.x = event.mouseMove.x;
			this->mousePosition.y = event.mouseMove.y;
			break;
		}
		default: break;
		}
	}
}

void Engine::update(float dtAsSeconds) {
	if (!background_sound_played) {
		background_sound_played = true;
		soundManager.getSound("background_sound").setVolume(70.0f);
		soundManager.getSound("background_sound").setLoop(true);
		soundManager.getSound("background_sound").play();
	}

	for (auto it = m_particles.begin(); it != m_particles.end();) {
		if (it->getTTL() > 0.0) {
			it->update(dtAsSeconds);
			it++;
		}
		else {
			it = m_particles.erase(it);
		}
	}

	// Update ghost
	if (ghost_active) {
		animationHandler.update("idle_ghost", dtAsSeconds);
	}
	else if (ghost_vanish) {
		if (!ghost_vanish_sound_played) {
			ghost_vanish_sound_played = true;
			soundManager.playSound("ghost_shriek_sound");
		}
		if (animationHandler.hasResetted("vanish_ghost")) {
			animationHandler.resetAnimationHandler("vanish_ghost", ghost_vanish);
			ghost_vanish_sound_played = false;

			// Set sprite position out of view, so there are no collisions with invisible sprites.
			spriteManager.getSprite("idle_ghost").setPosition(0, 600);
			spriteManager.getSprite("vanish_ghost").setPosition(0, 600);
			spriteManager.getSprite("appear_ghost").setPosition(0, 600);
		}

		animationHandler.update("vanish_ghost", dtAsSeconds);
	}
	else if (!ghost_vanish && !ghost_appear) {
		// Create rng for spawning ghost
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<float> spawnCoordXDis(100, 900);
		uniform_real_distribution<float> spawnCoordyDis(40, 200);

		int spawnCoordX = spawnCoordXDis(gen);
		int spawnCoordY = spawnCoordyDis(gen);

		spriteManager.getSprite("idle_ghost").setPosition(spawnCoordX, spawnCoordY);
		spriteManager.getSprite("vanish_ghost").setPosition(spawnCoordX, spawnCoordY);
		spriteManager.getSprite("appear_ghost").setPosition(spawnCoordX, spawnCoordY);

		ghost_appear = true;
	}
	else if (ghost_appear) {
		if (!ghost_appear_sound_played) {
			ghost_appear_sound_played = true;
			soundManager.getSound("charge_sound").setVolume(30);
			soundManager.playSound("charge_sound");
		}
		if (animationHandler.hasResetted("appear_ghost")) {
			animationHandler.resetAnimationHandler("appear_ghost", ghost_appear);
			ghost_appear_sound_played = false;

			ghost_active = true;
		}
		animationHandler.update("appear_ghost", dtAsSeconds);
	}

	// Check for collision
	float idleGhostBufferLeft = 15.0f;
	float idleGhostBufferTop = 0.0f;
	float idleGhostBufferWidth = 32.f;
	float idleGhostBufferHeight = 40.0f;

	FloatRect idleGhostBounds = spriteManager.getSprite("idle_ghost").getGlobalBounds();
	idleGhostBounds.left += idleGhostBufferLeft;
	idleGhostBounds.top += idleGhostBufferTop;
	idleGhostBounds.width -= idleGhostBufferWidth;
	idleGhostBounds.height -= idleGhostBufferHeight;

	if (spriteManager.getSprite("skill_4").getGlobalBounds().intersects(spriteManager.getSprite("idle_ghost").getGlobalBounds())) {
		// Adjust out hit boxes
		float skill4BufferTop = 25.0f;
		float skill4BufferLeft = 43.0f;
		float skill4BufferWidth = 95.0f;
		float skill4BufferHeight = 85.0f;

		FloatRect skill4Bounds = spriteManager.getSprite("skill_4").getGlobalBounds();
		skill4Bounds.left += skill4BufferLeft;
		skill4Bounds.top += skill4BufferTop;
		skill4Bounds.width -= skill4BufferWidth;
		skill4Bounds.height -= skill4BufferHeight;

		// For Debugging Purposes
		if (debug_active) {
			square.setSize(Vector2f(skill4Bounds.width, skill4Bounds.height));
			square.setPosition(skill4Bounds.left, skill4Bounds.top);
			square.setFillColor(sf::Color::Transparent);
			square.setOutlineColor(sf::Color::Blue);
			square.setOutlineThickness(1.0f);

			rectangle.setSize(Vector2f(idleGhostBounds.width, idleGhostBounds.height));
			rectangle.setPosition(idleGhostBounds.left, idleGhostBounds.top);
			rectangle.setFillColor(sf::Color::Transparent);
			rectangle.setOutlineColor(sf::Color::Red);
			rectangle.setOutlineThickness(1.0f);
		}
	}

	for (auto objectPtr = gameObjects.begin(); objectPtr != gameObjects.end();) {
		if (auto skill3Ptr = dynamic_cast<Skill_3*>(objectPtr->get())) {
			if (skill3Ptr->isActive()) {
				skill_3_active = true;
				skill3Ptr->update(dtAsSeconds);
			}
			else if (!skill3Ptr->isActive() && skill3Ptr->isAlive()) {
				skill_3_active = false;
				skill3Ptr->setAlive(false);
				auto skill4 = make_unique<Skill_4>(textureManager.getRef("skill_4"), animationHandler, soundManager, skillPosition, skill_id);
				gameObjects.push_back(move(skill4));

				objectPtr = gameObjects.begin();
				continue;
			}
			else {
				objectPtr = gameObjects.erase(objectPtr);
				continue;
			}
		}
		else if (auto skill4Ptr = dynamic_cast<Skill_4*>(objectPtr->get())) {
			if (skill4Ptr->isAlive()) {
				skill4Ptr->update(dtAsSeconds);

				if (ghost_active && skill4Ptr->collide(idleGhostBounds)) {
					// Handle collision with ghost
					ghost_active = false;
					ghost_vanish = true;

					// Generate particles
					random_device rd;
					mt19937 gen(rd());
					uniform_real_distribution<float> pointsDis(25, 50);

					for (unsigned short i = 0; i < 10; i++) {
						Particle particle(this->m_window, pointsDis(gen), Vector2i(this->spriteManager.getSprite("idle_ghost").getPosition()));
						this->m_particles.push_back(particle);
					}
				}
			}
			else {
				objectPtr = gameObjects.erase(objectPtr);
				continue;
			}
		}
		++objectPtr;
	}

	// Update Mage and skills
	if (skill_3_active) {
		// Update mage sprite while casting skill_3
		animationHandler.update("skill_3_mage", dtAsSeconds);

	}
	else {
		followMouse(this->spriteManager.getSprite("idle_mage"));
		followMouse(this->spriteManager.getSprite("skill_3_mage"));

		animationHandler.update("idle_mage", dtAsSeconds);
	}
}

void Engine::draw() {
	this->m_window.clear();

	this->m_window.draw(spriteManager.getSprite("background"));

	for (const auto& particle : this->m_particles) {
		this->m_window.draw(particle);
	}

	// Draw mage 
	if (skill_3_active == true) {
		this->m_window.draw(spriteManager.getSprite("skill_3_mage"));

	}
	else if (skill_4_active == true) {
		this->m_window.draw(spriteManager.getSprite("skill_4"));
		this->m_window.draw(spriteManager.getSprite("idle_mage"));
	}
	else {
		this->m_window.draw(spriteManager.getSprite("idle_mage"));
	}

	// Draw ghost
	if (ghost_active) {
		this->m_window.draw(spriteManager.getSprite("idle_ghost"));
	}
	else if (ghost_vanish) {
		this->m_window.draw(spriteManager.getSprite("vanish_ghost"));
	}
	else if (ghost_appear) {
		this->m_window.draw(spriteManager.getSprite("appear_ghost"));
	}

	// Draw game objects (skill objects)
	for (const auto& objectPtr : gameObjects) {
		if (auto object = objectPtr.get()) {
			if (object->isAlive()) {
				this->m_window.draw(*object);
			}
		}
	}

	// For Debugging Purposes.
	if (debug_active) {
		m_window.draw(debugText);
		m_window.draw(rectangle);
		m_window.draw(square);
	}

	this->m_window.display();
}

void Engine::followMouse(Sprite& sprite) {
	if (this->mousePosition.x < 500) {
		sprite.setScale(Vector2f(-1, 1));
	}
	else {
		sprite.setScale(Vector2f(1, 1));
	}
}