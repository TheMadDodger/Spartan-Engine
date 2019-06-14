#pragma once
class ShaderLoader : public ContentLoader<ShaderData>
{
public:
	ShaderLoader();
	virtual ~ShaderLoader();

	ShaderData *LoadContent(const std::string& file) override;

private:
	bool GetCompiledShader(unsigned int &shaderID, unsigned int shader_type, const std::string &file);
};

