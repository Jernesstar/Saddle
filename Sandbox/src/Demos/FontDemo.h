#include <unordered_map>

#include <ft2build.h>
#include <freetype/freetype.h>

#include <glm/vec3.hpp>

#include <Saddle/Core/Application.h>
#include <Saddle/Renderer/Renderer2D.h>
#include <Saddle/Renderer/OrthographicCamera.h>
#include <Saddle/Renderer/StereographicCamera.h>
#include <Saddle/Renderer/CameraController.h>
#include <Saddle/ECS/Components.h>
#include <Saddle/Text/Font.h>
#include <Saddle/Text/Text.h>

using namespace Saddle;

class FontDemo : public Application {
public:
    FontDemo();

    void OnUpdate(TimeStep ts) override;

private:
    Font m_Font{ "Sandbox/assets/fonts/pixel_font.ttf", 0, 48 };
    Text m_Text{ "This is not a piece of sample text", m_Font, glm::vec4(0.6f, 0.7f, 0.8f, 1.0f) };

    OrthographicCamera camera{ 0.0, 1600.0f, 0.0f, 900.0f };
    StereographicCamera camera2{ 90.0f, 0.0f, 1.0f, 1600, 900 };
    CameraController controller{ camera2 };
};

FontDemo::FontDemo()
{
    EventSystem::RegisterEventListener<KeyPressedEvent>(
    [](const KeyPressedEvent& event) {
        if(event.Key == Key::Escape)
            Application::Close();
    });

    camera2.SetPosition({ 0.0f, 0.0f, 500.0f });
    controller.TranslationSpeed = 0.5f;
}

void FontDemo::OnUpdate(TimeStep ts)
{
    Renderer::Clear({ });
    Renderer2D::BeginScene(camera2);

    Renderer2D::DrawText(m_Text, glm::vec2(500.0f, 400.0f));
    Renderer2D::DrawQuad(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(200.0f, 300.0f), glm::vec2(50.0f, 50.0f));

    Renderer2D::EndScene();
}