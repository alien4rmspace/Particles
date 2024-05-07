#include "sound_manager.h"

SoundManager::~SoundManager() {
  for (auto& pair : soundBuffers) {
    // I can't get this to work I keep getting an exception thrown "Access violation".
    // I'm assuming this gets deleted somewhere else and I'm no longer able to delete it. -DS

    //delete pair.second;
  }
}

void SoundManager::loadBuffer(const string& name, const string& buffer) {
  SoundBuffer* soundBuffer = new SoundBuffer;
  if (!soundBuffer->loadFromFile(buffer)) {
    cout << "Could not load " << buffer << endl;
    delete soundBuffer; 
    return;
  }
  this->soundBuffers[name] = soundBuffer;

  Sound sound;
  sound.setBuffer(*(this->soundBuffers.at(name)));
  this->sounds[name] = sound;
}

const SoundBuffer& SoundManager::getBuffer(const string& soundBuffer) const {
  auto buffer = soundBuffers.find(soundBuffer);
  // Check to see if soundBuffer is a valid key to a mapped value.
  if (buffer != soundBuffers.end()) {
    return *(buffer->second);
  }
  else {
    throw out_of_range("Sound buffer not found " + soundBuffer);
  }
}

void SoundManager::playSound(const string& soundName) {
  auto soundIterator = sounds.find(soundName);
  // Check to see if soundBuffer is a valid key to a mapped value.
  if (soundIterator != sounds.end()) {
    Sound& sound = (soundIterator->second);
    sound.play();
  }
  else {
    throw out_of_range("Sound buffer not found " + soundName);
  }
}

Sound& SoundManager::getSound(const string& soundName) {
  auto soundIterator = sounds.find(soundName);
  // Check to see if soundBuffer is a valid key to a mapped value.
  if (soundIterator != sounds.end()) {
    return soundIterator->second;
  }
  else {
    throw out_of_range("Sound buffer not found " + soundName);
  }
}
