#pragma once

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
};