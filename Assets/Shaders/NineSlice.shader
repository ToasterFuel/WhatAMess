==========
OpenGL
==========
#version 330 core
layout (location = 0) in vec4 vertex; //<vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}

++++++++++

#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec4 spriteColor;
uniform vec4 borders; //(all in percent from edge)<left width, lower height, right width, top height>: <.1, .1, .8, .8>
uniform vec4 scales; //<original scale x, original scale y, current scale x, current scale y>

float map(float value, float originalMin, float originalMax, float newMin, float newMax)
{
    return newMin + (value - originalMin) * (newMax - newMin) / (originalMax - originalMin);
}

/*
 * texCoord: current UV
 * scales: <scale of the original image (as of writing it's the width in pixels), scale of the image now>
 * borders: <% of the image from the left/bottom edge for the slice, % of the image from the top/right edge for the slice)
 */
float getSliceValue(float texCoord, vec2 scales, vec2 borders)
{
    vec2 sliceUVs = (borders * scales.x) / scales.y;
    sliceUVs.y = 1 - sliceUVs.y;

    if(texCoord <= sliceUVs.x)
        return map(texCoord, 0, sliceUVs.x, 0, borders.x);

    if(texCoord >= sliceUVs.y)
        return map(texCoord, sliceUVs.y, 1, 1 - borders.y, 1);

    return map(texCoord, sliceUVs.x, sliceUVs.y, borders.x, 1 - borders.y);
}

void main()
{
    vec2 slicedCoords = vec2(getSliceValue(TexCoords.x, scales.xz, borders.xz), getSliceValue(TexCoords.y, scales.yw, borders.yw));
    color = texture(image, slicedCoords) * spriteColor;
}


==========
WebGL
==========
attribute vec4 vertex; // <vec2 position, vec2 texCoords>
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying vec2 TexCoords;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}

++++++++++

#version 100
precision mediump float;
varying vec2 TexCoords;

uniform sampler2D image;
uniform vec4 spriteColor;

float getSliceValue(float testValue, float min, float max)
{
    if(testValue < min || testValue > max)
        return testValue;
    return mix(min, max, testValue + min);
}

void main()
{
    vec2 slicedCoords;
    slicedCoords.x = getSliceValue(TextCoords.x, borders.x, borders.z);
    slicedCoords.y = getSliceValue(TextCoords.y, borders.y, borders.w);
    gl_FragColor = texture2D(image, TexCoords) * spriteColor;
}
