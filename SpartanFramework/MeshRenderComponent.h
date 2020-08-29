#pragma once
#include "BaseComponent.h"

namespace Spartan
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
		size_t GetMaterial();

		void Draw(const GameContext& gameContext) override;

	private:
		void Initialize(const GameContext& gameContext) override;
		void Update(const GameContext& gameContext) override;

		COMPONENT(MeshRenderComponent);

	private:
		Mesh* m_pMeshToRender;
		size_t m_MaterialID;
		GLuint gVBO;
		GLuint gIBO;
		GLuint gVertexPos2DLocation;
	};
}