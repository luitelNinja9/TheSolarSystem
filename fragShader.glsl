#version 430

out vec4 fragColor;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

layout(binding = 0) uniform sampler2D samp;
//layout(binding=1) uniform sampler2D normMap;



in vec4 varyingColor1;
in vec4 varyingColor2;
in vec2 ptc;
//in vec3 varyingTangent;



struct PositionalLight
{ 
vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform mat4 norm_matrix;


//vec3 calcNewNormal()
//{ vec3 normal = normalize(varyingNormal);
//vec3 tangent = normalize(varyingTangent);
//tangent = normalize(tangent - dot(tangent, normal) * normal); // tangent is perpendicular to normal
//vec3 bitangent = cross(tangent, normal);
//mat3 tbn = mat3(tangent, bitangent, normal);
 // TBN matrix to convert to camera space
//vec3 retrievedNormal = texture(normMap,tc).xyz;
//retrievedNormal = retrievedNormal * 2.0 - 1.0;
 // convert from RGB space
//vec3 newNormal = tbn * retrievedNormal;
//newNormal = normalize(newNormal);
//return newNormal;
//}




//UI
uniform int button;


void main(void)
{	
	//Green color
	//color = vec4(0.0,1.0,0.0,1.0);


	
	//if(gl_VertexID > 6) color = varyingColor;
	//else 
	//fragColor = texture(samp,ptc);
	//texture color
	vec4 textureColor = texture(samp,ptc);

	//if(button == 1) fragColor = vec4(0.3,0.3,0.3,1.0); 
	if(button == 1) fragColor = textureColor; 
	if(button == 2) fragColor = vec4(0.0,1.0,0.0,1.0); 
	else if(button == 0) fragColor = textureColor*(varyingColor1) + varyingColor2;
	
}