#include "pch.h"
#include "SoundStreamManager.h"
#include "SoundStream.h"
#include <fstream>
#include <iostream>

SoundStreamManager::SoundStreamManager(const std::string& filePath)
{
	using json = nlohmann::json;
	std::ifstream input{ filePath };
	try
	{
		if (input.fail())
		{
			throw 1;
		}
	}
	catch (int errC)
	{
		if (errC == 1)
		{
			std::cout << "[SoundStreamManager] Failed to load: " << filePath << "\n";
			return;
		}
	}
	json jFile{};
	input >> jFile;
	json jSoundStreams{ jFile.at("soundstreams") };
	//std::cout << std::setw(4) << jTextures << '\n';
	for (json::iterator it = jSoundStreams.begin(); it != jSoundStreams.end(); ++it)
	{
		//std::cout << it.key() << " : " << it.value() << "\n";
		m_pSoundStreams[it.key()] = new SoundStream{ it.value() };
	}
}

SoundStreamManager::~SoundStreamManager()
{
	for (auto& sfx : m_pSoundStreams)
	{
		delete sfx.second;
	}
	m_pSoundStreams.clear();
}

SoundStream* SoundStreamManager::operator[](const std::string& name)
{
	return m_pSoundStreams.at(name);
}

const SoundStream* SoundStreamManager::operator[](const std::string& name) const
{
	return m_pSoundStreams.at(name);
}

SoundStream* SoundStreamManager::GetSoundStream(const std::string& name)
{
	return m_pSoundStreams.at(name);
}

const SoundStream* SoundStreamManager::GetSoundStream(const std::string& name) const
{
	return m_pSoundStreams.at(name);
}

SoundStream* SoundStreamManager::Play(const std::string& name, bool repeat)
{
	GetSoundStream(name)->Play(repeat);
	return GetSoundStream(name);
}

const SoundStream* SoundStreamManager::Play(const std::string& name, bool repeat) const
{
	GetSoundStream(name)->Play(repeat);
	return GetSoundStream(name);
}

bool SoundStreamManager::IsPlaying(const std::string& name) const
{
	return GetSoundStream(name)->IsPlaying();
}

void SoundStreamManager::Pause(const std::string& name)
{
	GetSoundStream(name)->Pause();
}

void SoundStreamManager::Resume(const std::string& name)
{
	GetSoundStream(name)->Resume();
}

void SoundStreamManager::Mute(const std::string& name)
{
	m_PreviousVolume = GetSoundStream(name)->GetVolume();
	GetSoundStream(name)->SetVolume(0);
}

void SoundStreamManager::UnMute(const std::string& name)
{
	if (m_PreviousVolume == -1)
	{
		return;
	}

	GetSoundStream(name)->SetVolume(m_PreviousVolume);
	m_PreviousVolume = -1;
}
