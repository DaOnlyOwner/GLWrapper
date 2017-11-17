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

		struct VertexCollection
		{
			std::vector<std::unique_ptr<VertexCollection>> ChildCollections;
			std::vector<Vertex> Vertices;
			std::vector<u32> Indices;

		};
		
		//TODO: Need to transform the child meshes.
		VertexCollection* LoadModel(const char* filename);
	}

}