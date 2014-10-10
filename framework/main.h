void render();
void initialize();

namespace Framework
{
	GLuint createShader(GLenum eShaderType, const std::string &strShaderFile);
	GLuint createProgram(const std::vector<GLuint> &shaderList);
}