#pragma once
#include "ContentLoader.h"
#include "MathHelpers.h"
#include "Debug.h"

using namespace Math;

class Content // Base Class for content
{
public:
	Content(const std::string &file) : m_FileName(file) {}
	virtual ~Content() {}
	const std::string &GetFile() { return m_FileName; };

	template <class T>
	T *As() { return static_cast<T*>(this); };

protected:
	friend class ContentManager;
	const std::string m_FileName;
};

class TextureData : public Content
{
public:
	TextureData(const std::string &file, const Vector2 &origin) : Content(file), m_Origin(origin) {}

	SDL_Surface *GetImage() { return m_pImage; };
	SDL_Texture *GetTexture() { return m_pTexture; };

	const Vector2 &GetDimensions() { return m_Dimensions; }
	const GLuint &GetID() { return m_TextureID; }
	const Vector2 &GetOrigin() { return m_Origin; }

	void SetOrigin(const Vector2 &origin)
	{
		m_Origin = origin;
	}

	virtual ~TextureData()
	{
		glDeleteTextures(1, &m_TextureID);
		SDL_FreeSurface(m_pImage);
		m_pImage = NULL;
	}

	static const Float4 ToTextureCoordinates(TextureData *pTexture, const SDL_Rect &src)
	{
		Float4 result;
		auto dimensions = pTexture->GetDimensions();
		result.x = (float)src.x / dimensions.x;
		result.y = (float)src.y / dimensions.y;

		result.w = (float)src.w / dimensions.x;
		result.h = (float)src.h / dimensions.y;

		return result;
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
		glBindTexture(GL_TEXTURE_2D , m_TextureID);

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
	SDL_Surface *m_pImage;
	SDL_Texture *m_pTexture;
	GLuint m_TextureID;

	Vector2 m_Dimensions;
	Vector2 m_Origin;
};

class AudioData : public Content
{
public:
	AudioData(const std::string &file) : Content(file) {}
	virtual ~AudioData()
	{
		if (m_pChunck)
			Mix_FreeChunk(m_pChunck);

		if (m_pMusic)
			Mix_FreeMusic(m_pMusic);

		m_pChunck = nullptr;
		m_pMusic = nullptr;
	}

	Mix_Music *GetMusic() const
	{
		if (!m_IsMusic)
		{
			std::cerr << "AudioData::GetMusic > Object does not contain music!" << std::endl;
			return nullptr;
		}
		return m_pMusic;
	}

	Mix_Chunk *GetWAVChunck() const
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
	Mix_Music *m_pMusic = nullptr;
	Mix_Chunk *m_pChunck = nullptr;
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
	SpriteSheetData(const std::string &file) : Content(file) {}
	virtual ~SpriteSheetData() {}

private:
	friend class SpriteSheetLoader;
	friend class SpriteSheetComponent;
	std::vector<AnimationClip> m_AnimationClips;
	int m_TotalClips;
	std::string m_ImageFile;

	TextureData *m_pImageData;
};

class FontData : public Content
{
public:
	FontData(const std::string &file) : Content(file) {}
	virtual ~FontData()
	{
		TTF_CloseFont(m_pTTFFont);
		m_pTTFFont = nullptr;
	}

	TTF_Font *GetFontData() { return m_pTTFFont; }

	int GetSize()
	{
		return TTF_FontHeight(m_pTTFFont);
	}

private:
	friend class FontLoader;
	TTF_Font *m_pTTFFont = nullptr;
};

class Material : public Content
{
public:
	Material(const std::string &file) : Content(file) {}
	virtual ~Material()
	{
		glDeleteProgram(m_ShaderProgramID);
		Utilities::Debug::LogGLError(glGetError());
	}

	void SetFloat(const std::string &name, float value) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1f(ID, value);
		Utilities::Debug::LogGLError(glGetError());
	}
	
	void SetBool(const std::string &name, bool value) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1i(ID, (int)value);
		Utilities::Debug::LogGLError(glGetError());
	}
	
	void SetVec3(const std::string &name, const Vector3 &value) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform3f(ID, value.x, value.y, value.z);
		Utilities::Debug::LogGLError(glGetError());
	}

	void SetVec2(const std::string &name, const Vector3 &value) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform2f(ID, value.x, value.y);
		Utilities::Debug::LogGLError(glGetError());
	}

	void SetColor(const std::string &name, const Color &value) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform4f(ID, value.r, value.g, value.b, value.a);
		Utilities::Debug::LogGLError(glGetError());
	}

	void SetDouble(const std::string &name, double value) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		glUniform1d(ID, value);
		Utilities::Debug::LogGLError(glGetError());
	}

	void SetMatrix(const std::string &name, const Matrix3X3 &m) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());

		float mp[6] = {m.m[0][0], m.m[1][0], m.m[1][0], m.m[0][1], m.m[1][1], m.m[2][1]};
		glUniformMatrix3x2fv(ID, 1, false, mp);
		Utilities::Debug::LogGLError(glGetError());
	}

	void SetMatrix(const std::string &name, const std::vector<Matrix3X3> &matrices) const
	{
		GLint ID = glGetUniformLocation(m_ShaderProgramID, name.c_str());
		Utilities::Debug::LogGLError(glGetError());
		const size_t arraySize = matrices.size() * 6;
		float *mp = new float[arraySize];
		size_t index = 0;
		for (Matrix3X3 m : matrices)
		{
			mp[index] = m.m[0][0];
			mp[index + 1] = m.m[1][0];
			mp[index + 2] = m.m[2][0];
			mp[index + 3] = m.m[0][1];
			mp[index + 4] = m.m[1][1];
			mp[index + 5] = m.m[2][1];
		}

		glUniformMatrix3x2fv(ID, matrices.size(), false, mp);
		Utilities::Debug::LogGLError(glGetError());
		delete[] mp;
	}

	void Use()
	{
		glUseProgram(m_ShaderProgramID);
		Utilities::Debug::LogGLError(glGetError());
	}

	static void Reset()
	{
		glUseProgram(0);
		Utilities::Debug::LogGLError(glGetError());
	}

private:
	friend class ShaderLoader;
	unsigned int m_ShaderProgramID;
};

#pragma warning(disable:4996)
class ContentManager
{
public: // Singleton calls
	static ContentManager *GetInstance();
	static void Destroy();

public: // System methods
	void Initialize();

	template <typename T>
	T *Load(std::string file)
	{
		for (Content *pContent : m_pContent)
		{
			if (pContent->m_FileName == file)
				return static_cast<T*>(pContent);
		}

		for (BaseLoader *pLoader : m_pLoaders)
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

	static bool FileExists(const std::string &file)
	{
		if (FILE *f = fopen(file.c_str(), "r")) {
			fclose(f);
			return true;
		}
		else {
			return false;
		}
	}

private:
	void AddLoader(BaseLoader *pLoader);

private: // Content data
	std::vector<Content*> m_pContent;
	std::vector<BaseLoader*> m_pLoaders;

private: // Singleton
	ContentManager();
	~ContentManager();
	static ContentManager *m_pContentManager;
};
