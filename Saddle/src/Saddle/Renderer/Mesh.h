#pragma once

#include <vector>
#include <memory>

#include <glm/vec3.hpp>

#include <assimp/scene.h>

#include "OpenGL/VertexArray.h"
#include "OpenGL/IndexBuffer.h"
#include "OpenGL/Texture2D.h"

namespace Saddle {

class Mesh {
public:
    Mesh(const std::string& path = "");
    ~Mesh();

    void LoadMesh(const std::string& path);

    uint32_t GetSubMeshCount() const { return m_SubMeshes.size(); }
    const std::string& GetPath() const { return m_Path; }

private:
    enum BufferIndex {
        Position,
        TextureCoordinate,
        Normal
    };
    struct SubMesh {
        uint32_t BaseVertex = 0;
        uint32_t BaseIndex = 0;
        uint32_t IndexCount = 0;
        uint32_t MaterialIndex = 0;
    };

    std::string m_Path;

    std::vector<SubMesh> m_SubMeshes;
    std::vector<std::unique_ptr<Texture2D>> m_Textures;

    std::vector<glm::vec3> m_Positions;
    std::vector<glm::vec3> m_Normals;
    std::vector<glm::vec2> m_TextureCoords;
    std::vector<uint32_t> m_Indices;

    std::unique_ptr<VertexBuffer> m_Buffers[3];
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexArray> m_VertexArray;

    void Clear();
    void LoadSubMesh(const aiMesh* mesh);
    void LoadMaterial(const aiScene* scene, const std::string& dir, uint32_t index);

    friend class Renderer;
};

}