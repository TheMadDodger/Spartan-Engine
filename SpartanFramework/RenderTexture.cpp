#include "stdafx.h"
#include "RenderTexture.h"

namespace SpartanEngine
{
	std::vector<RenderTexture*> RenderTexture::m_pRenderTextures = std::vector<RenderTexture*>();
	std::list<RenderTexture*> RenderTexture::m_pRenderTextureUsedList = std::list<RenderTexture*>();
	RenderTexture* RenderTexture::m_pDefaultTexture = nullptr;
	RenderTexture* RenderTexture::m_pCurrentlyInUse = nullptr;

	RenderTexture* RenderTexture::CreateRenderTexture(int width, int height, bool hasDepthBuffer)
	{
		RenderTexture* m_pNewRenderTexture = new RenderTexture(width, height, hasDepthBuffer);
		m_pNewRenderTexture->Initialize();
		m_pRenderTextures.push_back(m_pNewRenderTexture);
		return m_pNewRenderTexture;
	}

	void RenderTexture::DestroyAll()
	{
		for (size_t i = 0; i < m_pRenderTextures.size(); i++)
		{
			if (m_pRenderTextures[i] == m_pDefaultTexture) continue;
			delete m_pRenderTextures[i];
		}
		m_pRenderTextures.clear();
		m_pRenderTextureUsedList.clear();
	}

	void RenderTexture::UseDefaultRenderTexture()
	{
		m_pRenderTextureUsedList.clear();
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);

		m_pDefaultTexture->Use();
	}

	RenderTexture* RenderTexture::GetDefaultRenderTexture()
	{
		return m_pDefaultTexture;
	}

	void RenderTexture::StartFinalRender()
	{
		auto gameSettings = BaseGame::GetGame()->GetGameSettings();
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);
		glViewport(0, 0, gameSettings.Window.Width, gameSettings.Window.Height);
	}

	void RenderTexture::EndFinalRender()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_pDefaultTexture->m_GLFrameBufferID);
		glViewport(0, 0, m_pDefaultTexture->m_Dimensions.x, m_pDefaultTexture->m_Dimensions.y);
	}

	void RenderTexture::Resize(int width, int height)
	{
		DestroyGLData();
		m_Dimensions = IntVector2(width, height);
		Initialize();
	}

	void RenderTexture::Use()
	{
		if (m_pCurrentlyInUse == this)
		{
			Utilities::Debug::LogWarning("RenderTexture already in use!");
			return;
		}

		Bind();

		m_pRenderTextureUsedList.push_back(this);
		m_pCurrentlyInUse = this;
	}

	void RenderTexture::StopUse()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, NULL);

		m_pRenderTextureUsedList.pop_back();

		// Bind the last used rendertexture again if there is one
		if (m_pRenderTextureUsedList.size() > 0)
		{
			RenderTexture* pEnd = m_pRenderTextureUsedList.back();
			pEnd->Bind();
			m_pCurrentlyInUse = pEnd;
			return;
		}
		UseDefaultRenderTexture();
	}

	const GLuint& RenderTexture::GetTextureID()
	{
		return m_GLTextureID;
	}

	const IntVector2& RenderTexture::GetDimensions()
	{
		return m_Dimensions;
	}

	RenderTexture::RenderTexture(int width, int height, bool hasDepthBuffer) : m_Dimensions(width, height), m_GLFrameBufferID(NULL), m_GLTextureID(NULL), m_HasDepthBuffer(hasDepthBuffer), m_GLDepthBufferID(NULL)
	{
	}

	RenderTexture::~RenderTexture()
	{
		DestroyGLData();
	}

	void RenderTexture::Initialize()
	{
		// Create framebuffer
		glGenFramebuffers(1, &m_GLFrameBufferID);
		Utilities::Debug::LogGLError(glGetError());
		glBindFramebuffer(GL_FRAMEBUFFER, m_GLFrameBufferID);
		Utilities::Debug::LogGLError(glGetError());

		// Create texture
		glGenTextures(1, &m_GLTextureID);
		Utilities::Debug::LogGLError(glGetError());
		glBindTexture(GL_TEXTURE_2D, m_GLTextureID);
		Utilities::Debug::LogGLError(glGetError());

		// Initialize texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Dimensions.x, m_Dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		Utilities::Debug::LogGLError(glGetError());

		// Set texture filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		Utilities::Debug::LogGLError(glGetError());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		Utilities::Debug::LogGLError(glGetError());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		Utilities::Debug::LogGLError(glGetError());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		Utilities::Debug::LogGLError(glGetError());

		// Make the depth buffer
		if (m_HasDepthBuffer)
		{
			// The depth buffer
			glGenRenderbuffers(1, &m_GLDepthBufferID);
			Utilities::Debug::LogGLError(glGetError());
			glBindRenderbuffer(GL_RENDERBUFFER, m_GLDepthBufferID);
			Utilities::Debug::LogGLError(glGetError());
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Dimensions.x, m_Dimensions.y);
			Utilities::Debug::LogGLError(glGetError());
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_GLDepthBufferID);
			Utilities::Debug::LogGLError(glGetError());
		}

		// Initialize the framebuffer
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_GLTextureID, 0);
		Utilities::Debug::LogGLError(glGetError());

		GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, DrawBuffers);
		Utilities::Debug::LogGLError(glGetError());

		// Check if something went wrong
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Utilities::Debug::LogError("There was an error when trying to create a frame buffer!");
			return;
		}

		//glBindTexture(GL_TEXTURE_2D, NULL);
		//glBindFramebuffer(GL_FRAMEBUFFER, NULL);
		//Utilities::Debug::LogGLError(glGetError());

		// Bind the last used rendertexture again if there is one
		if (m_pRenderTextureUsedList.size() > 0)
		{
			RenderTexture* pEnd = m_pRenderTextureUsedList.back();
			pEnd->Bind();
		}
	}

	void RenderTexture::DestroyGLData()
	{
		if (m_GLFrameBufferID != NULL) glDeleteFramebuffers(1, &m_GLFrameBufferID);
		if (m_GLDepthBufferID != NULL) glDeleteRenderbuffers(1, &m_GLDepthBufferID);
		if (m_GLTextureID != NULL) glDeleteTextures(1, &m_GLTextureID);

		m_GLFrameBufferID = NULL;
		m_GLDepthBufferID = NULL;
		m_GLTextureID = NULL;
	}

	void RenderTexture::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_GLFrameBufferID);
		glViewport(0, 0, m_Dimensions.x, m_Dimensions.y);
	}
}