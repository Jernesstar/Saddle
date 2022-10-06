#include "Renderer.h"

#include <glad/glad.h>

#include "Saddle/Core/Assert.h"
#include "Saddle/Core/Application.h"
#include "Saddle/Core/Log.h"

namespace Saddle {

void OpenGLMessageCallback(unsigned int source, unsigned int type, unsigned int id, 
    unsigned int severity, int length, const char* message, const void* userParam)
{
    switch(severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         SADDLE_CORE_LOG_ERROR(message);   return;
        case GL_DEBUG_SEVERITY_MEDIUM:       SADDLE_CORE_LOG_ERROR(message);   return;
        case GL_DEBUG_SEVERITY_LOW:          SADDLE_CORE_LOG_WARNING(message); return;
        case GL_DEBUG_SEVERITY_NOTIFICATION: SADDLE_CORE_LOG_INFO(message);    return;
    }
}

void Renderer::Init()
{
    m_Window = Application::Get().GetWindow().GetNativeWindow();

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(OpenGLMessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
}

void Renderer::Clear(glm::vec4 color)
{
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Submit(const VertexArray& vertex_array, const Shader& shader)
{
    shader.Bind();
    vertex_array.Bind();
    glDrawElements(GL_TRIANGLES, vertex_array.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    vertex_array.Unbind();
    shader.Unbind();
}

void Renderer::Render() { glfwSwapBuffers(m_Window); }

}