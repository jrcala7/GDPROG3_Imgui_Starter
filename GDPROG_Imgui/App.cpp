// App.cpp : Owns the GLFW window, the ImGui context and the main loop.

#include "App.h"

#include <cstdio>

#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"   // ImGui backend: input and window events from GLFW
#include "imgui_impl_opengl3.h" // ImGui backend: drawing with OpenGL 3

// GLFW calls this whenever something goes wrong, so errors show up in the console.
static void GlfwErrorCallback(int error, const char* description)
{
	std::fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

App::App(std::string title, int width, int height)
	: title(std::move(title)), width(width), height(height)
{
}

App::~App()
{
	Shutdown();
}

bool App::Init()
{
	// The window must exist before ImGui can attach to it.
	if (!InitWindow())
		return false;

	InitImGui();
	return true;
}

void App::Run()
{
	// One loop iteration = one frame. ImGui is "immediate mode": the whole UI is
	// rebuilt from scratch every frame, which is why panels redraw every time.
	while (!glfwWindowShouldClose(window))
	{
		BeginFrame();
		DrawPanels();
		EndFrame();
	}
}

void App::AddPanel(std::unique_ptr<Panel> panel)
{
	panels.push_back(std::move(panel));
}

bool App::InitWindow()
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return false;

	// Ask for an OpenGL 3.3 core context (matches "#version 330" in InitImGui).
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	// macOS only provides core contexts when forward-compatible is set.
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	// Make this window's OpenGL context the one all GL calls draw into.
	glfwMakeContextCurrent(window);

	// Enable vsync: limits the loop to the monitor's refresh rate.
	glfwSwapInterval(1);
	return true;
}

void App::InitImGui()
{
	// Make sure the ImGui headers and compiled library are the same version.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Let users move between widgets with the keyboard (Tab, arrows, Enter).
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Built-in color themes: StyleColorsDark, StyleColorsLight, StyleColorsClassic.
	ImGui::StyleColorsDark();

	// Connect ImGui to GLFW (input) and OpenGL (rendering).
	// "true" lets ImGui install its own GLFW input callbacks.
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void App::BeginFrame()
{
	// Process keyboard, mouse and window events (resize, close, ...).
	glfwPollEvents();

	// Start a new ImGui frame. Backends first, then ImGui itself.
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void App::DrawPanels()
{
	// Every ImGui:: widget call must happen between NewFrame() and Render(),
	// which is exactly where this function runs.
	for (auto& panel : panels)
	{
		panel->Update(); // non-UI logic
		panel->Render(); // ImGui widgets
	}
}

void App::EndFrame()
{
	// Turn this frame's widget calls into draw data.
	ImGui::Render();

	// Match the OpenGL viewport to the window size (it may have been resized).
	int displayW, displayH;
	glfwGetFramebufferSize(window, &displayW, &displayH);
	glViewport(0, 0, displayW, displayH);

	// Clear the background, then draw ImGui on top.
	glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Show the finished frame (double buffering: draw off-screen, then swap).
	glfwSwapBuffers(window);
}

void App::Shutdown()
{
	// Already shut down, or Init() never succeeded.
	if (window == nullptr)
		return;

	// Destroy panels first, while ImGui still exists.
	panels.clear();

	// Shut down in the reverse order of InitImGui().
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Then the window and GLFW itself.
	glfwDestroyWindow(window);
	glfwTerminate();
	window = nullptr;
}
