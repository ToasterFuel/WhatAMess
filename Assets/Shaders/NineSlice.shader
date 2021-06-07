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

float map(float value, float min1, float max1, float min2, float max2)
{
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

float getSliceValue(float testValue, float min, float max)
{
    if(testValue < min || testValue > max)
        return testValue;
    return mix(min, max, testValue + min);
}

void main()
{
    vec2 slicedCoords;
    //slicedCoords.x = getSliceValue(TexCoords.x, borders.x, borders.z);
    //slicedCoords.y = getSliceValue(TexCoords.y, borders.y, borders.w);
    vec2 currentPixels = TexCoords * scales.zw;
    vec4 originalPixels = borders * scales.xyxy;
    if(currentPixel.x < originalPixels.x)
        map(currentPixel.x, 0, originalPixels.x, 0, border.x);
    else if(scales.z - (TexCoords.x * scales.z) > scales.x - (borders.z * scales.x))
        map(scales.z - (TexCoords.x * scales.z), scales.z - (borders.z * scales.z), scales.z, 1);
    else
        map(currentPixel.x, scales.z * borders.x, scales.z * borders.z, borders.x, borders.z);

    slicedCoords.x
    slicedCoords.y = TexCoords.y;
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
