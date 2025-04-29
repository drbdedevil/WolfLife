#pragma once

#include "raylib.h"
#include <string>

class Application
{
public:
	static Application& getInstance()
	{
		static Application app;
		return app;
	}
	~Application();

	void run();
private:
	Application();

	void DrawTextCentered(const std::string& text, int fontSize, const Color& color, int screenWidth, int screenHeight, int padding = 20);
};