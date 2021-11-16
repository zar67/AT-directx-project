#pragma once

#include <string>
#include <map>
#include <memory>
#include <Audio.h>

#include "SoundType.h"

class SoundManager
{
public:
	static void Initialise();

	static void LoadSoundFile(SoundType type, std::string filename);
	static void Play(SoundType type, bool loop = false);
	static void Stop(SoundType type, bool immediate = false);

	static void Update();
	static void Pause(bool paused);

private:
	static void ResetAudio();

	static std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
	static std::map<SoundType, std::vector<std::unique_ptr<DirectX::SoundEffect>>> m_soundsMap;
	static std::map<SoundType, std::vector<std::unique_ptr<DirectX::SoundEffectInstance>>> m_loopedSoundsMap;
};