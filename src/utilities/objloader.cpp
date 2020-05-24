#include "objloader.h"

Loader::~Loader()
{
    LoadedMeshes.clear();
}

bool Loader::LoadFile(std::string Path)
{
    // If the file is not an .obj file return false
            if (Path.substr(Path.size() - 4, 4) != ".obj")
                return false;


            std::ifstream file(Path);

            if (!file.is_open())
                return false;

            LoadedMeshes.clear();
            LoadedVertices.clear();
            LoadedIndices.clear();

            std::vector<Vector3> Positions;
            std::vector<Vector2> TCoords;
            std::vector<Vector3> Normals;

            std::vector<Vertex> Vertices;
            std::vector<unsigned int> Indices;

            std::vector<std::string> MeshMatNames;

            bool listening = false;
            std::string meshname;

            Mesh tempMesh;

            #ifdef OBJL_CONSOLE_OUTPUT
            const unsigned int outputEveryNth = 1000;
            unsigned int outputIndicator = outputEveryNth;
            #endif

            std::string curline;
            while (std::getline(file, curline))
            {
                #ifdef OBJL_CONSOLE_OUTPUT
                if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1)
                {
                    if (!meshname.empty())
                    {
                        std::cout
                            << "\r- " << meshname
                            << "\t| vertices > " << Positions.size()
                            << "\t| texcoords > " << TCoords.size()
                            << "\t| normals > " << Normals.size()
                            << "\t| triangles > " << (Vertices.size() / 3)
                            << (!MeshMatNames.empty() ? "\t| material: " + MeshMatNames.back() : "");
                    }
                }
                #endif

                // Generate a Mesh Object or Prepare for an object to be created
                if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g')
                {
                    if (!listening)
                    {
                        listening = true;

                        if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
                        {
                            meshname = algorithm::tail(curline);
                        }
                        else
                        {
                            meshname = "unnamed";
                        }
                    }
                    else
                    {
                        // Generate the mesh to put into the array

                        if (!Indices.empty() && !Vertices.empty())
                        {
                            // Create Mesh
                            tempMesh = Mesh(Vertices, Indices);
                            tempMesh.MeshName = meshname;

                            // Insert Mesh
                            LoadedMeshes.push_back(tempMesh);

                            // Cleanup
                            Vertices.clear();
                            Indices.clear();
                            meshname.clear();

                            meshname = algorithm::tail(curline);
                        }
                        else
                        {
                            if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
                            {
                                meshname = algorithm::tail(curline);
                            }
                            else
                            {
                                meshname = "unnamed";
                            }
                        }
                    }
                    #ifdef OBJL_CONSOLE_OUTPUT
                    std::cout << std::endl;
                    outputIndicator = 0;
                    #endif
                }
                // Generate a Vertex Position
                if (algorithm::firstToken(curline) == "v")
                {
                    std::vector<std::string> spos;
                    Vector3 vpos;
                    algorithm::split(algorithm::tail(curline), spos, " ");

                    vpos.X = std::stof(spos[0]);
                    vpos.Y = std::stof(spos[1]);
                    vpos.Z = std::stof(spos[2]);

                    Positions.push_back(vpos);
                }
                // Generate a Vertex Texture Coordinate
                if (algorithm::firstToken(curline) == "vt")
                {
                    std::vector<std::string> stex;
                    Vector2 vtex;
                    algorithm::split(algorithm::tail(curline), stex, " ");

                    vtex.X = std::stof(stex[0]);
                    vtex.Y = std::stof(stex[1]);

                    TCoords.push_back(vtex);
                }
                // Generate a Vertex Normal;
                if (algorithm::firstToken(curline) == "vn")
                {
                    std::vector<std::string> snor;
                    Vector3 vnor;
                    algorithm::split(algorithm::tail(curline), snor, " ");

                    vnor.X = std::stof(snor[0]);
                    vnor.Y = std::stof(snor[1]);
                    vnor.Z = std::stof(snor[2]);

                    Normals.push_back(vnor);
                }
                // Generate a Face (vertices & indices)
                if (algorithm::firstToken(curline) == "f")
                {
                    // Generate the vertices
                    std::vector<Vertex> vVerts;
                    GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);

                    // Add Vertices
                    for (int i = 0; i < int(vVerts.size()); i++)
                    {
                        Vertices.push_back(vVerts[i]);

                        LoadedVertices.push_back(vVerts[i]);
                    }

                    std::vector<unsigned int> iIndices;

                    VertexTriangluation(iIndices, vVerts);

                    // Add Indices
                    for (int i = 0; i < int(iIndices.size()); i++)
                    {
                        unsigned int indnum = (unsigned int)((Vertices.size()) - vVerts.size()) + iIndices[i];
                        Indices.push_back(indnum);

                        indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
                        LoadedIndices.push_back(indnum);

                    }
                }
                // Get Mesh Material Name
                if (algorithm::firstToken(curline) == "usemtl")
                {
                    MeshMatNames.push_back(algorithm::tail(curline));

                    // Create new Mesh, if Material changes within a group
                    if (!Indices.empty() && !Vertices.empty())
                    {
                        // Create Mesh
                        tempMesh = Mesh(Vertices, Indices);
                        tempMesh.MeshName = meshname;
                        int i = 2;
                        while(1) {
                            tempMesh.MeshName = meshname + "_" + std::to_string(i);

                            for (auto &m : LoadedMeshes)
                                if (m.MeshName == tempMesh.MeshName)
                                    continue;
                            break;
                        }

                        // Insert Mesh
                        LoadedMeshes.push_back(tempMesh);

                        // Cleanup
                        Vertices.clear();
                        Indices.clear();
                    }

                    #ifdef OBJL_CONSOLE_OUTPUT
                    outputIndicator = 0;
                    #endif
                }
                // Load Materials
                if (algorithm::firstToken(curline) == "mtllib")
                {
                    // Generate LoadedMaterial

                    // Generate a path to the material file
                    std::vector<std::string> temp;
                    algorithm::split(Path, temp, "/");

                    std::string pathtomat = "";

                    if (temp.size() != 1)
                    {
                        for (int i = 0; i < temp.size() - 1; i++)
                        {
                            pathtomat += temp[i] + "/";
                        }
                    }


                    pathtomat += algorithm::tail(curline);

                    #ifdef OBJL_CONSOLE_OUTPUT
                    std::cout << std::endl << "- find materials in: " << pathtomat << std::endl;
                    #endif

                    // Load Materials
                    LoadMaterials(pathtomat);
                }
            }

            #ifdef OBJL_CONSOLE_OUTPUT
            std::cout << std::endl;
            #endif

            // Deal with last mesh

            if (!Indices.empty() && !Vertices.empty())
            {
                // Create Mesh
                tempMesh = Mesh(Vertices, Indices);
                tempMesh.MeshName = meshname;

                // Insert Mesh
                LoadedMeshes.push_back(tempMesh);
            }

            file.close();

            // Set Materials for each Mesh
            for (int i = 0; i < MeshMatNames.size(); i++)
            {
                std::string matname = MeshMatNames[i];

                // Find corresponding material name in loaded materials
                // when found copy material variables into mesh material
                for (int j = 0; j < LoadedMaterials.size(); j++)
                {
                    if (LoadedMaterials[j].name == matname)
                    {
                        LoadedMeshes[i].MeshMaterial = LoadedMaterials[j];
                        break;
                    }
                }
            }

            if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        // Loaded Mesh Objects
        std::vector<Mesh> LoadedMeshes;
        // Loaded Vertex Objects
        std::vector<Vertex> LoadedVertices;
        // Loaded Index Positions
        std::vector<unsigned int> LoadedIndices;
        // Loaded Material Objects
        std::vector<Material> LoadedMaterials;

    private:
        // Generate vertices from a list of positions,
        //    tcoords, normals and a face line
        void GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
            const std::vector<Vector3>& iPositions,
            const std::vector<Vector2>& iTCoords,
            const std::vector<Vector3>& iNormals,
            std::string icurline)
        {
            std::vector<std::string> sface, svert;
            Vertex vVert;
            algorithm::split(algorithm::tail(icurline), sface, " ");

            bool noNormal = false;

            // For every given vertex do this
            for (int i = 0; i < int(sface.size()); i++)
            {
                // See What type the vertex is.
                int vtype;

                algorithm::split(sface[i], svert, "/");

                // Check for just position - v1
                if (svert.size() == 1)
                {
                    // Only position
                    vtype = 1;
                }

                // Check for position & texture - v1/vt1
                if (svert.size() == 2)
                {
                    // Position & Texture
                    vtype = 2;
                }

                // Check for Position, Texture and Normal - v1/vt1/vn1
                // or if Position and Normal - v1//vn1
                if (svert.size() == 3)
                {
                    if (svert[1] != "")
                    {
                        // Position, Texture, and Normal
                        vtype = 4;
                    }
                    else
                    {
                        // Position & Normal
                        vtype = 3;
                    }
                }

                // Calculate and store the vertex
                switch (vtype)
                {
                case 1: // P
                {
                    vVert.Position = algorithm::getElement(iPositions, svert[0]);
                    vVert.TextureCoordinate = Vector2(0, 0);
                    noNormal = true;
                    oVerts.push_back(vVert);
                    break;
                }
                case 2: // P/T
                {
                    vVert.Position = algorithm::getElement(iPositions, svert[0]);
                    vVert.TextureCoordinate = algorithm::getElement(iTCoords, svert[1]);
                    noNormal = true;
                    oVerts.push_back(vVert);
                    break;
                }
                case 3: // P//N
                {
                    vVert.Position = algorithm::getElement(iPositions, svert[0]);
                    vVert.TextureCoordinate = Vector2(0, 0);
                    vVert.Normal = algorithm::getElement(iNormals, svert[2]);
                    oVerts.push_back(vVert);
                    break;
                }
                case 4: // P/T/N
                {
                    vVert.Position = algorithm::getElement(iPositions, svert[0]);
                    vVert.TextureCoordinate = algorithm::getElement(iTCoords, svert[1]);
                    vVert.Normal = algorithm::getElement(iNormals, svert[2]);
                    oVerts.push_back(vVert);
                    break;
                }
                default:
                {
                    break;
                }
                }
            }

            // take care of missing normals
            // these may not be truly acurate but it is the
            // best they get for not compiling a mesh with normals
            if (noNormal)
            {
                Vector3 A = oVerts[0].Position - oVerts[1].Position;
                Vector3 B = oVerts[2].Position - oVerts[1].Position;

                Vector3 normal = math::CrossV3(A, B);

                for (int i = 0; i < int(oVerts.size()); i++)
                {
                    oVerts[i].Normal = normal;
                }
            }
        }
}
