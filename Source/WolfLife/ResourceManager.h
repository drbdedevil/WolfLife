#pragma once

#include "raylib.h"

class TextureObject;

class ResourceManager
{
public:
	static ResourceManager& getInstance()
	{
		static ResourceManager manager;
		return manager;
	}
	~ResourceManager();

	void loadTextures();
	void unloadTextures();

	TextureObject* getDogTexture() const;
	TextureObject* getWolfTexture() const;
	TextureObject* getSheepTexture() const;
private:
	ResourceManager();

	TextureObject* m_dogTexture;
	TextureObject* m_wolfTexture;
	TextureObject* m_sheepTexture;
};