#include "ShaderData.h"

#include <fstream>
#include <string>
#include <iostream>

const std::string ShaderData::BUILD_DELIMITER = "==========";
const std::string ShaderData::SHADER_DELIMITER = "++++++++++";
const std::string ShaderData::WEB_GL_ID = "WebGL";
const std::string ShaderData::OPEN_GL_ID = "OpenGL";

ShaderData::ShaderData()
{
}

const char* ShaderData::GetVertexShader() const
{
#ifdef OPEN_GL_BUILD
    return openVertexShader.c_str();
#elif WEB_GL_BUILD
    return webVertexShader.c_str();
#endif
}

const char* ShaderData::GetFragmentShader() const
{
#ifdef OPEN_GL_BUILD
    return openFragmentShader.c_str();
#elif WEB_GL_BUILD
    return webFragmentShader.c_str();
#endif
}

void ShaderData::SaveShader(ShaderBuild shaderBuild, ShaderType shaderType, std::stringstream& ss)
{
    if(shaderBuild == SHADER_OPEN_GL)
    {
        if(shaderType == SHADER_VERT)
        {
            openVertexShader = ss.str();
        }
        else if(shaderType == SHADER_FRAG)
        {
            openFragmentShader = ss.str();
        }
    }
    else if(shaderBuild == SHADER_WEB_GL)
    {
        if(shaderType == SHADER_VERT)
        {
            webVertexShader = ss.str();
        }
        else if(shaderType == SHADER_FRAG)
        {
            webFragmentShader = ss.str();
        }
    }
}

bool ShaderData::LoadFromFile(const char* path)
{
    std::string line;
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout << "Could not open file: " << path << "\n";
        return false;
    }

    std::stringstream ss;
    ShaderType shaderType = SHADER_TYPE_UNKNOWN;
    ShaderBuild shaderBuild = SHADER_BUILD_UNKNOWN;

    while(getline(file, line))
    {
        if(line.compare(BUILD_DELIMITER) == 0)
        {
            if(shaderBuild != SHADER_BUILD_UNKNOWN)
                SaveShader(shaderBuild, shaderType, ss);

            if(!getline(file, line))
            {
                std::cout << "Could not load shader: " << path << " file build settings not formatted correctly.\n";
                return false;
            }

            if(line.compare(ShaderData::OPEN_GL_ID) == 0)
            {
                shaderBuild = SHADER_OPEN_GL;
            }
            else if(line.compare(ShaderData::WEB_GL_ID) == 0)
            {
                shaderBuild = SHADER_WEB_GL;
            }
            else
            {
                std::cout << "Unknown shader build type for file: " << path << "\n";
                return false;
            }

            if(!getline(file, line))
            {
                std::cout << "Could not load shader: " << path << " file build settings not formatted correctly.\n";
                return false;
            }
            if(line.compare(ShaderData::BUILD_DELIMITER) != 0)
            {
                std::cout << "Shader formatting incorrect for build delimiter: " << path << "\n";
                return false;
            }
            shaderType = SHADER_VERT;
            ss.str(std::string());
            continue;
        }
        else if(line.compare(ShaderData::SHADER_DELIMITER) == 0)
        {
            if(shaderType == SHADER_FRAG || shaderType == SHADER_TYPE_UNKNOWN)
            {
                std::cout << "Shader formatting incorrect for shader delimiter: " << path << "\n";
                return false;
            }
            SaveShader(shaderBuild, shaderType, ss);
            shaderType = SHADER_FRAG;
            ss.str(std::string());
            continue;
        }
        ss << line << '\n';
    }
    SaveShader(shaderBuild, shaderType, ss);
    file.close();

    return true;
}
