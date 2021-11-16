#pragma once

#include <string>
#include <map>
#include <memory>
#include <Audio.h>

#include "SoundType.h"

class SoundManager
{
public:
	static SoundManager& GetInstance()
	{
		static SoundManager instance;
		return instance;
	}

	void Initialise();

	void LoadSoundFile(SoundType type, std::string filename);
	void Play(SoundType type, bool loop = false);
	void Stop(SoundType type, bool immediate = false);

	void Update();
	void Pause(bool paused);

private:
	void ResetAudio();

	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
	std::map<SoundType, std::vector<std::unique_ptr<DirectX::SoundEffect>>> m_soundsMap;
	std::map<SoundType, std::vector<std::unique_ptr<DirectX::SoundEffectInstance>>> m_loopedSoundsMap;
};