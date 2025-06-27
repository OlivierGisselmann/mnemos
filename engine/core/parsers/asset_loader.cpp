#include <core/parsers/asset_loader.hpp>

namespace Mnemos
{
    std::vector<std::string> Split(const std::string& s, char delim) {
        std::vector<std::string> elems;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    Renderable* AssetLoader::LoadOBJ(const std::string& path)
    {
        const std::string fileContent = ResourceManager::Get().ReadTextFile(path);

        std::vector<vec3<f32>> positions;
        std::vector<vec3<f32>> normals;
        std::vector<vec2<f32>> uvs;

        std::vector<Vertex> uniqueVertices;
        std::vector<u32> indices;
        std::unordered_map<std::string, uint32_t> vertexCache;

        std::stringstream stream {fileContent};
        std::string line;

        // Parse file
        while(std::getline(stream, line))
        {
            std::istringstream lineStream(line);
            std::string type;
            lineStream >> type;

            if(type == "v")
            {
                vec3<f32> pos;
                lineStream >> pos.x >> pos.y >> pos.z;
                positions.push_back(pos);
            }
            else if(type == "vt")
            {
                vec2<f32> uv;
                lineStream >> uv.x >> uv.y;
                uvs.push_back(uv);
            }
            else if(type == "vn")
            {
                vec3<f32> nml;
                lineStream >> nml.x >> nml.y >> nml.z;
                normals.push_back(nml);
            }
            else if(type == "f")
            {
                for(int i = 0; i < 3; ++i)
                {
                    std::string vert;
                    lineStream >> vert;

                    // Check for vertex existence in cache
                    if(vertexCache.count(vert))
                    {
                        indices.push_back(vertexCache[vert]);
                        continue;
                    }

                    // Parse faces and check for normals and UVs existence
                    auto tokens = Split(vert, '/');
                    int posIndex = std::stoi(tokens[0]) - 1;
                    int normIndex = -1;
                    int uvIndex = -1;

                    // If no uvs specified, normals are at array[1] position
                    if(uvs.empty())
                        normIndex = tokens.size() > 1 && !tokens[1].empty() && !normals.empty() ? std::stoi(tokens[1]) - 1 : -1;
                    else
                    {
                        uvIndex  = tokens.size() > 1 && !tokens[1].empty() && !uvs.empty() ? std::stoi(tokens[1]) - 1 : -1;
                        normIndex = tokens.size() > 2 && !tokens[2].empty() && !normals.empty() ? std::stoi(tokens[2]) - 1 : -1;
                    }


                    Vertex v;
                    v.position = positions[posIndex];
                    if(normIndex != -1)
                        v.normal = normals[normIndex];
                    if(uvIndex != -1)
                        v.texCoords = uvs[uvIndex];

                    uniqueVertices.push_back(v);
                    u32 index = (u32)(uniqueVertices.size() - 1);
                    vertexCache[vert] = index;
                    indices.push_back(index);
                }
            }
        }

        Mesh* mesh = new Mesh(uniqueVertices.data(), sizeof(Vertex), uniqueVertices.size(), indices.data(), indices.size());
        Material* material = MaterialFactory::CreateDefault();

        return new Renderable {mesh, material, mat4<f32>(1.0f)};
    }
}
