#version 120

uniform float time;

void main()
{

	vec4 vertexPos = gl_Vertex;

	vertexPos.x += mod(time*20,(20*20));
	vertexPos.y += mod(time*20,(20*20));

    // transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * vertexPos;

    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

    // forward the vertex color
    gl_FrontColor = gl_Color;
}