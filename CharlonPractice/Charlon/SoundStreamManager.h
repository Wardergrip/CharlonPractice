#pragma once
#include <map>
#include <vector>

class SoundStream;

class SoundStreamManager final
{
public:
	SoundStreamManager(const std::string& filePath);
	SoundStreamManager(const SoundStreamManager& other) = delete;
	SoundStreamManager& operator=(const SoundStreamManager& other) = delete;
	SoundStreamManager(SoundStreamManager&& other) = delete;
	SoundStreamManager& operator=(SoundStreamManager&& other) = delete;
	~SoundStreamManager();

	SoundStream* operator[](const std::string& name);
	const SoundStream* operator[](const std::string& name) const;

	SoundStream* GetSoundStream(const std::string& name);
	const SoundStream* GetSoundStream(const std::string& name) const;

	SoundStream* Play(const std::string& name, bool repeat = false);
	const SoundStream* Play(const std::string& name, bool repeat = false) const;

	bool IsPlaying(const std::string& name) const;
	void Pause(const std::string& name);
	void Resume(const std::string& name);
	void Mute(const std::string& name);
	void UnMute(const std::string& name);
private:
	std::map<std::string, SoundStream*> m_pSoundStreams;
	int m_PreviousVolume;
};



