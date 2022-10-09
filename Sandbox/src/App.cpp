#include "App.h"

#include <iostream>

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Saddle/Core/Assert.h>
#include <Saddle/Core/Input.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>

#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>
#include <OpenGL/VertexArray.h>
#include <OpenGL/Texture2D.h>
#include <OpenGL/Quad.h>

const Vertex vertices[4] = 
{
    { glm::vec2(-0.5f,  0.5f), glm::vec2(0.f, 1.f) }, // Top left, 0
    { glm::vec2( 0.5f,  0.5f), glm::vec2(1.f, 1.f) }, // Top right, 1
    { glm::vec2(-0.5f, -0.5f), glm::vec2(0.f, 0.0) }, // Bottom left, 2
    { glm::vec2( 0.5f, -0.5f), glm::vec2(1.f, 0.0) }, // Bottom right, 3
    // { glm::vec2(-0.5f,  0.0f), glm::vec4(0.f, 0.f, 1.f, 1.0) }, // Middle left, 4
    // { glm::vec2( 0.0f,  0.5f), glm::vec4(0.f, 0.f, 1.f, 1.0) }, // Middle top, 5
};

void App::Run()
{
    auto vec = Window.GetFrameBufferSize();
    float ratio = vec.x / vec.y;

    glm::mat4 mvp = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
    glm::mat4 identity_matrix(1);

    BufferLayout layout({
        { "a_VertexPosition", BufferDataType::Vec2, true },
        { "a_TextureCoordinate", BufferDataType::Vec2, true },
    });

    Quad quad(vertices, layout);

    Texture2D texture("Sandbox/assets/images/kick_drum.png");
    Shader shader("Sandbox/assets/shaders/vertex_shader.glsl", "Sandbox/assets/shaders/fragment_shader.glsl");

    texture.Bind(0);

    shader.Bind();
    shader.SetUniformInt("u_Texture", 0);

    while(Window.IsOpen())
    {
        Renderer::Clear({ 1, 1, 1, 1 });

        // mvp = mvp * glm::translate(identity_matrix, glm::vec3(0.01f, 0.0f, 0.0f));
        shader.SetUniformMatrix4("u_MVP", mvp);

        Renderer::Submit(*quad.VertexArray, shader);
        Renderer::Render();

        EventSystem::PollEvents();
    }
}