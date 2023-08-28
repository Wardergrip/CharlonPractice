#include "pch.h"
#include "ResourceManager.h"

#include "TextureManager.h"
#include "SoundEffectManager.h"
#include "SoundStreamManager.h"

TextureManager* ResourceManager::c_TextureManager{nullptr};
SoundEffectManager* ResourceManager::c_SoundEffectManager{nullptr};
SoundStreamManager* ResourceManager::c_SoundStreamManager{ nullptr };

void ResourceManager::Init(const std::string& filePath)
{
	if (c_TextureManager || c_SoundEffectManager || c_SoundStreamManager)
	{
		return;
	}
	c_TextureManager = new TextureManager{ filePath };
	c_SoundEffectManager = new SoundEffectManager{ filePath };
	c_SoundStreamManager = new SoundStreamManager{ filePath };
}

void ResourceManager::CleanUp()
{
	delete c_TextureManager;
	c_TextureManager = nullptr;
	delete c_SoundEffectManager;
	c_SoundEffectManager = nullptr;
	delete c_SoundStreamManager;
	c_SoundStreamManager = nullptr;
}

Texture* ResourceManager::GetTexture(ResourceManager::Textures key)
{
	std::string str{ KeyToStr(key) };
	if (str.empty())
	{
		return nullptr;
	}
	return GetTexture(str);
}

Texture* ResourceManager::GetTexture(const std::string& name)
{
    return c_TextureManager->GetTexture(name);
}

SoundEffect* ResourceManager::GetSFX(ResourceManager::SoundEffects key)
{
	return c_SoundEffectManager->GetSoundEffect(KeyToStr(key));
}

SoundEffect* ResourceManager::GetSFX(const std::string& name)
{
	return c_SoundEffectManager->GetSoundEffect(name);
}

SoundEffect* ResourceManager::SFXPlay(ResourceManager::SoundEffects key)
{
	return SFXPlay(KeyToStr(key));
}

SoundEffect* ResourceManager::SFXPlay(const std::string& name, int loops)
{
	return c_SoundEffectManager->Play(name,loops);
}

void ResourceManager::SFXMuteAll()
{
	c_SoundEffectManager->MuteAll();
}

void ResourceManager::SFXUnmuteAll()
{
	c_SoundEffectManager->UnmuteAll();
}

void ResourceManager::SFXStopAll()
{
	c_SoundEffectManager->StopAll();
}

void ResourceManager::SFXPauseAll()
{
	c_SoundEffectManager->PauseAll();
}

void ResourceManager::SFXResumeAll()
{
	c_SoundEffectManager->ResumeAll();
}

SoundStream* ResourceManager::GetSoundStream(ResourceManager::SoundStreams key)
{
	
	return GetSoundStream(KeyToStr(key));
}

SoundStream* ResourceManager::GetSoundStream(const std::string& name)
{
	return c_SoundStreamManager->GetSoundStream(name);
}

SoundStream* ResourceManager::SSPlay(ResourceManager::SoundStreams key, bool repeat)
{
	return SSPlay(KeyToStr(key),repeat);;
}

SoundStream* ResourceManager::SSPlay(const std::string& name, bool repeat)
{
	return c_SoundStreamManager->Play(name,repeat);
}

bool ResourceManager::SSisPlaying(ResourceManager::SoundStreams key)
{
	return SSisPlaying(KeyToStr(key));
}

bool ResourceManager::SSisPlaying(const std::string& name)
{
	return c_SoundStreamManager->IsPlaying(name);
}

void ResourceManager::SSPause(ResourceManager::SoundStreams key)
{
	SSPause(KeyToStr(key));
}

void ResourceManager::SSPause(const std::string& name)
{
	c_SoundStreamManager->Pause(name);
}

void ResourceManager::SSResume(ResourceManager::SoundStreams key)
{
	SSResume(KeyToStr(key));
}

void ResourceManager::SSResume(const std::string& name)
{
	c_SoundStreamManager->Resume(name);
}

void ResourceManager::SSMute(ResourceManager::SoundStreams key)
{
	SSMute(KeyToStr(key));
}

void ResourceManager::SSMute(const std::string& name)
{
	c_SoundStreamManager->Mute(name);
}

void ResourceManager::SSUnMute(ResourceManager::SoundStreams key)
{
	SSUnMute(KeyToStr(key));
}

void ResourceManager::SSUnMute(const std::string& name)
{
	c_SoundStreamManager->UnMute(name);
}

std::string ResourceManager::KeyToStr(ResourceManager::Textures key)
{
	switch (key)
	{
	case ResourceManager::Textures::missing:
		return "missing";
		break;
	case ResourceManager::Textures::hoover:
		return "hoover";
	case ResourceManager::Textures::silverBullet:
		return "silverBullet";
	default:
		break;
	}
    return std::string();
}

std::string ResourceManager::KeyToStr(ResourceManager::SoundEffects key)
{
	switch (key)
	{
	case ResourceManager::SoundEffects::test:
		return "test";
		break;
	default:
		break;
	}
	return std::string();
}

std::string ResourceManager::KeyToStr(ResourceManager::SoundStreams key)
{
	switch (key)
	{
	case ResourceManager::SoundStreams::sadTheme:
		return "sadTheme";
		break;
	default:
		break;
	}
	return std::string();
}
