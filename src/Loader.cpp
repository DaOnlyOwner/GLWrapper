#include "tools3d/Loader.h"
#include "tools3d/Common.h"
#include "tools3d/Vector.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"

#include "glm/glm.hpp"

namespace doo
{
	namespace loader
	{
 
		void createVertices(std::vector<gl::Vertex>& p_vertices, aiMesh* p_assMesh, const aiMatrix4x4& p_localTransform)
		{
			for (u32 i = 0; i < p_assMesh->mNumVertices; i++)
			{
				gl::Vertex v;

				aiVector3D assPos = p_localTransform * p_assMesh->mVertices[i];

				glm::vec3 pos{ assPos.x, assPos.y, assPos.z };
				v.Position = pos;

				aiMatrix4x4 normalMatrix = p_localTransform;

				aiVector3D assNormal = normalMatrix.Inverse().Transpose() * p_assMesh->mNormals[i];
				glm::vec3 normal{ assNormal.x, assNormal.y, assNormal.z };
				v.Normal = normal;

				p_vertices.push_back(v);

			}
		}

		void createIndices(std::vector<u32>& p_indices, aiMesh* p_assMesh)
		{
			for (u32 i = 0; i < p_assMesh->mNumFaces; i++)
			{
				aiFace& face = p_assMesh->mFaces[i];

				for (u32 j = 0; j < face.mNumIndices; j++)
				{
					p_indices.push_back(face.mIndices[j]);
				}
			}
		}

		// TODO: Parameter to also load not static models;
		void createSceneGraph(aiNode* p_node, const aiScene* p_scene, MeshNode* p_model, const aiMatrix4x4& p_parentTransform)
		{
			aiMatrix4x4 localTransform = p_parentTransform * p_node->mTransformation;

			// Meshes on the same layer are batched together
			for (u32 i = 0; i < p_node->mNumMeshes; i++)
			{
				aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
				
				std::vector<gl::Vertex> p_verticesToLoad;
				std::vector<u32> p_indicesToLoad;

				createVertices(p_verticesToLoad, mesh, localTransform);
				createIndices(p_indicesToLoad, mesh);
				const char* meshName = mesh->mName.C_Str();
				p_model->LocalMeshes.push_back({p_verticesToLoad,p_indicesToLoad,meshName,true});

			}

			p_model->Name = p_node->mName.C_Str();

			for (u32 i = 0; i < p_node->mNumChildren; i++)
			{
				MeshNode* toBeAdded = new MeshNode();
				std::unique_ptr<MeshNode> ptr(toBeAdded);
				createSceneGraph(p_node->mChildren[i], p_scene, toBeAdded, localTransform);
				p_model->Children.push_back(std::move(ptr));
			}
		}

		// TODO: Error handling
		MeshNode* LoadAsSceneGraph(const char* p_filename)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(p_filename, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!scene) throw ImportError("Couldn't load or read file: " + std::string(importer.GetErrorString()));
			if (!scene->HasMeshes()) throw ImportError("Specified file contains no meshes.");

			MeshNode* model = new MeshNode;
			createSceneGraph(scene->mRootNode, scene, model, scene->mRootNode->mTransformation);
			return model;
		}


		const aiScene* loadScene(const char* p_filename, Assimp::Importer& p_importer, u32 p_steps = aiProcessPreset_TargetRealtime_MaxQuality)
		{
			const aiScene* scene = p_importer.ReadFile(p_filename, p_steps);
			if (!scene) throw ImportError("Couldn't load or read file: " + std::string(p_importer.GetErrorString()));
			if (!scene->HasMeshes()) throw ImportError("Specified file contains no meshes.");
			return scene;
		}


		void LoadAsMeshlist(const char* p_filename, std::vector<gl::Mesh>& p_meshlist)
		{
			Assimp::Importer importer;
			const aiScene* scene = loadScene(p_filename, importer, aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_PreTransformVertices);
			

			for(u32 i = 0; i<scene->mNumMeshes; i++)
			{
				std::vector<gl::Vertex> vertices;
				std::vector<u32> indices;
				createVertices(vertices, scene->mMeshes[i], aiMatrix4x4
				   (1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1));
			
				createIndices(indices, scene->mMeshes[i]);

				p_meshlist.push_back(gl::Mesh( vertices,indices, scene->mMeshes[i]->mName.C_Str(), true));
			}
			
		}
	}
}

