#include "tools3d/Loader.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"
#include "tools3d/Common.h"

namespace doo
{
	namespace loader
	{
		Vertex createVertices(Mesh* p_myMesh, aiMesh* p_assMesh, const aiMatrix4x4& p_localTransform)
		{
			for (int i = 0; i < p_assMesh->mNumVertices; i++)
			{
				Vertex v;

				aiVector3D assPos = p_localTransform * p_assMesh->mVertices[i];

				Vec3 pos{ assPos.x, assPos.y, assPos.z };
				v.Position = pos;

				aiMatrix4x4 normalMatrix = p_localTransform;

				aiVector3D assNormal = normalMatrix.Inverse().Transpose() * p_assMesh->mNormals[i];
				Vec3 normal{ assNormal.x, assNormal.y, assNormal.z };
				v.Normal = normal;

				p_myMesh->Vertices.push_back(v);

			}
		}

		void createIndices(Mesh* p_myMesh, aiMesh* p_assMesh)
		{
			for (u32 i = 0; i < p_assMesh->mNumFaces; i++)
			{
				aiFace& face = p_assMesh->mFaces[i];

				for (u32 j = 0; j < face.mNumIndices; j++)
				{
					p_myMesh->Indices.push_back(face.mIndices[j]);
				}

			}
		}

		void createModel(aiNode* p_node, const aiScene* p_scene, Model* p_model, const aiMatrix4x4& p_parentTransform)
		{
			aiMatrix4x4 localTransform = p_parentTransform * p_node->mTransformation;

			// Meshes on the same layer are batched together
			for (u32 i = 0; i < p_node->mNumMeshes; i++)
			{
				aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
				Mesh myMesh;

				createIndices(&myMesh, mesh);
				createVertices(&myMesh, mesh, localTransform);
				myMesh.Name = mesh->mName.C_Str();

				p_model->LocalMeshes.push_back(myMesh);
			}

			p_model->Name = p_node->mName.C_Str();

			for (u32 i = 0; i < p_node->mNumChildren; i++)
			{
				Model* toBeAdded = new Model();
				std::unique_ptr<Model> ptr(toBeAdded);
				createModel(p_node->mChildren[i], p_scene, toBeAdded, localTransform);
				p_model->Children.push_back(std::move(ptr));
			}
		}

		// TODO: Error handling
		Model* LoadModel(const char* p_filename)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(p_filename, aiProcessPreset_TargetRealtime_MaxQuality);

			if (!scene) throw ImportError("Couldn't load or read file: " + std::string(importer.GetErrorString()));
			if (!scene->HasMeshes()) throw ImportError("Specified file contains no meshes.");

			Model* model = new Model;


			createModel(scene->mRootNode, scene, model, scene->mRootNode->mTransformation);
			return model;
		}

	}
}

