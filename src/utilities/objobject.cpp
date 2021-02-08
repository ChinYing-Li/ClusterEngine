#include <iostream>
#include <cmath>

#include "src/ext/objloader.h"
#include "shader.h"
#include "objobject.h"

namespace Cluster
{
extern objl::Loader obj_loader;

Obj::
Obj(fs::path obj_path, unsigned int num_instance):
m_instance(num_instance)
{
    bool loaded = obj_loader.LoadFile(obj_path.c_str());
    if(loaded)
    {
        for(int i = 0; i < obj_loader.LoadedMeshes.size(); ++i)
        {
            m_meshes.push_back(Mesh(obj_loader.LoadedMeshes[i], m_instance));
        }
    }
}

void Obj::
render(Shader& shader)
{
    for(Mesh& mesh: m_meshes)
    {
        mesh.render(shader);
    }
}

void Obj::
set_instance_mat(std::vector<glm::mat4> &instance_mat)
{
    for(Mesh& m: m_meshes)
    {
        m.send_instance_matrices(instance_mat);
    }
}

}
