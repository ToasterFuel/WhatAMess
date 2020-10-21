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
