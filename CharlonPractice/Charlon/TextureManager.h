#pragma once
#include <map>

class Texture;

class TextureManager final
{
public:
	TextureManager(const std::string& filePath);
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;
	~TextureManager();

	Texture* operator[](const std::string& name);
	const Texture* operator[](const std::string& name) const;

	Texture* GetTexture(const std::string& name);
	const Texture* GetTexture(const std::string& name) const;
private:
	std::map<std::string, Texture*> m_pTextures;
};

