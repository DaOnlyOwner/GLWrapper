#include "GLWrapper/Loader.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"
#include "GLWrapper/Common.h"


using namespace doo::loader;

Vertex createVertex(aiMesh* p_mesh, u32 p_index, const aiMatrix4x4& p_localTransform)
{
	Vertex v;
	
	aiVector3D assPos = p_localTransform * p_mesh->mVertices[p_index];

	Vec3 pos{assPos.x, assPos.y, assPos.z};
	v.Position = pos;

	aiMatrix4x4 normalMatrix = p_localTransform;

	aiVector3D assNormal = normalMatrix.Inverse().Transpose() * p_mesh->mNormals[p_index];
	Vec3 normal{ assNormal.x, assNormal.y, assNormal.z };
	v.Normal = normal;

	return v;
}

void createIndices(VertexCollection* p_collection, aiMesh* p_mesh)
{
	for(u32 i = 0; i<p_mesh->mNumFaces; i++)
	{
		aiFace& face = p_mesh->mFaces[i];

		for(u32 j = 0; j<face.mNumIndices; j++)
		{
			p_collection->Indices.push_back(face.mIndices[j]);
		}

	}
}

void createCollection(aiNode* p_node, const aiScene* p_scene, VertexCollection* p_collection, const aiMatrix4x4& p_parentTransform )
{
	aiMatrix4x4 localTransform = p_parentTransform * p_node->mTransformation;

	for (u32 i = 0; i<p_node->mNumMeshes; i++)
	{
		aiMesh* mesh = p_scene->mMeshes[p_node->mMeshes[i]];
		createIndices(p_collection, mesh);
		Vertex v = createVertex(mesh, i, localTransform);
		p_collection->Vertices.push_back(v);
	}

	for(u32 i = 0; i<p_node->mNumChildren; i++)
	{
		VertexCollection* toBeAdded = new VertexCollection();
		std::unique_ptr<VertexCollection> ptr ( toBeAdded );
		createCollection(p_node->mChildren[i], p_scene, toBeAdded, localTransform);
		p_collection->ChildCollections.push_back(std::move(ptr));
	}

}

// TODO: Error handling
VertexCollection* LoadModel(const char* p_filename)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(p_filename, aiProcessPreset_TargetRealtime_MaxQuality);
	
	if (!scene) throw import_error("Couldn't load or read file: " + std::string(importer.GetErrorString()));
	if (!scene->HasMeshes()) throw import_error("Specified file contains no meshes.");

	VertexCollection* collection = new VertexCollection;
	

	createCollection(scene->mRootNode, scene, collection,scene->mRootNode->mTransformation);
	return collection;
}
