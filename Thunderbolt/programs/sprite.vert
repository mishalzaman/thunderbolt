//#version 330 core
//layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>
//
//out vec2 TexCoords;
//
//uniform mat4 model;
//uniform mat4 projection;
//
//void main()
//{
//    TexCoords = vertex.zw;
//    gl_Position = projection * model * vec4(vertex.xyz, 1.0);
//}

#version 330 core
layout (location = 0) in vec3 a_Pos; // <vec2 position, vec2 texCoords>
layout (location = 1) in vec4 a_Colour;
layout (location = 2) in vec2 a_TexCoords;

out vec2 v_TexCoods;
out vec4 v_Colour;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    v_TexCoods = a_TexCoords;
    v_Colour = a_Colour;
    gl_Position = projection * model * vec4(a_Pos, 1.0f);
}