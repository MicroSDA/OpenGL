#version 400 core 

in vec3 Position; // In attribute - glBindAttribLocation(m_program, 0, "Position");
in vec2 TexCoord; // In attribute - glBindAttribLocation(m_program, 1, "TexCoord");
in vec3 Normal;   // In attribute - glBindAttribLocation(m_program, 2, "Normal");

out vec2 TexCoord_out; // Out Variables for Fagment Shader
out vec3 Normal_out;   // Out Variables for Fagment Shader

uniform mat4 MVP_U;    // In Uniform - glGetUniformLocation(m_program, "MVP_U");
uniform mat4 Normal_U; // In Uniform - glGetUniformLocation(m_program, "Normal_U")


void main()
{
	gl_Position = MVP_U * vec4(Position, 1.0); // Set Position 
	TexCoord_out = TexCoord; // For Out
	Normal_out = (Normal_U * vec4(Normal, 0.0)).xyz; // For Out
}