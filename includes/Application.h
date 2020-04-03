#pragma once

#include "helper/Singleton.h"

enum class ApplicationState
{
	Started,
	Running,
	Stopped
};

class Application
{

	GE_DECLARE_SINGLETON(Application)

public:

	void Initialize();
	void Run();
	void Shutdown();

private:

	bool bShutdown = false;
	class Window* win = nullptr;
	ApplicationState meAppState = ApplicationState::Stopped;

	class GameInstance* game = nullptr;
};
