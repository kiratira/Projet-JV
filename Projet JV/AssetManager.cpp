#include "AssetManager.h"
#include <assert.h>


AssetManager* AssetManager::sInstance = nullptr;

AssetManager::AssetManager() 
{
	assert(sInstance == nullptr);
	sInstance = this;
}
AssetManager::~AssetManager() {

}
sf::Texture& AssetManager::GetTexture(std::string const& filename) 
{
	auto& textMap = sInstance->m_Textures; //texture Map
	auto search = textMap.find("Asset/Textures/" + filename);

	if (search != textMap.end())
	{
		return search->second;
	}
	else
	{
		auto& texture = textMap["Asset/Textures/" + filename];
		texture.loadFromFile("Asset/Textures/" + filename);
		return texture;
	}
}

sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string const& filename)
{
	auto& soundMap = sInstance->m_SoundBuffers; //Sound Map
	auto search = soundMap.find("Asset/Sounds/" + filename);

	if (search != soundMap.end())
	{
		return search->second;
	}
	else
	{
		auto& sound = soundMap["Asset/Sounds/" + filename];
		sound.loadFromFile("Asset/Sounds/" + filename);
		return sound;
	}
}

sf::Font& AssetManager::GetFont(std::string const& filename)
{
	auto& fontMap = sInstance->m_Fonts; //Fonts Map
	auto search = fontMap.find("Asset/Fonts/" + filename);

	if (search != fontMap.end())
	{
		return search->second;
	}
	else
	{
		auto& sound = fontMap["Asset/Fonts/" + filename];
		sound.loadFromFile("Asset/Fonts/" + filename);
		return sound;
	}
}