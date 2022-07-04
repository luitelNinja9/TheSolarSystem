#version 430
in vec3 varyingNormal;
in vec3 varyingLightDir;
in vec3 varyingVertPos;
in vec3 varyingTangent;
in vec3 originalVertex;

layout (location=2) in vec3 vertNormal;

out vec4 fragColor;
in vec3 varyingHalfVector;
in vec2 ptc;

// structs and uniforms same as for Gouraud shading

struct PositionalLight
{ vec4 ambient;
vec4 diffuse;
vec4 specular;
vec3 position;
};

uniform vec4 globalAmbient;
uniform PositionalLight light;
uniform mat4 norm_matrix;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform int button;
uniform float distance;


layout(binding = 0) uniform sampler2D samp;
layout(binding = 1) uniform sampler2D sampn;



vec3 calcNewNormal()
{ vec3 normal = normalize(varyingNormal);
vec3 tangent = normalize(varyingTangent);
tangent = normalize(tangent - dot(tangent, normal) * normal); // tangent is perpendicular to normal
vec3 bitangent = cross(tangent, normal);
mat3 tbn = mat3(tangent, bitangent, normal);
 // TBN matrix to convert to camera space
vec3 retrievedNormal = texture(sampn,ptc).xyz;
retrievedNormal = retrievedNormal * 2.0 - 1.0;
 // convert from RGB space
vec3 newNormal = tbn * retrievedNormal;
newNormal = normalize(newNormal);
return newNormal;
}





void main(void)
{ // normalize the light, normal, and view vectors:

vec4 textureColor = texture(samp,ptc);

vec3 L = normalize(varyingLightDir);
vec3 N = normalize(varyingNormal);
if(button==1) vec3 N = calcNewNormal();
vec3 V = normalize(-varyingVertPos);
// compute light reflection vector with respect to N:
vec3 R = normalize(reflect(-L, N));
vec3 H = normalize(varyingHalfVector);

// get the angle between the light and surface normal:
float cosTheta = dot(L,N);
// angle between the view vector and reflected light:
float cosPhi = dot(V,R);
//float cosPhi = dot(H,N);

float attenDis = 1/(1.0f + 0.3f*distance + 0.3f*distance*distance);
// compute ADS contributions (per pixel), and combine to build output color:
vec3 ambient = ((globalAmbient ) + (light.ambient*5.0f )).xyz;
vec3 diffuse = light.diffuse.xyz  * max(cosTheta,0.0);
vec3 specular = light.specular.xyz  * pow(max(cosPhi,0.0), 5.0);
		 
//fragColor = textureColor * vec4((ambient + diffuse + specular), 1.0);

fragColor = (globalAmbient)*0.14f + 
	textureColor * (light.ambient*(attenDis*15.0f)*6.0+
	1.5*(light.diffuse*15.0f)*attenDis*max(cosTheta,0.0)) + 
	1.1*attenDis*10.0f*(light.specular*pow(max(cosPhi,0.0), 2.5));
}
