#include <stdio.h>
#include <stdlib.h>

#include "helper/Types.h"
#include "Application.h"

u32 main(u32 argc, AnsiString* argv) {
	Application& app = Application::GetInstance();

	app.Initialize();
	app.Run();
	app.Shutdown();

	return EXIT_SUCCESS;
}
