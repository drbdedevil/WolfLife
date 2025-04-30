#include "TextureObject.h"

TextureObject::TextureObject(const std::string& path, int frameWidth, int frameHeight, int totalFrames) 
	: m_frameWidth(frameWidth), m_frameHeight(frameHeight), m_totalFrames(totalFrames)
{
	m_texture = LoadTexture(path.c_str());
	if (m_texture.id != 0)
	{
		bIsLoad = true;
	}
}

TextureObject::~TextureObject()
{
	UnloadTexture(m_texture);
}

void TextureObject::setCurrentFrame(int newFrame)
{
	if (newFrame > m_totalFrames)
	{
		m_currentFrame = m_totalFrames;
		return;
	}
	else if (newFrame < 0)
	{
		m_currentFrame = 0;
		return;
	}
	m_currentFrame = newFrame;
}

int TextureObject::getFrameWidth() const
{
	return m_frameWidth;
}

int TextureObject::getFrameHeight() const
{
	return m_frameHeight;
}

int TextureObject::getTotalFrames() const
{
	return m_totalFrames;
}

int TextureObject::getCurrentFrame() const
{
	return m_currentFrame;
}

Texture2D* TextureObject::getTexture()
{
	return &m_texture;
}

bool TextureObject::isLoad() const
{
	return bIsLoad;
}
