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
uniform vec4 spriteColor;

void main()
{
    color = texture(image, TexCoords) * spriteColor;
    //color = vec4(TexCoords.x, TexCoords.y, 0.0f, 1.0f);
}

==========
WebGL
==========
attribute vec3 aPos;
attribute vec2 aTexCoord;
uniform vec3 aColor;
varying vec3 Color;
varying vec2 TexCoord;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    Color = aColor;
    TexCoord = aTexCoord;
}

++++++++++

#version 100
precision mediump float;
varying vec2 TexCoord;
varying vec3 Color;
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
    gl_FragColor = mix(texture2D(texture1, TexCoord), texture2D(texture2, TexCoord), 0.2);// * vec4(Color, 1.0);
}
