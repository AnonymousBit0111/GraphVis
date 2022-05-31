#pragma once
#include "../include/imgui.h"
#include <SDL2/SDL.h>

class App{
public:
  App();
  void Run();

  ~App();

private:
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  bool open = true;
  SDL_Renderer* mrenderer;
  SDL_Window* mwindow;
private:
  void Update();
  void Pollevents();
  void Draw();

};
