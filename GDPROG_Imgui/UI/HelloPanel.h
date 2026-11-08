// UI/HelloPanel.h : Example panel showing a text and a button.
//
// Use this class as a template for your own panels:
//   - Copy HelloPanel.h / HelloPanel.cpp into the UI folder and rename them.
//   - Change the title passed to Panel(...) in the constructor.
//   - Replace the Draw...() functions with your own sections.
//   - Add the new .cpp to add_executable() in CMakeLists.txt.
//   - Register the panel in main() with app.AddPanel(...).

#pragma once

#include "UI/Panel.h"

// HelloPanel inherits from Panel, so it gets an ImGui window (with a title bar
// and close button) for free. It only has to say WHAT goes inside the window.
class HelloPanel : public Panel
{
public:
	// Sets the window title shown in the panel's title bar.
	HelloPanel();

protected:
	// Called every frame by Panel::Render(), between ImGui::Begin() and
	// ImGui::End(). Everything drawn here appears inside this panel.
	void DrawContent() override;

private:
	// Each section of the panel is its own function so it is easy to find,
	// reorder or remove. Add a new function here for each new section.

	// Draws a line of plain text.
	void DrawGreeting();

	// Draws a button and a label showing how many times it was clicked.
	void DrawClickButton();

	// Panel state lives in member variables so it is kept between frames.
	// (ImGui redraws everything every frame; local variables would reset.)
	int clickCount = 0;
};
