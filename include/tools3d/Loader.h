#pragma once
#include "Common.h"
#include "Mesh.h"
#include <memory>
#include <string>
#include <vector>


namespace doo
{
	namespace loader
	{
		MAKE_EXCEPTION(ImportError);

		struct MeshNode
		{
			std::vector<gl::Mesh> LocalMeshes;
			std::vector<std::unique_ptr<MeshNode>> Children;
			std::string Name;
		};

		gl::Mesh* LoadAsMeshlist(const char* filename);
		MeshNode* LoadAsSceneGraph(const char* filename);
		
	}

}
