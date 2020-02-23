#pragma once
#include "ContentLoader.h"
#include "Mesh.h"

class ModelLoader : public ContentLoader<Model>
{
public:
	ModelLoader();
	~ModelLoader();

	Model* LoadContent(const std::string& file) override;

private:
	void ProcessNode(aiNode* node, const aiScene* scene, Model *pModel);
	Mesh *ProcessMesh(aiMesh* mesh);
};
