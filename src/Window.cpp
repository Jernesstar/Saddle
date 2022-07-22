#include "Window.h"

namespace Saddle {

Window::Window() : Width(0), Height(0)  { }

Window::Window(int width, int height, const std::string& window_title, Uint32 sdl_init_flags)
    : ui_elements(), game_objects(), sounds(), Width(width), Height(height)
{
    SDL_Init(sdl_init_flags);
    TTF_Init();
    // IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

    window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    Mix_CloseAudio();
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Window::AddUIElement(UI::UIElement& element)
{
    ui_elements.push_back(&element);
}

void Window::AddGameObject(GameObject& game_object)
{
    game_objects.push_back(&game_object);
}

void Window::AddSound(Sound& sound)
{
    sounds.push_back(&sound);
}

void Window::RenderUI()
{
    SDL_RenderClear(renderer);
    while(ui_elements.size() > 0)
    {
        UI::UIElement* element = ui_elements[ui_elements.size() - 1];
        SDL_RenderCopy(renderer, *element->GetTexture(), NULL, element->GetRect());
        ui_elements.pop_back();
    }
    SDL_RenderPresent(renderer);
}

void Window::RenderGameObjects()
{
    SDL_RenderClear(renderer);
    while(game_objects.size() > 0)
    {
        GameObject* game_object = game_objects[game_objects.size() - 1];
        SDL_RenderCopy(renderer, *game_object->GetTexture(), NULL, game_object->GetRect());
        game_objects.pop_back();
    }
    SDL_RenderPresent(renderer);
}

void Window::RenderScene()
{
    RenderGameObjects();
    RenderUI();
}

void Window::HandleEvent(SDL_Event& event)
{
    for(int i = 0; i < ui_elements.size(); i++)
    {
        ui_elements[i]->HandleEvent(event);
    }
    for(int i = 0; i < game_objects.size(); i++)
    {
        game_objects[i]->HandleEvent(event);
    }
}

SDL_Renderer** Window::GetRenderer()
{
    return &renderer;
}

SDL_Window** Window::GetWindow()
{
    return &window;
}

}