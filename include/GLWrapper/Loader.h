#pragma once
#include <vector>
#include "Common.h"
#include <memory>


namespace doo
{
	namespace loader
	{
		MAKE_EXCEPTION(import_error);

		struct Vertex
		{
			Vec3 Position;
			Vec3 Normal;
			//f32 Tangent[3];
			//f32 Bitangent[3];
			//f32 TextCoords[2];
		};


		struct Mesh
		{
			std::vector<Vertex> Vertices;
			std::vector<u32> Indices;
			std::string Name;
		};

		struct Model
		{
			std::vector<Mesh> LocalMeshes;
			std::vector<std::unique_ptr<Model>> Children;
			std::string Name;
		};

		//TODO: Need to transform the child meshes.
		Model* LoadModel(const char* filename);
	}

}