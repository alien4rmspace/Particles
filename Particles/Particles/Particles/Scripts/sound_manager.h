#pragma once

#include<SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include<vector>
#include<unordered_map>
#include <iostream>

using namespace std;
using namespace sf;

class SoundManager {
public:
	SoundManager() {
		cout << "Sound Manager loaded successfully." << endl;
	}
	~SoundManager();

	void loadBuffer(const string& name, const string& buffer);
	const SoundBuffer& getBuffer(const string& soundBuffer) const;

	void playSound(const string& sound);
	Sound& getSound(const string& soundName);

private:
	unordered_map<string, SoundBuffer*> soundBuffers;
	unordered_map<string, Sound> sounds;
};