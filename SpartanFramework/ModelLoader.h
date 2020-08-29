#pragma once
#include "ContentLoader.h"
#include "Model.h"

namespace Spartan
{
	class ModelLoader : public ContentLoader<Model>
	{
	public:
		ModelLoader();
		~ModelLoader();

		Model* LoadContent(const std::string& file) override;

	private:
		void ProcessNode(aiNode* node, const aiScene* scene, Model* pModel);
		Mesh* ProcessMesh(aiMesh* mesh);
	};
}