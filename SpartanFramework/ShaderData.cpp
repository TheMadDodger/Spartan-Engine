#include "stdafx.h"
#include "ShaderData.h"

namespace Spartan
{
	ShaderData::ShaderData() : Content(), m_ShaderProgramID(0) {}

	ShaderData::~ShaderData()
	{
		for (size_t i = 0; i < m_ShaderIDs.size(); i++)
		{
			// Detach shader
			glDetachShader(m_ShaderProgramID, m_ShaderIDs[i]);
			Utilities::Debug::LogGLError(glGetError());

			// Delete shader
			glDeleteShader(m_ShaderIDs[i]);
			Utilities::Debug::LogGLError(glGetError());
		}

		// Delete program
		glDeleteProgram(m_ShaderProgramID);
		Utilities::Debug::LogGLError(glGetError());
	}

	const GLuint& ShaderData::GetProgramID() { return m_ShaderProgramID; }
}