#include "SoundManager.h"
#include "StringConversion.h"

void SoundManager::Initialise()
{
	m_audioEngine = std::make_unique<DirectX::AudioEngine>();

	m_soundsMap.clear();
	m_loopedSoundsMap.clear();

	// Initialise Sounds
	LoadSoundFile(SoundType::MUSIC, "Assets\\Sound\\music.wav");
	LoadSoundFile(SoundType::LEVEL_COMPLETE, "Assets\\Sound\\level_complete.wav");
	LoadSoundFile(SoundType::PLAYER_INJURED, "Assets\\Sound\\player_injured.wav");
	LoadSoundFile(SoundType::PLAYER_DEATH, "Assets\\Sound\\player_death_one.wav");
	LoadSoundFile(SoundType::PLAYER_DEATH, "Assets\\Sound\\player_death_two.wav");
	LoadSoundFile(SoundType::ITEM_PICKUP, "Assets\\Sound\\item_pickup.wav");
	LoadSoundFile(SoundType::BULLET_PICKUP, "Assets\\Sound\\bullet_pickup.wav");
	LoadSoundFile(SoundType::FIST_FIRE, "Assets\\Sound\\fist_hit.wav");
	LoadSoundFile(SoundType::CHAINSAW_IDLE, "Assets\\Sound\\chainsaw_idle.wav");
	LoadSoundFile(SoundType::CHAINSAW_FIRE, "Assets\\Sound\\chainsaw_fire.wav");
	LoadSoundFile(SoundType::PISTOL_FIRE, "Assets\\Sound\\pistol_fire.wav");
	LoadSoundFile(SoundType::RIFLE_FIRE, "Assets\\Sound\\pistol_fire.wav");
	LoadSoundFile(SoundType::SHOTGUN_FIRE, "Assets\\Sound\\shotgun_fire.wav");
	LoadSoundFile(SoundType::CANNON_FIRE, "Assets\\Sound\\cannon_fire.wav");
	LoadSoundFile(SoundType::ZOMBIE_SIGHT, "Assets\\Sound\\zombie_sight.wav");
	LoadSoundFile(SoundType::ZOMBIE_ATTACK, "Assets\\Sound\\zombie_attack.wav");
	LoadSoundFile(SoundType::ZOMBIE_INJURED, "Assets\\Sound\\zombie_injured.wav");
	LoadSoundFile(SoundType::ZOMBIE_DEATH, "Assets\\Sound\\zombie_death_one.wav");
	LoadSoundFile(SoundType::ZOMBIE_DEATH, "Assets\\Sound\\zombie_death_two.wav");
	LoadSoundFile(SoundType::ZOMBIE_DEATH, "Assets\\Sound\\zombie_death_three.wav");
	LoadSoundFile(SoundType::DEMON_SIGHT, "Assets\\Sound\\demon_sight.wav");
	LoadSoundFile(SoundType::DEMON_ATTACK, "Assets\\Sound\\demon_attack.wav");
	LoadSoundFile(SoundType::DEMON_INJURED, "Assets\\Sound\\demon_injured.wav");
	LoadSoundFile(SoundType::DEMON_DEATH, "Assets\\Sound\\demon_death.wav");
	LoadSoundFile(SoundType::PUPPY_SIGHT, "Assets\\Sound\\puppy_sight.wav");
	LoadSoundFile(SoundType::PUPPY_ATTACK, "Assets\\Sound\\puppy_attack.wav");
	LoadSoundFile(SoundType::PUPPY_INJURED, "Assets\\Sound\\puppy_injured.wav");
	LoadSoundFile(SoundType::PUPPY_DEATH, "Assets\\Sound\\puppy_death.wav");
}

void SoundManager::LoadSoundFile(SoundType type, std::string filename)
{
	std::unique_ptr<DirectX::SoundEffect> soundEffect = std::make_unique<DirectX::SoundEffect>(
		m_audioEngine.get(), 
		StringConversion::StringToWide(filename).c_str()
	);

	m_soundsMap[type].push_back(std::move(soundEffect));
}

void SoundManager::Play(SoundType type, bool loop)
{
	int randomIndex = rand() % m_soundsMap[type].size();

	if (loop)
	{
		std::unique_ptr<DirectX::SoundEffectInstance> instance = m_soundsMap[type][randomIndex]->CreateInstance();
		instance->Play(true);
		m_loopedSoundsMap[type].push_back(std::move(instance));
	}
	else
	{
		m_soundsMap[type][randomIndex]->Play();
	}
}

void SoundManager::Stop(SoundType type, bool immediate)
{
	for (auto& instance : m_loopedSoundsMap[type])
	{
		instance->Stop(immediate);
	}

	m_loopedSoundsMap[type].clear();
}

void SoundManager::Update()
{
	if (!m_audioEngine->Update())
	{
		if (m_audioEngine->IsCriticalError())
		{
			ResetAudio();
		}
	}
}

void SoundManager::Pause(bool paused)
{
	if (paused)
	{
		m_audioEngine->Suspend();
	}
	else
	{
		m_audioEngine->Resume();
	}
}

void SoundManager::ResetAudio()
{
	if (m_audioEngine->Reset())
	{
		for (auto& mapVector : m_loopedSoundsMap)
		{
			for (auto& instance : mapVector.second)
			{
				instance->Play(true);
			}
		}
	}
}