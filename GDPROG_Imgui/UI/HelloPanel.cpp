// UI/HelloPanel.cpp : Example panel showing a text and a button.

#include "UI/HelloPanel.h"

// Pass the window title up to the Panel base class.
// Note: ImGui uses the title as the window's ID, so every panel needs a unique one.
HelloPanel::HelloPanel() : Panel("Hello, ImGui!")
{
}

// The panel's layout: call each section in the order it should appear,
// top to bottom.
void HelloPanel::DrawContent()
{
	DrawGreeting();

	// A horizontal line to visually separate the sections.
	ImGui::Separator();

	DrawClickButton();

	// TODO: Add more sections here, e.g. DrawSettings();
}

void HelloPanel::DrawGreeting()
{
	// ImGui::Text works like printf, e.g. ImGui::Text("Score: %d", score);
	ImGui::Text("This is some text.");
}

void HelloPanel::DrawClickButton()
{
	// ImGui::Button draws the button AND returns true on the frame it is clicked,
	// so the click handling goes right here inside the if.
	if (ImGui::Button("Click me"))
		clickCount++;

	// SameLine() places the next widget to the right instead of below.
	ImGui::SameLine();
	ImGui::Text("Clicked %d times", clickCount);
}
