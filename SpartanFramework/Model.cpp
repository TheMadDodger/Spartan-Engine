#include "stdafx.h"
#include "Model.h"

namespace Spartan
{
	Model::Model() : Content() {}

	Model::~Model()
	{
		for (size_t i = 0; i < m_pMeshes.size(); i++)
		{
			delete m_pMeshes[i];
		}
		m_pMeshes.clear();
	}

	void Model::AddMesh(Mesh* pMesh) { m_pMeshes.push_back(pMesh); }
	Mesh* Model::GetMesh(size_t index) { return m_pMeshes[index]; }
}