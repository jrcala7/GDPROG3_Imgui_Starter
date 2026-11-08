Use this class as a template for your own panels:
   - Copy HelloPanel.h / HelloPanel.cpp into the UI folder and rename them.
   - Change the title passed to Panel(...) in the constructor.
   - Replace the Draw...() functions with your own sections.
   - Add the new .cpp to add_executable() in CMakeLists.txt.
   - Register the panel in main() with app.AddPanel(...).

For more info regarding widgets, visit https://pthom.github.io/imgui_explorer/?lib=imgui&demo=Widgets%2FBasic
