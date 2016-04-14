#version 400 core

in vec2 TexCoord_out; // In Variables of VertexShader
in vec3 Normal_out;   // In Variables of VertexShader


uniform sampler2D Sampler;    // Texture Sampler
uniform vec3 LightDirection_U; // In Uniform - glGetUniformLocation(m_program, "LightPosition_U");
uniform float LightMinStr_U;   // In Uniform - glGetUniformLocation(m_program, "LightMaxStr_U");
uniform float LightMaxStr_U;   // In Uniform - glGetUniformLocation(m_program, "LightMinStr_U");

out vec4 out_Color;            // Out result

void main()
{

    vec4 TextureColor = texture(Sampler, TexCoord_out);
	
	//If texture have transparent 
	if(TextureColor.a < 0.6){
	   discard;
	}
	
	out_Color = TextureColor * clamp(dot(-LightDirection_U, Normal_out), LightMinStr_U, LightMaxStr_U);
}
