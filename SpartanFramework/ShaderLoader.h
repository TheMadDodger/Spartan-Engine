#pragma once
class ShaderLoader : public ContentLoader<Material>
{
public:
	ShaderLoader();
	virtual ~ShaderLoader();

	Material *LoadContent(const std::string& file) override;

private:
	bool GetCompiledShader(unsigned int &shaderID, unsigned int shader_type, const std::string &file);
};

