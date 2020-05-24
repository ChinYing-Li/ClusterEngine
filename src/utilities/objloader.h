// OBJ_Loader.h - A Single Header OBJ Model Loader

#pragma once

// Iostream - STD I/O Library
#include <iostream>

// Vector - STD Vector/Array Library
#include <vector>

// String - STD String Library
#include <string>

// fStream - STD File I/O Library
#include <fstream>

// Math.h - STD math Library
#include <math.h>
#include "../components/appearance/material.h"
#include "gl_headers.h"
// Namespace: OBJL
//
// Description: The namespace that holds eveyrthing that
//    is needed and used for the OBJ Model Loader

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TextureCoordinate;
};


    // Structure: Mesh
    //
    // Description: A Simple Mesh Object that holds
    //    a name, a vertex list, and an index list
    struct Mesh
    {
        // Default Constructor
        Mesh()
        {

        }
        // Variable Set Constructor
        Mesh(std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _Indices)
        {
            Vertices = _Vertices;
            Indices = _Indices;
        }
        // Mesh Name
        std::string MeshName;
        // Vertex List
        std::vector<Vertex> Vertices;
        // Index List
        std::vector<unsigned int> Indices;

        // Material
        Material MeshMaterial;
    };

    // Namespace: Math
    //
    // Description: The namespace that holds all of the math
    //    functions need for OBJL
    namespace math
    {
        // Vector3 Cross Product
        Vector3 CrossV3(const Vector3 a, const Vector3 b)
        {
            return Vector3(a.Y * b.Z - a.Z * b.Y,
                a.Z * b.X - a.X * b.Z,
                a.X * b.Y - a.Y * b.X);
        }

        // Vector3 Magnitude Calculation
        float MagnitudeV3(const Vector3 in)
        {
            return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
        }

        // Vector3 DotProduct
        float DotV3(const Vector3 a, const Vector3 b)
        {
            return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
        }

        // Angle between 2 Vector3 Objects
        float AngleBetweenV3(const Vector3 a, const Vector3 b)
        {
            float angle = DotV3(a, b);
            angle /= (MagnitudeV3(a) * MagnitudeV3(b));
            return angle = acosf(angle);
        }

        // Projection Calculation of a onto b
        Vector3 ProjV3(const Vector3 a, const Vector3 b)
        {
            Vector3 bn = b / MagnitudeV3(b);
            return bn * DotV3(a, bn);
        }
    }

    // Namespace: Algorithm
    //
    // Description: The namespace that holds all of the
    // Algorithms needed for OBJL
    namespace algorithm
    {
        // Vector3 Multiplication Opertor Overload
        Vector3 operator*(const float& left, const Vector3& right)
        {
            return Vector3(right.X * left, right.Y * left, right.Z * left);
        }

        // A test to see if P1 is on the same side as P2 of a line segment ab
        bool SameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b)
        {
            Vector3 cp1 = math::CrossV3(b - a, p1 - a);
            Vector3 cp2 = math::CrossV3(b - a, p2 - a);

            if (math::DotV3(cp1, cp2) >= 0)
                return true;
            else
                return false;
        }

        // Generate a cross produect normal for a triangle
        Vector3 GenTriNormal(Vector3 t1, Vector3 t2, Vector3 t3)
        {
            Vector3 u = t2 - t1;
            Vector3 v = t3 - t1;

            Vector3 normal = math::CrossV3(u,v);

            return normal;
        }

        // Check to see if a Vector3 Point is within a 3 Vector3 Triangle
        bool inTriangle(Vector3 point, Vector3 tri1, Vector3 tri2, Vector3 tri3)
        {
            // Test to see if it is within an infinite prism that the triangle outlines.
            bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
                && SameSide(point, tri3, tri1, tri2);

            // If it isn't it will never be on the triangle
            if (!within_tri_prisim)
                return false;

            // Calulate Triangle's Normal
            Vector3 n = GenTriNormal(tri1, tri2, tri3);

            // Project the point onto this normal
            Vector3 proj = math::ProjV3(point, n);

            // If the distance from the triangle to the point is 0
            //    it lies on the triangle
            if (math::MagnitudeV3(proj) == 0)
                return true;
            else
                return false;
        }

        // Split a String into a string array at a given token
        inline void split(const std::string &in,
            std::vector<std::string> &out,
            std::string token)
        {
            out.clear();

            std::string temp;

            for (int i = 0; i < int(in.size()); i++)
            {
                std::string test = in.substr(i, token.size());

                if (test == token)
                {
                    if (!temp.empty())
                    {
                        out.push_back(temp);
                        temp.clear();
                        i += (int)token.size() - 1;
                    }
                    else
                    {
                        out.push_back("");
                    }
                }
                else if (i + token.size() >= in.size())
                {
                    temp += in.substr(i, token.size());
                    out.push_back(temp);
                    break;
                }
                else
                {
                    temp += in[i];
                }
            }
        }

        // Get tail of string after first token and possibly following spaces
        inline std::string tail(const std::string &in)
        {
            size_t token_start = in.find_first_not_of(" \t");
            size_t space_start = in.find_first_of(" \t", token_start);
            size_t tail_start = in.find_first_not_of(" \t", space_start);
            size_t tail_end = in.find_last_not_of(" \t");
            if (tail_start != std::string::npos && tail_end != std::string::npos)
            {
                return in.substr(tail_start, tail_end - tail_start + 1);
            }
            else if (tail_start != std::string::npos)
            {
                return in.substr(tail_start);
            }
            return "";
        }

        // Get first token of string
        inline std::string firstToken(const std::string &in)
        {
            if (!in.empty())
            {
                size_t token_start = in.find_first_not_of(" \t");
                size_t token_end = in.find_first_of(" \t", token_start);
                if (token_start != std::string::npos && token_end != std::string::npos)
                {
                    return in.substr(token_start, token_end - token_start);
                }
                else if (token_start != std::string::npos)
                {
                    return in.substr(token_start);
                }
            }
            return "";
        }

        // Get element at given index position
        template <class T>
        inline const T & getElement(const std::vector<T> &elements, std::string &index)
        {
            int idx = std::stoi(index);
            if (idx < 0)
                idx = int(elements.size()) + idx;
            else
                idx--;
            return elements[idx];
        }
    }

    // Class: Loader
    //
    // Description: The OBJ Model Loader
    class Loader
    {
    public:
        // Default Constructor
        Loader() = default;
        ~Loader();
        // Load a file into the loader
        //
        // If file is loaded return true
        //
        // If the file is unable to be found
        // or unable to be loaded return false
        bool LoadFile(std::string Path);

        // Triangulate a list of vertices into a face by printing
        //    inducies corresponding with triangles within it
        void VertexTriangluation(std::vector<unsigned int>& oIndices,
            const std::vector<Vertex>& iVerts)
        {
            // If there are 2 or less verts,
            // no triangle can be created,
            // so exit
            if (iVerts.size() < 3)
            {
                return;
            }
            // If it is a triangle no need to calculate it
            if (iVerts.size() == 3)
            {
                oIndices.push_back(0);
                oIndices.push_back(1);
                oIndices.push_back(2);
                return;
            }

            // Create a list of vertices
            std::vector<Vertex> tVerts = iVerts;

            while (true)
            {
                // For every vertex
                for (int i = 0; i < int(tVerts.size()); i++)
                {
                    // pPrev = the previous vertex in the list
                    Vertex pPrev;
                    if (i == 0)
                    {
                        pPrev = tVerts[tVerts.size() - 1];
                    }
                    else
                    {
                        pPrev = tVerts[i - 1];
                    }

                    // pCur = the current vertex;
                    Vertex pCur = tVerts[i];

                    // pNext = the next vertex in the list
                    Vertex pNext;
                    if (i == tVerts.size() - 1)
                    {
                        pNext = tVerts[0];
                    }
                    else
                    {
                        pNext = tVerts[i + 1];
                    }

                    // Check to see if there are only 3 verts left
                    // if so this is the last triangle
                    if (tVerts.size() == 3)
                    {
                        // Create a triangle from pCur, pPrev, pNext
                        for (int j = 0; j < int(tVerts.size()); j++)
                        {
                            if (iVerts[j].Position == pCur.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pPrev.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pNext.Position)
                                oIndices.push_back(j);
                        }

                        tVerts.clear();
                        break;
                    }
                    if (tVerts.size() == 4)
                    {
                        // Create a triangle from pCur, pPrev, pNext
                        for (int j = 0; j < int(iVerts.size()); j++)
                        {
                            if (iVerts[j].Position == pCur.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pPrev.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pNext.Position)
                                oIndices.push_back(j);
                        }

                        Vector3 tempVec;
                        for (int j = 0; j < int(tVerts.size()); j++)
                        {
                            if (tVerts[j].Position != pCur.Position
                                && tVerts[j].Position != pPrev.Position
                                && tVerts[j].Position != pNext.Position)
                            {
                                tempVec = tVerts[j].Position;
                                break;
                            }
                        }

                        // Create a triangle from pCur, pPrev, pNext
                        for (int j = 0; j < int(iVerts.size()); j++)
                        {
                            if (iVerts[j].Position == pPrev.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == pNext.Position)
                                oIndices.push_back(j);
                            if (iVerts[j].Position == tempVec)
                                oIndices.push_back(j);
                        }

                        tVerts.clear();
                        break;
                    }

                    // If Vertex is not an interior vertex
                    float angle = math::AngleBetweenV3(pPrev.Position - pCur.Position, pNext.Position - pCur.Position) * (180 / 3.14159265359);
                    if (angle <= 0 && angle >= 180)
                        continue;

                    // If any vertices are within this triangle
                    bool inTri = false;
                    for (int j = 0; j < int(iVerts.size()); j++)
                    {
                        if (algorithm::inTriangle(iVerts[j].Position, pPrev.Position, pCur.Position, pNext.Position)
                            && iVerts[j].Position != pPrev.Position
                            && iVerts[j].Position != pCur.Position
                            && iVerts[j].Position != pNext.Position)
                        {
                            inTri = true;
                            break;
                        }
                    }
                    if (inTri)
                        continue;

                    // Create a triangle from pCur, pPrev, pNext
                    for (int j = 0; j < int(iVerts.size()); j++)
                    {
                        if (iVerts[j].Position == pCur.Position)
                            oIndices.push_back(j);
                        if (iVerts[j].Position == pPrev.Position)
                            oIndices.push_back(j);
                        if (iVerts[j].Position == pNext.Position)
                            oIndices.push_back(j);
                    }

                    // Delete pCur from the list
                    for (int j = 0; j < int(tVerts.size()); j++)
                    {
                        if (tVerts[j].Position == pCur.Position)
                        {
                            tVerts.erase(tVerts.begin() + j);
                            break;
                        }
                    }

                    // reset i to the start
                    // -1 since loop will add 1 to it
                    i = -1;
                }

                // if no triangles were created
                if (oIndices.size() == 0)
                    break;

                // if no more vertices
                if (tVerts.size() == 0)
                    break;
            }
        }

        // Load Materials from .mtl file
        bool LoadMaterials(std::string path)
        {
            // If the file is not a material file return false
            if (path.substr(path.size() - 4, path.size()) != ".mtl")
                return false;

            std::ifstream file(path);

            // If the file is not found return false
            if (!file.is_open())
                return false;

            Material tempMaterial;

            bool listening = false;

            // Go through each line looking for material variables
            std::string curline;
            while (std::getline(file, curline))
            {
                // new material and material name
                if (algorithm::firstToken(curline) == "newmtl")
                {
                    if (!listening)
                    {
                        listening = true;

                        if (curline.size() > 7)
                        {
                            tempMaterial.name = algorithm::tail(curline);
                        }
                        else
                        {
                            tempMaterial.name = "none";
                        }
                    }
                    else
                    {
                        // Generate the material

                        // Push Back loaded Material
                        LoadedMaterials.push_back(tempMaterial);

                        // Clear Loaded Material
                        tempMaterial = Material();

                        if (curline.size() > 7)
                        {
                            tempMaterial.name = algorithm::tail(curline);
                        }
                        else
                        {
                            tempMaterial.name = "none";
                        }
                    }
                }
                // Ambient Color
                if (algorithm::firstToken(curline) == "Ka")
                {
                    std::vector<std::string> temp;
                    algorithm::split(algorithm::tail(curline), temp, " ");

                    if (temp.size() != 3)
                        continue;

                    tempMaterial.Ka.X = std::stof(temp[0]);
                    tempMaterial.Ka.Y = std::stof(temp[1]);
                    tempMaterial.Ka.Z = std::stof(temp[2]);
                }
                // Diffuse Color
                if (algorithm::firstToken(curline) == "Kd")
                {
                    std::vector<std::string> temp;
                    algorithm::split(algorithm::tail(curline), temp, " ");

                    if (temp.size() != 3)
                        continue;

                    tempMaterial.Kd.X = std::stof(temp[0]);
                    tempMaterial.Kd.Y = std::stof(temp[1]);
                    tempMaterial.Kd.Z = std::stof(temp[2]);
                }
                // Specular Color
                if (algorithm::firstToken(curline) == "Ks")
                {
                    std::vector<std::string> temp;
                    algorithm::split(algorithm::tail(curline), temp, " ");

                    if (temp.size() != 3)
                        continue;

                    tempMaterial.Ks.X = std::stof(temp[0]);
                    tempMaterial.Ks.Y = std::stof(temp[1]);
                    tempMaterial.Ks.Z = std::stof(temp[2]);
                }
                // Specular Exponent
                if (algorithm::firstToken(curline) == "Ns")
                {
                    tempMaterial.Ns = std::stof(algorithm::tail(curline));
                }
                // Optical Density
                if (algorithm::firstToken(curline) == "Ni")
                {
                    tempMaterial.Ni = std::stof(algorithm::tail(curline));
                }
                // Dissolve
                if (algorithm::firstToken(curline) == "d")
                {
                    tempMaterial.d = std::stof(algorithm::tail(curline));
                }
                // Illumination
                if (algorithm::firstToken(curline) == "illum")
                {
                    tempMaterial.illum = std::stoi(algorithm::tail(curline));
                }
                // Ambient Texture Map
                if (algorithm::firstToken(curline) == "map_Ka")
                {
                    tempMaterial.map_Ka = algorithm::tail(curline);
                }
                // Diffuse Texture Map
                if (algorithm::firstToken(curline) == "map_Kd")
                {
                    tempMaterial.map_Kd = algorithm::tail(curline);
                }
                // Specular Texture Map
                if (algorithm::firstToken(curline) == "map_Ks")
                {
                    tempMaterial.map_Ks = algorithm::tail(curline);
                }
                // Specular Hightlight Map
                if (algorithm::firstToken(curline) == "map_Ns")
                {
                    tempMaterial.map_Ns = algorithm::tail(curline);
                }
                // Alpha Texture Map
                if (algorithm::firstToken(curline) == "map_d")
                {
                    tempMaterial.map_d = algorithm::tail(curline);
                }
                // Bump Map
                if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump" || algorithm::firstToken(curline) == "bump")
                {
                    tempMaterial.map_bump = algorithm::tail(curline);
                }
            }

            // Deal with last material

            // Push Back loaded Material
            LoadedMaterials.push_back(tempMaterial);

            // Test to see if anything was loaded
            // If not return false
            if (LoadedMaterials.empty())
                return false;
            // If so return true
            else
                return true;
        }
    };
}
