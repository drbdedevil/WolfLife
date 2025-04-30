#include "ResourceManager.h"

#include "Utils.h"
#include "TextureObject.h"

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::loadTextures()
{
    std::string sheepAnimPath = Utils::getExecutablePath();

	m_dogTexture = new TextureObject((sheepAnimPath + std::string("/Resources/Dog.png")).c_str(), 7, 16, 3);
	m_wolfTexture = new TextureObject((sheepAnimPath + std::string("/Resources/Wolf.png")).c_str(), 7, 16, 3);
	m_sheepTexture = new TextureObject((sheepAnimPath + std::string("/Resources/Sheep.png")).c_str(), 9, 14, 3);
}

void ResourceManager::unloadTextures()
{
	delete m_dogTexture;
	delete m_wolfTexture;
	delete m_sheepTexture;
}

TextureObject* ResourceManager::getDogTexture() const
{
	return m_dogTexture;
}

TextureObject* ResourceManager::getWolfTexture() const
{
	return m_wolfTexture;
}

TextureObject* ResourceManager::getSheepTexture() const
{
	return m_sheepTexture;
}
