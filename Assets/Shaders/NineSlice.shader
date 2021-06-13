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
    vec2 sliceUVs = (borders.xz * scales.x) / scales.z;
    sliceUVs.y = 1 - sliceUVs.y;
    vec4 otherColor = spriteColor;
    if(TexCoords.x <= sliceUVs.x)
    {
        otherColor = vec4(1, 0, 0, 1);
        slicedCoords.x = map(TexCoords.x, 0, sliceUVs.x, 0, borders.x);
    }
    else if(TexCoords.x >= sliceUVs.y)
    {
        otherColor = vec4(0, 0, 1, 1);
        slicedCoords.x = map(TexCoords.x, sliceUVs.y, 1, 1 - borders.z, 1);
    }
    else
    {
        otherColor = vec4(0, 1, 0, 1);
        slicedCoords.x = map(TexCoords.x, sliceUVs.x, sliceUVs.y, borders.x, 1 - borders.z);
    }
    /*
    if(currentPixels.x < originalPixels.x)
    {
        otherColor = vec4(1, 0, 0, 1);
        slicedCoords.x = map(currentPixels.x, 0, originalPixels.x, 0, borders.x);
    }
    else if(scales.z - (TexCoords.x * scales.z) < scales.x - (borders.z * scales.x))
    {
        otherColor = vec4(0, 1, 0, 1);
        slicedCoords.x = map(scales.z - (TexCoords.x * scales.z), scales.z - (borders.z * scales.z), scales.z, borders.w, 1);
    }
    else
    {
        otherColor = vec4(0, 0, 1, 1);
        slicedCoords.x = map(currentPixels.x, scales.z * borders.x, scales.z * borders.z, borders.x, borders.z);
    }
    */

    slicedCoords.y = TexCoords.y;
    //color = texture(image, slicedCoords) * spriteColor;
    color = texture(image, slicedCoords) * otherColor;
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
