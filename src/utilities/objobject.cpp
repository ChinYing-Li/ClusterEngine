#include <iostream>
#include <cmath>

#include "src/ext/objloader.h"
#include "shader.h"
#include "objobject.h"

namespace Cluster
{
extern objl::Loader g_obj_loader;

Obj::
Obj(fs::path obj_path, unsigned int num_instance):
m_instance(num_instance)
{
    bool loaded = g_obj_loader.LoadFile(obj_path.c_str());
    if(loaded)
    {
      fs::path root_dir = obj_path.root_directory();
        for(int i = 0; i < g_obj_loader.LoadedMeshes.size(); ++i)
        {
            m_meshes.push_back(Mesh(g_obj_loader.LoadedMeshes[i], root_dir));
        }
    }
}

void Obj::
render(const Shader& shader)
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
