==========
OpenGL
==========
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 mvp;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = mvp * vec4(vertex.xy, 0.0, 1.0);
}

++++++++++

#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;

void main()
{
    color = texture(image, TexCoords);
    //color = vec4(TexCoords.x, TexCoords.y, 0.0f, 1.0f);
}
