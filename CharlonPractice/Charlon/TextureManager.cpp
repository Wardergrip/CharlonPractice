#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <fstream>
#include <iostream>

TextureManager::TextureManager(const std::string& filePath)
{
	using json = nlohmann::json; // convenience
	std::ifstream input{ filePath }; // load file from filepath
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
			std::cout << "[TextureManager] Failed to load: " << filePath << "\n";
			return;
		}
	}
	json jFile{}; // make json object
	input >> jFile; // transfer all date from input to json object
	json jTextures{ jFile.at("textures") }; // make a new object that contains everything inside whatever we looked for
	//std::cout << std::setw(4) << jTextures << '\n';
	for (json::iterator it = jTextures.begin(); it != jTextures.end(); ++it) // go over all elements inside
	{
		//std::cout << it.key() << " : " << it.value() << "\n";
		m_pTextures[it.key()] = new Texture{ it.value() };
	}
}

TextureManager::~TextureManager()
{
	for (auto& sfx : m_pTextures)
	{
		delete sfx.second;
	}
	m_pTextures.clear();
}

Texture* TextureManager::operator[](const std::string& name)
{
	return GetTexture(name);
}

const Texture* TextureManager::operator[](const std::string& name) const
{
	return GetTexture(name);
}

Texture* TextureManager::GetTexture(const std::string& name)
{
	return (m_pTextures.at(name));
}

const Texture* TextureManager::GetTexture(const std::string& name) const
{
	return (m_pTextures.at(name));
}
