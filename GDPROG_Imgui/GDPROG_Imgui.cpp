// GDPROG_Imgui.cpp : Entry point. Create the app, add panels, run.

#include <memory>

#include "App.h"
#include "UI/HelloPanel.h"

int main()
{
	App app("GDPROG ImGui Starter", 1280, 720);
	if (!app.Init())
		return 1;

	// Register your panels here.
	app.AddPanel(std::make_unique<HelloPanel>());

	app.Run();
	return 0;
}
