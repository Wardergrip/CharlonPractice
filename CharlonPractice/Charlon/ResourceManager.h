#pragma once

class TextureManager;
class SoundEffectManager;
class SoundStreamManager;

class Texture;
class SoundEffect;
class SoundStream;

class ResourceManager final
{
public:
	enum class Textures
	{
		missing,
		hoover,
		silverBullet
	};
	enum class SoundEffects
	{
		test
	};
	enum class SoundStreams
	{
		sadTheme
	};

	ResourceManager() = delete;

	static void Init(const std::string& filePath);
	static void CleanUp();

	static Texture* GetTexture(ResourceManager::Textures key);
	static Texture* GetTexture(const std::string& name);

	static SoundEffect* GetSFX(ResourceManager::SoundEffects key);
	static SoundEffect* GetSFX(const std::string& name);
	static SoundEffect* SFXPlay(ResourceManager::SoundEffects key);
	static SoundEffect* SFXPlay(const std::string& name, int loops = 0);
	static void SFXMuteAll();
	static void SFXUnmuteAll();
	static void SFXStopAll();
	static void SFXPauseAll();
	static void SFXResumeAll();

	static SoundStream* GetSoundStream(ResourceManager::SoundStreams key);
	static SoundStream* GetSoundStream(const std::string& name);
	static SoundStream* SSPlay(ResourceManager::SoundStreams key, bool repeat = false);
	static SoundStream* SSPlay(const std::string& name, bool repeat = false);
	static bool SSisPlaying(ResourceManager::SoundStreams key);
	static bool SSisPlaying(const std::string& name);
	static void SSPause(ResourceManager::SoundStreams key);
	static void SSPause(const std::string& name);
	static void SSResume(ResourceManager::SoundStreams key);
	static void SSResume(const std::string& name);
	static void SSMute(ResourceManager::SoundStreams key);
	static void SSMute(const std::string& name);
	static void SSUnMute(ResourceManager::SoundStreams key);
	static void SSUnMute(const std::string& name);
private:
	static std::string KeyToStr(ResourceManager::Textures key);
	static std::string KeyToStr(ResourceManager::SoundEffects key);
	static std::string KeyToStr(ResourceManager::SoundStreams key);

	static TextureManager* c_TextureManager;
	static SoundEffectManager* c_SoundEffectManager;
	static SoundStreamManager* c_SoundStreamManager;
};

