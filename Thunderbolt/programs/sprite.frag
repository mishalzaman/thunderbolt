//#version 330 core
//in vec2 TexCoords;
//out vec4 color;
//
//uniform sampler2D image;
//uniform vec3 spriteColor;
//
//void main()
//{    
//    color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
//} 

#version 330 core
in vec2 v_TexCoods;
in vec4 v_Colour;

out vec4 o_Colour;

uniform sampler2D image;

void main()
{    
//    o_Colour = vec4(v_Colour);
    o_Colour = texture(image, v_TexCoods);
} 