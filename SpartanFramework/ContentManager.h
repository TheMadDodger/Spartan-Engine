#pragma once
#include "ContentLoader.h"
#include "MathHelpers.h"
#include "Debug.h"
#include "SEObject.h"
#include "Manager.h"
#include "VertexHelpers.h"
#include "Content.h"
#include "Gradient.h"

namespace SpartanEngine
{
	class TextureData : public Content
	{
	public:
		TextureData(const std::string& file, const Vector2& origin) : Content(file), m_Origin(origin) {}
		TextureData(const GLuint &textureID, const Vector2& dimensions) : Content(""), m_Origin(), m_TextureID(textureID), m_Dimensions(dimensions) {}

		SDL_Surface* GetImage() { return m_pImage; };
		SDL_Texture* GetTexture() { return m_pTexture; };

		const Vector2& GetDimensions() { return m_Dimensions; }
		const GLuint& GetID() { return m_TextureID; }
		const Vector2& GetOrigin() { return m_Origin; }

		void SetOrigin(const Vector2& origin)
		{
			m_Origin = origin;
		}

		virtual ~TextureData()
		{
			glDeleteTextures(1, &m_TextureID);
			if (m_pImage) SDL_FreeSurface(m_pImage);
			m_pImage = NULL;
		}

		static const Float4 ToTextureCoordinates(TextureData* pTexture, const SDL_Rect& src)
		{
			Float4 result;
			auto dimensions = pTexture->GetDimensions();
			result.x = (float)src.x / dimensions.x;
			result.y = (float)src.y / dimensions.y;

			result.w = (float)src.w / dimensions.x;
			result.h = (float)src.h / dimensions.y;

			return result;
		}

		void BuildTextureFromData(const Vector2& dimensions, float* pData, GLint internalFormat, GLenum dataFormat)
		{
			m_Dimensions = dimensions;

			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			GLenum e = glGetError();
			if (e != GL_NO_ERROR)
			{
				std::cerr << "Texture::CreateFromSurface, error binding textures, Error id = " << e << '\n';
			}

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, (GLsizei)m_Dimensions.x, (GLsizei)m_Dimensions.y, 0, dataFormat, GL_FLOAT, pData);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

	private:
		void BuildTexture()
		{
			GLenum pixelFormat{ GL_RGB };
			switch (m_pImage->format->BytesPerPixel)
			{
			case 3:
				if (m_pImage->format->Rmask == 0x000000ff)
				{
					pixelFormat = GL_RGB;
				}
				else
				{
					pixelFormat = GL_BGR;
				}
				break;
			case 4:
				if (m_pImage->format->Rmask == 0x000000ff)
				{
					pixelFormat = GL_RGBA;
				}
				else
				{
					pixelFormat = GL_BGRA;
				}
				break;
			default:
				std::cerr << "Texture::CreateFromSurface, unknow pixel format, BytesPerPixel: " << m_pImage->format->BytesPerPixel << "\nUse 32 bit or 24 bit images.\n";
				return;
			}

			m_Dimensions = Vector2((float)m_pImage->w, (float)m_pImage->h);

			glGenTextures(1, &m_TextureID);
			glBindTexture(GL_TEXTURE_2D, m_TextureID);

			GLenum e = glGetError();
			if (e != GL_NO_ERROR)
			{
				std::cerr << "Texture::CreateFromSurface, error binding textures, Error id = " << e << '\n';
			}

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pImage->w, m_pImage->h, 0, pixelFormat, GL_UNSIGNED_BYTE, m_pImage->pixels);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

	private:
		friend class TextureLoader;
		friend class Renderer;
		SDL_Surface* m_pImage;
		SDL_Texture* m_pTexture;
		GLuint m_TextureID;

		Vector2 m_Dimensions;
		Vector2 m_Origin;
	};

	class AudioData : public Content
	{
	public:
		AudioData(const std::string& file) : Content(file) {}
		virtual ~AudioData()
		{
			if (m_pChunck)
				Mix_FreeChunk(m_pChunck);

			if (m_pMusic)
				Mix_FreeMusic(m_pMusic);

			m_pChunck = nullptr;
			m_pMusic = nullptr;
		}

		Mix_Music* GetMusic() const
		{
			if (!m_IsMusic)
			{
				std::cerr << "AudioData::GetMusic > Object does not contain music!" << std::endl;
				return nullptr;
			}
			return m_pMusic;
		}

		Mix_Chunk* GetWAVChunck() const
		{
			if (m_IsMusic)
			{
				std::cerr << "AudioData::GetWAVChunck > Object contains music!" << std::endl;
				return nullptr;
			}
			return m_pChunck;
		}

		bool IsMusic() const
		{
			return m_IsMusic;
		}

		void SetVolume(int volume);
		int GetVolume() const;

