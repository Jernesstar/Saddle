#include "Game.h"

#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Renderer/Renderer2D.h>

Game::Game()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event) {
        if(event.Key == Key::Escape)
            Application::Close();
    });

    uint32_t block_size = 30;
    std::string name = "Star";

    m_GameMode = new OnePlayerClassicSnake(name, block_size);
}

void Game::OnUpdate(TimeStep ts)
{
    Renderer::Clear({ 1.0f, 0.0f, 0.0f, 1.0f });

    
}
