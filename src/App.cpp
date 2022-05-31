#include "../include/App.h"
#include "../include/imgui.h"
#include "../include/imgui_impl_sdl.h"
#include "../include/imgui_impl_sdlrenderer.h"
#include "implot.h"

#include <algorithm>
#include <vector>

App::App() {

        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
            0) {
                printf("Error: %s\n", SDL_GetError());
        }

        // Setup window
        SDL_WindowFlags window_flags =
                (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
        mwindow = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example",
                                   SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                   1280, 720, window_flags);

        // Setup SDL_Renderer instance
        mrenderer = SDL_CreateRenderer(
                mwindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if (mrenderer == NULL) {
                SDL_Log("Error creating SDL_Renderer!");
                return;
        }
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;
        // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable
        // Keyboard Controls io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; //
        // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        // ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(mwindow, mrenderer);
        ImGui_ImplSDLRenderer_Init(mrenderer);
}

void App::Run() {
        while (open) {
                ImGui_ImplSDLRenderer_NewFrame();
                ImGui_ImplSDL2_NewFrame();
                ImGui::NewFrame();

                Pollevents();
                Update();
                Draw();
        }
}

void App::Update() {

        static std::vector<float> framerates;
        static std::vector<int> nums;

        if (framerates.size() >= 100) {
                framerates.erase(framerates.begin());
        }
        framerates.push_back(ImGui::GetIO().Framerate);


        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and
                                       // append into it.

        ImVec2 graphS = ImVec2(500,500);

        ImGui::PlotLines("graph",framerates.data(),framerates.size(),0,NULL,100,20,graphS);



        ImGui::End();
}

void App::Pollevents() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                        open = false;
                if (event.type == SDL_WINDOWEVENT &&
                    event.window.event == SDL_WINDOWEVENT_CLOSE &&
                    event.window.windowID == SDL_GetWindowID(mwindow))
                        open = false;
        }
}

void App::Draw() {
        ImGui::Render();
        SDL_SetRenderDrawColor(
                mrenderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
                (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(mrenderer);
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(mrenderer);
}

App::~App() {

        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(mrenderer);
        SDL_DestroyWindow(mwindow);
        SDL_Quit();
}
