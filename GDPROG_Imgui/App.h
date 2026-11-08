// App.h : Owns the GLFW window, the ImGui context and the main loop.
//
// Students usually don't need to edit this file. To put things on screen,
// create a Panel (see UI/HelloPanel.h) and register it with AddPanel().
//
// Typical usage (see main() in GDPROG_Imgui.cpp):
//   App app("My App", 1280, 720);
//   if (!app.Init()) return 1;
//   app.AddPanel(std::make_unique<HelloPanel>());
//   app.Run();

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "UI/Panel.h"

// Forward declaration so this header doesn't need to include GLFW.
struct GLFWwindow;

class App
{
public:
	// Stores the window settings. Nothing is created until Init() is called.
	App(std::string title, int width, int height);

	// Cleans up ImGui and GLFW automatically when the App goes out of scope.
	~App();

	// The App owns a window, so copying it makes no sense; disable copies.
	App(const App&) = delete;
	App& operator=(const App&) = delete;

	// Creates the window and sets up ImGui.
	// Returns false if the window could not be created.
	bool Init();

	// Runs the main loop until the user closes the window.
	// Every frame: BeginFrame() -> DrawPanels() -> EndFrame().
	void Run();

	// Registers a panel to be updated and drawn every frame.
	// The App takes ownership, so pass it with std::make_unique<YourPanel>().
	void AddPanel(std::unique_ptr<Panel> panel);

private:
	// --- Setup (called from Init) ---

	// Initializes GLFW, creates the OS window and its OpenGL context.
	bool InitWindow();

	// Creates the ImGui context, sets the style and connects the GLFW and
	// OpenGL3 backends to the window.
	void InitImGui();

	// --- Per-frame steps (called from Run) ---

	// Reads keyboard/mouse input and starts a new ImGui frame.
	void BeginFrame();

	// Calls Update() then Render() on every registered panel.
	void DrawPanels();

	// Clears the screen, draws ImGui's output and shows it on the window.
	void EndFrame();

	// --- Cleanup (called from the destructor) ---

	// Shuts down ImGui and destroys the window, in reverse order of creation.
	void Shutdown();

	// Window settings passed into the constructor.
	std::string title;
	int width;
	int height;

	// The OS window, created by InitWindow().
	GLFWwindow* window = nullptr;

	// All panels, drawn in the order they were added.
	std::vector<std::unique_ptr<Panel>> panels;

	// Background color behind the panels (RGBA, 0.0 to 1.0).
	float clearColor[4] = { 0.15f, 0.15f, 0.18f, 1.0f };
};
