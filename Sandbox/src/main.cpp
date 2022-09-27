#include <linmath.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <glad/glad.h>

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Saddle/Core/Application.h>
#include <Saddle/Core/Assert.h>
#include <Saddle/Events/EventSystem.h>
#include <Saddle/Renderer/Renderer.h>
#include <Saddle/Core/Input.h>
#include <OpenGL/Shader.h>
#include <OpenGL/VertexBuffer.h>
#include <OpenGL/IndexBuffer.h>

using namespace Saddle;

class App : public Application {

Vertex vertices[4] = 
{
    {  -0.5f, -0.5f, 1.f, 0.f, 0.f },
    {  0.5f, -0.5f, 0.f, 1.f, 0.f },
    {  0.5f,  0.5f, 0.f, 0.f, 1.f },
    {  -0.5f,  0.5f, 1.f, 0.f, 0.f },
};

unsigned int indices[6] = {
    0, 1, 2,
    2, 3, 0
};

public:
    void Run()
    {
        GLuint program;
        GLint mvp_location, vertex_position, vertex_color;

        Shader vertex_shader("Sandbox/assets/shaders/vertex_shader.glsl", ShaderType::VertexShader);
        Shader fragment_shader("Sandbox/assets/shaders/fragment_shader.glsl", ShaderType::FragmentShader);
        Renderer::BindShader(vertex_shader, fragment_shader);
        
        program = Renderer::GetRendererID();
        mvp_location = glGetUniformLocation(program, "MVP");
        vertex_position = glGetAttribLocation(program, "vPos");
        vertex_color = glGetAttribLocation(program, "vCol");

        VertexBuffer vertex_buffer(sizeof(vertices), vertices);
        IndexBuffer index_buffer(6, indices);

        vertex_buffer.Bind();
        // Enabling a vertex attribute
        glEnableVertexAttribArray(vertex_position);
        // Setting the data for the attribute: 
        // 1. the attribute index, 2. the number of elements that make up the attribute,
        // 3. whether of not to normalize to values, 4. the size in bytes of the whole vertex
        // 5. a pointer to the start of the attribute in each vertex
        glVertexAttribPointer(vertex_position, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
        glEnableVertexAttribArray(vertex_color);
        glVertexAttribPointer(vertex_color, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)(sizeof(float) * 3));

        int width, height;
        glfwGetFramebufferSize(m_Window.GetNativeWindow(), &width, &height);

        float ratio = width / (float)height;
        glm::mat4 mvp = glm::ortho(-ratio, ratio, -1.0f, 1.0f, 1.0f, -1.0f);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

        while(m_Window.IsOpen())
        {
            Renderer::Clear();
            
            Renderer::Submit(vertex_buffer, index_buffer);
            Renderer::Render();

            EventSystem::PollEvents();
        }
    }
};

int main()
{
    Application::Init();

    App app;
    app.Run();

    Application::Close();
}