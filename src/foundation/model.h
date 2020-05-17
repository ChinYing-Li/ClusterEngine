#include <vector>
#include <string>

#include "../../includes/gl_headers.h"
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class GLMatrices;

class Model
{
public:
    Model() = default;
    Model(const std::string path_to_model);
    ~Model() = default;
    
    void draw(glm::mat4& VP, GLuint shaderID, GLMatrices& mat);
private:
    std::string m_directory;
    std::vector<Mesh> m_meshes;
    std::vector<MeshTex> m_loaded_texture;
    
    void load(const std::string path_to_model);
    void process_node(aiNode* node, const aiScene *scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene *scene);
    std::vector<MeshTex> loadMaterialTextures(aiMaterial *mat, aiTextureType type, const std::string typeName);
    unsigned int TextureFromFile(const char *path, const std::string &directory);
};
