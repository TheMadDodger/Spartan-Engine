#pragma once
#include "Content.h"

namespace Spartan
{
	class ShaderData : public Content
	{
	public:
		ShaderData();
		virtual ~ShaderData();

		BASIC_OBJECT(ShaderData, Content);

		const GLuint& GetProgramID();

	private:
		friend class ShaderLoader;
		friend class Material;
		GLuint m_ShaderProgramID;
		std::vector<GLuint> m_ShaderIDs;
	};
}
