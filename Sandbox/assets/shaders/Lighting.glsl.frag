#version 450 core

#define POINT_LIGHTS 4

layout(location = 0) in vec3 v_FragPosition;
layout(location = 1) in vec3 v_Normal;
layout(location = 2) in vec2 v_TextureCoordinate;

layout(location = 0) out vec4 FragColor;

struct Material {
    sampler2D Diffuse;
    sampler2D Specular;
    float Shininess;
};

struct DirectionalLight {
    vec3 Position;
    vec3 Direction;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

struct PointLight {
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float Constant;
    float Linear;
    float Quadratic;
};

struct SpotLight {
    vec3 Position;
    vec3 Direction;

    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;

    float CutoffAngle;
    float OuterCutoffAngle;
};

uniform vec3 u_CameraPosition;

uniform Material u_Material;

layout(binding = 0) uniform PointLight u_PointLights[POINT_LIGHTS];
uniform SpotLight u_SpotLight;

// layout(binding = 1) uniform SpotLight {
//     vec3 Position;
//     vec3 Direction;

//     vec3 Ambient;
//     vec3 Diffuse;
//     vec3 Specular;

//     float CutoffAngle;
//     float OuterCutoffAngle;
// } u_SpotLight;

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 view_dir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 view_dir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 view_dir);

void main()
{
    vec3 normal = normalize(v_Normal);
    vec3 view_dir = normalize(u_CameraPosition - v_FragPosition);

    vec3 result = vec3(0.0, 0.0, 0.0);
    result += CalcSpotLight(u_SpotLight, normal, view_dir);

    for(int i = 0; i < POINT_LIGHTS; i++)
        result += CalcPointLight(u_PointLights[i], normal, view_dir);

    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(light.Direction);
    vec3 reflect_dir = reflect(light_dir, normal);
    float diff = max(dot(normal, -light_dir), 0.0);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_Material.Shininess);

    vec3 ambient  = light.Ambient  * 1.0  * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 diffuse  = light.Diffuse  * diff * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.Specular, v_TextureCoordinate));
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(v_FragPosition - light.Position);
    vec3 reflect_dir = reflect(light_dir, normal);
    float diff = max(dot(normal, -light_dir), 0.0);
    float spec = pow(max(dot(view_dir, reflect_dir), 0.0), u_Material.Shininess);

    float dist = length(light.Position - v_FragPosition);
    float attenuation = 1.0 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));

    vec3 ambient  = light.Ambient  * 1.0  * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 diffuse  = light.Diffuse  * diff * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 specular = light.Specular * spec * vec3(texture(u_Material.Specular, v_TextureCoordinate));

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 view_dir)
{
    vec3 light_dir = normalize(v_FragPosition - light.Position);

    float theta = dot(light.Direction, normalize(-light_dir));
    float epsilon = light.OuterCutoffAngle - light.CutoffAngle;
    float intensity = clamp((theta - light.OuterCutoffAngle) / epsilon, 0.0, 1.0);

    vec3 ambient  = light.Ambient  * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 diffuse  = light.Diffuse  * vec3(texture(u_Material.Diffuse, v_TextureCoordinate));
    vec3 specular = light.Specular * vec3(texture(u_Material.Specular, v_TextureCoordinate));

    return (ambient + diffuse + specular) * intensity;
}