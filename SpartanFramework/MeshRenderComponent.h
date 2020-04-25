#pragma once
#include "BaseComponent.h"

namespace SpartanEngine
{
	class Mesh;
	class Material;

	class MeshRenderComponent : public BaseComponent
	{
	public:
		MeshRenderComponent();
		virtual ~MeshRenderComponent();

		void SetMesh(Mesh* pMesh);
		void SetMaterial(size_t materialID);

	private:
		void Initialize(const GameContext& gameContext) override;
		void Update(const GameContext& gameContext) override;
		void Draw(const GameContext& gameContext) override;

		COMPONENT_EDITOR(MeshRenderComponent)

	private:
		Mesh* m_pMesh;
		size_t m_MaterialID;
		GLuint gVBO;
		GLuint gIBO;
		GLuint gVertexPos2DLocation;
	};
}