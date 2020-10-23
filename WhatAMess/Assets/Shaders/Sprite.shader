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
}

==========
WebGL
==========
attribute vec4 vertex; // <vec2 position, vec2 texCoords>
uniform mat4 mvp;

varying vec2 TexCoords;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = mvp * vec4(vertex.xy, 0.0, 1.0);
}

++++++++++

#version 100
precision mediump float;
varying vec2 TexCoords;

uniform sampler2D image;
uniform vec4 spriteColor;

void main()
{
    gl_FragColor = texture2D(image, TexCoords) * spriteColor;
}
