#pragma once
#include "Common.h"
#include "VBO.h"
#include <vector>
#include "Mesh.h"

namespace doo
{
	namespace gl
	{
		class StaticModel
		{

		public:
			StaticModel(std::vector<Mesh>&& p_localMeshes, std::vector<std::unique_ptr<StaticModel>>&& p_children, const std::string& p_name) : m_localMeshes(std::move(p_localMeshes)),
																																   m_children(std::move(p_children)),
																																   m_name(p_name){}
			//void Draw() const;

		private:
			std::vector<Mesh> m_localMeshes;
			std::vector<std::unique_ptr<StaticModel>> m_children;
			std::string m_name;
		};
	}
}

