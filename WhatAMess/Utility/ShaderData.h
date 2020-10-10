#ifndef __SHADER_DATA__
#define __SHADER_DATA__

#include <string>
#include <sstream>

enum ShaderType
{
    SHADER_VERT,
    SHADER_FRAG,
    SHADER_TYPE_UNKNOWN
};

enum ShaderBuild
{
    SHADER_WEB_GL,
    SHADER_OPEN_GL,
    SHADER_BUILD_UNKNOWN
};

/*
Expected file format:

==========
OpenGL
==========

vertex

++++++++++

fragment

==========
WebGL
==========

vertex

++++++++++

fragment

*/

class ShaderData
{
public:
    ShaderData();
    bool LoadFromFile(const char* path);

    const char* GetVertexShader() const;
    const char* GetFragmentShader() const;

private:
    std::string webVertexShader;
    std::string webFragmentShader;
    std::string openVertexShader;
    std::string openFragmentShader;

    void SaveShader(ShaderBuild shaderBuild, ShaderType shaderType, std::stringstream& ss);

    static const std::string BUILD_DELIMITER;
    static const std::string SHADER_DELIMITER;
    static const std::string WEB_GL_ID;
    static const std::string OPEN_GL_ID;
};

#endif
