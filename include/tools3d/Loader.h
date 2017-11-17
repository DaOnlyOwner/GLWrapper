#pragma once
#include <vector>
#include "Common.h"
#include <memory>


namespace doo
{
	namespace loader
	{
		MAKE_EXCEPTION(import_error);

		struct Vec2
		{
			f32 x, y;
		};

		struct Vec3
		{
			f32 x, y, z;
		};

		struct Vec4
		{
			f32 x, y, z, v;
		};

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

		Model* LoadModel(const char* filename);
	}

}