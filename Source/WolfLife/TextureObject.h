#pragma once

#include <string>
#include "raylib.h"

class TextureObject
{
public:
	TextureObject(const std::string& path, int frameWidth, int frameHeight, int totalFrames);
	~TextureObject();

	void setCurrentFrame(int newFrame);

	int getFrameWidth() const;
	int getFrameHeight() const;
	int getTotalFrames() const;
	int getCurrentFrame() const;

	Texture2D* getTexture();

	bool isLoad() const;
private:
	Texture2D m_texture;

	int m_frameWidth;
	int m_frameHeight;
	int m_totalFrames;

	int m_currentFrame = 0;

	bool bIsLoad = false;
};