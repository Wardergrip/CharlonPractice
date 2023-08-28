#pragma once
#include <map>
#include <vector>

class SoundEffect;

class SoundEffectManager final
{
public:
	SoundEffectManager(const std::string& filePath);
	SoundEffectManager(const SoundEffectManager& other) = delete;
	SoundEffectManager& operator=(const SoundEffectManager& other) = delete;
	SoundEffectManager(SoundEffectManager&& other) = delete;
	SoundEffectManager& operator=(SoundEffectManager&& other) = delete;
	~SoundEffectManager();

	SoundEffect* operator[](const std::string& name);
	const SoundEffect* operator[](const std::string& name) const;

	SoundEffect* GetSoundEffect(const std::string& name);
	const SoundEffect* GetSoundEffect(const std::string& name) const;

	SoundEffect* Play(const std::string& name, int loops = 0);
	const SoundEffect* Play(const std::string& name, int loops = 0) const;

	void MuteAll();
	void UnmuteAll();
	static void StopAll();
	static void PauseAll();
	static void ResumeAll();
private:
	std::map<std::string, SoundEffect*> m_pSoundEffects;
	std::vector<int> m_pPreviousVolumes;
};

