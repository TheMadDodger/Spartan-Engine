#pragma once
#include "Content.h"
#include "Mesh.h"

namespace Spartan
{
	class Model : public Content
	{
	public:
		Model();
		virtual ~Model();

		BASIC_OBJECT(Model, Content);

		void AddMesh(Mesh* pMesh);
		Mesh* GetMesh(size_t index);

	private:
		std::vector<Mesh*> m_pMeshes;
	};
}

