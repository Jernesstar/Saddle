#version 450 core

uniform mat4 u_Model;
uniform mat4 u_ViewProj;

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

layout(location = 0) out vec3 v_Position;
layout(location = 1) out vec3 v_Normal;

void main()
{
    gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0);
    v_Position = a_Position;
    v_Normal = a_Normal;
}