	private:
		friend class AudioFileLoader;
		bool m_IsMusic = false;
		Mix_Music* m_pMusic = nullptr;
		Mix_Chunk* m_pChunck = nullptr;
		int m_Volume = MIX_MAX_VOLUME;
	};

	struct FrameData
	{
		SDL_Rect FrameRect;
	};

	struct AnimationClip
	{
		std::string Name;
		int NumberOfFrames;
		int FramesPerSecond;
		int ClipID;
		std::vector<FrameData> Frames;
	};

	class SpriteSheetData : public Content
	{
	public:
		SpriteSheetData(const std::string& file) : Content(file) {}
		virtual ~SpriteSheetData() {}

	private:
		friend class SpriteSheetLoader;
		friend class SpriteSheetComponent;
		std::vector<AnimationClip> m_AnimationClips;
		int m_TotalClips;
		std::string m_ImageFile;

		TextureData* m_pImageData;
	};

	class FontData : public Content
	{
	public:
		FontData(const std::string& file) : Content(file) {}
		virtual ~FontData()
		{
			TTF_CloseFont(m_pTTFFont);
			m_pTTFFont = nullptr;
		}

		TTF_Font* GetFontData() { return m_pTTFFont; }

		int GetSize()
		{
			return TTF_FontHeight(m_pTTFFont);
		}

	private:
		friend class FontLoader;
		TTF_Font* m_pTTFFont = nullptr;
	};

	class ShaderData : public Content
	{
	public:
		ShaderData(const std::string& file) : Content(file), m_ShaderProgramID(0) {}
		virtual ~ShaderData()
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

		const GLuint& GetProgramID()
		{
			return m_ShaderProgramID;
		}

	private:
		friend class ShaderLoader;
		friend class Material;
		GLuint m_ShaderProgramID;
		std::vector<GLuint> m_ShaderIDs;
	};

	//class ShaderData : public Content
	//{
	//public:
	//	ShaderData(const std::string &file) : Content(file) {}
	//	virtual ~ShaderData()
	//	{
	//		// Detach shaders
	//		glDetachShader(m_ShaderProgramID, m_VertexShaderID);
	//		Utilities::Debug::LogGLError(glGetError());
	//		glDetachShader(m_ShaderProgramID, m_FragmentShaderID);
	//		Utilities::Debug::LogGLError(glGetError());
	//
	//		// Delete shaders
	//		glDeleteShader(m_VertexShaderID);
	//		Utilities::Debug::LogGLError(glGetError());
	//		glDeleteShader(m_FragmentShaderID);
	//		Utilities::Debug::LogGLError(glGetError());
	//
	//		// Delete program
	//		glDeleteProgram(m_ShaderProgramID);
	//		Utilities::Debug::LogGLError(glGetError());
	//	}
	//
	//	const GLuint &GetProgramID()
	//	{
	//		return m_ShaderProgramID;
	//	}
	//
	//private:
	//	friend class ShaderLoader;
	//	friend class Material;
	//	GLuint m_ShaderProgramID;
	//	GLuint m_VertexShaderID;
	//	GLuint m_FragmentShaderID;
	//};

	class Mesh;

	class Model : public Content
	{
	public:
		Model(const std::string& path) : Content(path) {}
		~Model()
		{
			for (size_t i = 0; i < m_pMeshes.size(); i++)
			{
				delete m_pMeshes[i];
			}
			m_pMeshes.clear();
		}

		void AddMesh(Mesh* pMesh) { m_pMeshes.push_back(pMesh); }
		Mesh* GetMesh(size_t index) { return m_pMeshes[index]; }

	private:
		std::vector<Mesh*> m_pMeshes;
	};

#pragma warning(disable:4996)
	class ContentManager : Manager
	{
	public: // Singleton calls
		static ContentManager* GetInstance();
		static void Destroy();

	public: // System methods
		void Initialize();

		template <typename T>
		T* Load(std::string file)
		{
			for (Content* pContent : m_pContent)
			{
				if (pContent->m_FileName == file)
					return static_cast<T*>(pContent);
			}

			for (BaseLoader* pLoader : m_pLoaders)
			{
				const type_info& ti = typeid(T);
				if (pLoader->GetType() == ti)
				{
					T* pContent = static_cast<ContentLoader<T>*>(pLoader)->GetContent(file);
					if (pContent != nullptr)
					{
						m_pContent.push_back(pContent);
						return pContent;
					}
				}
			}

			return nullptr;
		}

		static bool FileExists(const std::string& file)
		{
			if (FILE* f = fopen(file.c_str(), "r")) {
				fclose(f);
				return true;
			}
			else {
				return false;
			}
		}

	private:
		void AddLoader(BaseLoader* pLoader);

	private: // Content data
		std::vector<Content*> m_pContent;
		std::vector<BaseLoader*> m_pLoaders;

	private: // Singleton
		ContentManager();
		~ContentManager();
		static ContentManager* m_pContentManager;
	};
}